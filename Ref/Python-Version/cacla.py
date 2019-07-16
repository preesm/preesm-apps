# Systems module
import sys
import time
from time import sleep
# OpenAI Gym modules
import gym
# TensorFlow
import tensorflow as tf
# Module for stats
from collections import namedtuple
# Numpy
import numpy as np

import actor_cacla
import critic_cacla

def train(env, parameters, render=False):
    return ''

def load(path):
    print('Loading model from: ', path)
    return ''

# Define a type for stats log
EpisodeStats = namedtuple("Stats", ["episode_lengths", "episode_rewards"])

# Main class
class CACLA(object):
    def __init__(self, env,
                 render=False,
                 max_episodes=100,
                 max_steps=1000,
                 max_reward=100,
                 actor_lr=0.01,
                 critic_lr=0.01,
                 discount_factor=0.99,
                 beta_variance=0.001,
                 sigma = 0.1,
                 model_save=False,
                 model_path = "./model/",
                 model_use=False):
        # All defaults values are choosen from
        # "Reinforcement Learning in Continuous Action Spaces" by Hado Van Hasselt and Marco A. Wiering
        self.env = env
        self.max_episodes = max_episodes
        self.max_step= max_steps
        self.max_reward= max_reward
        # Learning rate values for actor and critic FA
        self.actor_lr = actor_lr
        self.critic_lr = critic_lr
        # Discount factor
        self.discount_factor = discount_factor
        # Variance parameter
        self.beta_variance = beta_variance
        self.variance = 1.0
        # Actor / critic gradient constant
        self.actor_alpha = 0.001
        self.critic_alpha = 0.001
        # Gaussian sigma
        self.sigma_high = sigma
        self.sigma_low = 0.1
        self.sigma = sigma
        # Session variables
        self.render = render
        self.session = tf.Session()
        self.actor = actor_cacla.Actor(self.env, self.session, actor_lr, self.actor_alpha)
        self.critic = critic_cacla.Critic(self.env, self.session, critic_lr, self.critic_alpha)
        self.save_session = tf.train.Saver()
        self.save = model_save
        self.save_path = model_path
        if (model_use):
            split_path = model_path.split('/')
            print(split_path)
            split_path = split_path[0:len(split_path) - 1]
            self.save_path = '/'.join(split_path) + '/'
            self.save_session.restore(self.session, model_path)
        self.timers = []
        # Start all the timers
        self.fps_mean = 50
        self.timer_id = 0
        for i in range(self.fps_mean):
            self.timers.append(time.time())

    def print_fps(self):
        fps = self.get_fps()
        print("FPS: {}".format(fps))

    def get_fps(self):
        fps = 1 / ((time.time() - self.timers[self.timer_id]) / self.fps_mean)
        self.timers[self.timer_id] = time.time()
        self.timer_id = (self.timer_id + 1) % self.fps_mean
        return fps

    def save_exit(self):
        path = self.save_path + "model_" + time.strftime("%Y%m%d-%H%M%S") + ".ckpt"
        print("saving model...")
        self.save_session.save(self.session, path)
        print("saved model to: {}".format(path))
        print("exiting...")
        quit()

    def run_fixed(self):
        self.state = self.env.reset()
        t = 0
        array_size = 300
        reward_array = [0] * array_size
        index_array = 0
        i_episode = 0
        episode_reward = 0
        file = open("./stats.csv", "w")
        timer_start = time.time()
        while True:
            t += 1
            if self.render:
                self.env.render()
                sleep(0.01)
            # Get prediction for action
            action = self.actor.predict(self.state, self.sigma)

            # Perform the action
            next_state, reward, done, _ = self.env.step(action)

            # Compute delta (TD_error)
            value_next = self.critic.predict(next_state)
            value = self.critic.predict(self.state)
            target = reward + self.discount_factor * value_next
            td_error = target - value

            episode_reward += reward

            reward_array[index_array] = reward
            index_array = (index_array + 1) % array_size
            if t % array_size == 0:
                mean_reward = np.mean(reward_array)
                if abs(mean_reward) < 0.1:
                    wall_time = time.time() - timer_start
                    print("System converged in: {} time steps".format(t))
                    print("Wall Time: {}".format(wall_time))
                    file.close()
                    quit()
            if t % self.max_step == 0:
                print("Episode: {}".format(i_episode))
                print("Episode reward: {}".format(episode_reward))
                print("Time steps: {}".format(t))
                file.write("{}, {}".format(i_episode, episode_reward))
                i_episode += 1
                episode_reward = 0

            # Update critic network
            self.critic.update_critic(self.state, td_error)

            # If TD error is positive, update action
            if td_error > 0:
                # Compute the number of update for this action
                n_updates = int(np.ceil(td_error / np.sqrt(self.variance)))
                for i in range(n_updates):
                    # Update the actor network
                    self.actor.update_action(self.state, action)

            # Update the variance
            self.variance = self.update_var(td_error)

            # Update state
            self.state = next_state

    def run(self):
        episodes_stats = EpisodeStats(episode_lengths=np.zeros(self.max_episodes),
                                      episode_rewards=np.zeros(self.max_episodes))
        for i_episode in range(self.max_episodes):
            episode_reward = 0
            episode_timestep = 0
            self.state = self.env.reset()
            t = 0
            done = False
            array_size = 300
            reward_array = [0] * array_size
            while not done:
                t += 1
                if self.render:
                    self.env.render()
                    sleep(0.01)
                # Get prediction for action
                action = self.actor.predict(self.state, self.sigma)

                # Perform the action
                next_state, reward, done, _ = self.env.step(action)
                done = False  # Discard environment stop condition

                # Compute delta (TD_error)
                value_next = self.critic.predict(next_state)
                value = self.critic.predict(self.state)
                target = reward + self.discount_factor * value_next
                td_error = target - value

                reward_array = np.roll(reward_array, 1)
                reward_array[0] = reward
                if t % array_size == 0:
                    mean_reward = np.mean(reward_array)
                    if abs(mean_reward) < 0.1:
                        if self.save:
                            print("Target achieved in {} time steps".format(t))
                            self.save_exit()
                        else:
                            done = True

                # Update critic network
                self.critic.update_critic(self.state, target)

                # If TD error is positive, update action
                if td_error > 0:
                    # Compute the number of update for this action
                    n_updates = int(np.ceil(td_error / np.sqrt(self.variance)))
                    for i in range(n_updates):
                        # Update the actor network
                        self.actor.update_action(self.state, action)

                # Update the variance
                self.variance = self.update_var(td_error)

                # Update state
                self.state = next_state

                # Show FPS performances
                fps = self.get_fps()

                # Log values
                episode_reward += reward
                episode_timestep = t
                if done:
                    break

            self.print_fps()
            # Log the stats of the current episode
            episodes_stats.episode_rewards[i_episode] = episode_reward
            episodes_stats.episode_lengths[i_episode] = episode_timestep
            print("Episode: {}".format(i_episode))
            print("Episode reward: {}".format(episode_reward))
            print("Episode timestep: {}".format(episode_timestep))
            print("Episode sigma: {}".format(self.sigma))

            # Reduce sigma
            self.sigma = max(self.sigma_high + i_episode * (self.sigma_low - self.sigma_high) / (self.max_episodes / 2), self.sigma_low)

        path = self.save_path + "model_" + time.strftime("%Y%m%d-%H%M%S") + ".ckpt"
        print("saving model...")
        self.save_session.save(self.session, path)
        print("saved model to: {}".format(path))
        print("exiting...")
        quit()

    def run_test(self):
        i_episode = 0
        quit = False
        while not quit:
            # self.actor.gen_network()
            i_episode += 1
            episode_reward = 0
            episode_timestep = 0
            t = 0
            episode_step_limit = 300
            reward_array = [0] * episode_step_limit
            self.state = self.env.reset()
            print(self.state)
            done = False
            while not done:
                t += 1
                if self.render:
                    self.env.render()
                    sleep(0.001)
                # Get prediction for action
                action = self.actor.predict_no_sample(self.state)
                self.actor.gen_network()
                # Perform the action
                next_state, reward, done, _ = self.env.step(action)

                done = False

                # Compute delta (TD_error)
                target = reward + self.discount_factor * self.critic.predict(next_state)
                td_error = target - self.critic.predict(self.state)
                reward_array = np.roll(reward_array, 1)
                reward_array[0] = reward[0]
                mean_reward = np.mean(reward_array)
                if t % episode_step_limit == 0:
                    if abs(mean_reward) < 0.1:
                        done = True
                episode_timestep = t
                # Update critic network
                # self.critic.update_critic(self.state, target)
                # Update state
                self.state = next_state

                # Show FPS perfomances
                #self.print_fps()

            print("Episode: {}".format(i_episode))
            print("Episode reward: {}".format(episode_reward))
            print("Episode timestep: {}".format(episode_timestep))
            print("Running average of TD error variance: {}".format(self.variance))

    def run_perf(self):
        timer_quit = time.time()
        mean_FPS = 0
        counter_FPS = 0
        quit = False
        self.state = self.env.reset()
        total_duration = 0
        while not quit:
            # Get prediction for action
            action = self.actor.predict_no_sample(self.state)
            # Perform the action
            next_state, reward, done, _ = self.env.step(action)
            # target = reward + self.discount_factor * self.critic.predict(next_state)
            # td_error = target - self.critic.predict(self.state)
            self.state = next_state
            # Get performance
            mean_FPS += self.get_fps()
            counter_FPS += 1
            total_duration = time.time() - timer_quit
            if total_duration > 10:
                quit = True
        mean_FPS /= counter_FPS
        print("Running time: {}".format(total_duration))
        print("Average FPS: {}".format(mean_FPS))


    def bench(self):
        iterations = 10000.
        print("Bench configuration:")
        print("==> Sigma:         {}".format(self.sigma))
        print("==> Learning rate: {}".format(self.actor.nn_optimizer.__getattribute__("_lr")))
        print("==> Beta 1:        {}".format(self.actor.nn_optimizer.__getattribute__("_beta1")))
        print("==> Beta 2:        {}".format(self.actor.nn_optimizer.__getattribute__("_beta2")))
        print("==> Beta 1 pow:    {}".format(self.session.run(self.actor.nn_optimizer.__getattribute__("_beta1_power"))))
        print("==> Beta 2 pow:    {}".format(self.session.run(self.actor.nn_optimizer.__getattribute__("_beta2_power"))))
        print("==> Epsilon:       {}".format(self.actor.nn_optimizer.__getattribute__("_epsilon")))
        print("==> Iterations:    {}".format(iterations))
        print("The benchmark uses fixed sinus values for learning.\n"
              "Values of sinus used are evenly spaced (1 / iterations) in [0, 1]")
        delta = 1. / iterations
        self.actor.print_network()
        for i in range(int(iterations)):
            x = i * delta
            target = np.sin(x)
            self.state = [x, x, x]
            value = self.actor.predict_no_sample(self.state)
            # print("target: ", target)
            # print("prediction: ", value[0][0])
            # self.actor.print_infos(self.state, target)
            self.actor.update_action(self.state, target)
        self.actor.print_network()
        print("==> Beta 1 pow:    {}".format(self.session.run(self.actor.nn_optimizer.__getattribute__("_beta1_power"))))
        print("==> Beta 2 pow:    {}".format(self.session.run(self.actor.nn_optimizer.__getattribute__("_beta2_power"))))


    def generate_net(self):
        self.actor.gen_network()
        self.save_exit()

    def scale_reward(self, reward):
        scaled_reward = reward / self.max_reward
        if scaled_reward > 1:
            scaled_reward = 1
        elif scaled_reward < -1:
            scaled_reward = -1
        return scaled_reward

    def update_var(self, delta):
        return self.variance * (1 - self.beta_variance) + (delta ** 2) * self.beta_variance

    def signal_handler(self, signal, frame):
        print('Toggling render...')
        self.render = not self.render
