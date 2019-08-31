# Module to parse arguments
import argparse
# Systems module
import sys
from time import sleep
import signal
# JSON module
import json
# OpenAI Gym modules
import gym
from gym import wrappers
# TensorFlow
import tensorflow as tf
# Continuous Actor-Critic Learning Automateon implementation
from cacla import CACLA

import numpy as np

RENDER_SLEEP_TIME=0.01

def train(env, parameters, render=False, model_save=False, model_path="./model/", model_use=False):
    cacla = CACLA(env,
                  render,
                  max_episodes=10000,
                  max_steps=20000,
                  max_reward=100.0,
                  actor_lr=0.0001,
                  critic_lr=0.0001,
                  discount_factor=0.99,
                  beta_variance=0.001,
                  sigma=2,
                  model_save=model_save,
                  model_path=model_path,
                  model_use=model_use
                  )
    signal.signal(signal.SIGINT, cacla.signal_handler)
    cacla.run()

def test(env, parameters, render=False, model_save=False, model_path="./model/", model_use=False):
    # return cacla.train(env, parameters, render)
    cacla = CACLA(env,
                  render,
                  max_episodes=1000,
                  max_steps=10000,
                  max_reward=100.0,
                  actor_lr=0.01,
                  critic_lr=0.01,
                  discount_factor=0.95,
                  beta_variance=0.001,
                  sigma=0.1,
                  model_save=model_save,
                  model_path=model_path,
                  model_use=model_use
                  )
    signal.signal(signal.SIGINT, cacla.signal_handler)
    cacla.run_test()

def perf(env, parameters, render=False, model_save=False, model_path="./model/", model_use=False):
    # return cacla.train(env, parameters, render)
    cacla = CACLA(env,
                  render,
                  max_episodes=1000,
                  max_steps=10000,
                  max_reward=100.0,
                  actor_lr=0.01,
                  critic_lr=0.01,
                  discount_factor=0.95,
                  beta_variance=0.001,
                  sigma=0.1,
                  model_save=model_save,
                  model_path=model_path,
                  model_use=model_use
                  )
    signal.signal(signal.SIGINT, cacla.signal_handler)
    cacla.run_perf()


def bench(env, parameters, render=False, model_save=False, model_path="./model/", model_use=False):
    cacla = CACLA(env,
                  render,
                  max_episodes=10000,
                  max_steps=20000,
                  max_reward=100.0,
                  actor_lr=0.01,
                  critic_lr=0.01,
                  discount_factor=0.99,
                  beta_variance=0.001,
                  sigma=0.5,
                  model_save=model_save,
                  model_path=model_path,
                  model_use=model_use
                  )
    signal.signal(signal.SIGINT, cacla.signal_handler)
    cacla.bench()


def generate_net(env, parameters, render=False, model_save=False, model_path="./model/", model_use=False):
    cacla = CACLA(env,
	  render,
	  max_episodes=10000,
	  max_steps=20000,
	  max_reward=100.0,
	  actor_lr=0.01,
	  critic_lr=0.01,
	  discount_factor=0.99,
	  beta_variance=0.001,
	  sigma=0.5,
	  model_save=model_save,
	  model_path=model_path,
	  model_use=model_use
	  )
    signal.signal(signal.SIGINT, cacla.signal_handler)
    cacla.generate_net()

def valid_mode(argument):
    allowed = ['train', 'test', 'perf', 'bench']
    if argument not in allowed:
        raise argparse.ArgumentTypeError('Invalid mode.\nAvailable modes: \n\t\'test\': test a model on an environment'
                                         '\n\t\'train\': train a model on an environment')
    return argument

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('mode', type=valid_mode, nargs=1, default='train', help='Specifies the mode (train or test).')
    parser.add_argument('-environment', type=str, nargs=1, default=['Pendulum-v0'], help='Select the environment to run.')
    parser.add_argument('-monitor', action='store_true', default=False, help='Enables the monitoring of the environment.')
    parser.add_argument('-monitor-folder', default='./', help='Specifies the monitor\'s folder.')
    parser.add_argument('-training-parameters', default='./', help='Specifies the location of the model parameters to use.')
    parser.add_argument('-render', action='store_true', default=False, help='Specifies the monitor\'s folder.')
    parser.add_argument('-model-use', action='store_true', default=False, help='Use a pre-train model.')
    parser.add_argument('-model-save', action='store_true', default=False, help='Save model when episode is finished.')
    parser.add_argument('-model-path', type=str, default='./model/', help='Specifies the location of the model to use.')
    parser.add_argument('-generate-network', action='store_true', default=False, help='Generate a network.txt file and a model to perform benchmark.')
    args = parser.parse_args()
    try:
        env = gym.make(args.environment[0])
    except Exception as inst:
        print('An exception occurred while loading environment')
        print('\t|--> {}'.format(type(inst)))
        print('\t|--> {}'.format(inst))
    else:
        env.seed()
        tf.set_random_seed(42)
        if args.monitor:
            env = wrappers.Monitor(env, directory=args.monitor_folder + 'Monitor', force=True)
        if args.mode[0] == 'train':
            train(env, args.training_parameters, args.render, args.model_save, args.model_path, args.model_use)
        elif args.mode[0] == 'test':
            test(env, args.training_parameters, args.render, args.model_save, args.model_path, args.model_use)
        elif args.mode[0] == 'perf':
            perf(env, args.training_parameters, args.render, args.model_save, args.model_path, args.model_use)
        elif args.mode[0] == 'bench':
            if args.generate_network:
                generate_net(env, args.training_parameters, args.render, args.model_save, args.model_path, args.model_use)
            else:
                bench(env, args.training_parameters, args.render, args.model_save, args.model_path, args.model_use)
        env.close()

