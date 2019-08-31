# TensorFlow
import tensorflow as tf
# Numpy
import numpy as np
# Sys module
import sys


class Actor:
    def __init__(self, env, session, learning_rate=0.01, alpha=1e-5):
        self.session = session
        # Definition of action space size and boundaries
        self.min_action_value = env.action_space.low
        self.max_action_value = env.action_space.high
        self.action_space_dim = env.action_space.shape[0]
        # Definition of state space size and limits
        self.state_space_dim = env.observation_space.shape[0]
        # Neural Network optimizer
        self.nn_optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate)
        # Get the variables from the network
        self.max_gradient = sys.maxsize
        self.alpha = alpha
        # Initialization of variables
        with tf.name_scope("actor_inputs"):
            self.state = tf.placeholder(tf.float32, (None, self.state_space_dim), name="state")
            self.action = tf.placeholder(tf.float32, (None, self.action_space_dim), name="action")
            self.sigma = tf.placeholder(tf.float32, name="sigma")
        # Initialize actor predictor graph
        # Define the first executed actor (dataflow) as the neural network
        self.predicted_action = self.neural_network(self.state)
        # Define the second executed actor in the graph as the gaussian exploration
        self.predicted_action_sampled = self.gaussian_exploration_policy(self.predicted_action, self.sigma)
        # Final actor in graph is the clipping operator
        self.predicted_action_sampled = tf.clip_by_value(self.predicted_action_sampled, self.min_action_value,
                                                         self.max_action_value)
        network_variables = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope="actor_nn")
        with tf.name_scope("actor_loss"):
            self.loss = tf.losses.mean_squared_error(self.action, self.predicted_action)
        with tf.name_scope("actor_train"):
            gradients = self.nn_optimizer.compute_gradients(self.loss, network_variables)
            for i, (grad, var) in enumerate(gradients):
                if grad is not None:
                    # grad = tf.Print(grad, [grad], 'grad: ')
                    gradients[i] = ((self.loss * grad), var)
            self.learn_optimizer = self.nn_optimizer.apply_gradients(gradients)

        self.session.run(tf.global_variables_initializer())
        tf.summary.scalar("state", self.state)
        tf.summary.scalar("predicted_action", self.predicted_action)
        tf.summary.scalar("predicted_action_sampled", self.predicted_action_sampled)
        tf.summary.scalar("action", self.action)
        tf.summary.scalar("sigma", self.sigma)
        self.merged = tf.summary.merge_all()
        self.train_writer = tf.summary.FileWriter('./train',
                                             self.session.graph)

    def neural_network(self, state):
        # Function Approximator for the actor using a simple Neural Network (NN)
        # The NN:
        #        input layer (state)
        #        hidden layer (12 neurons, see "Reinforcement Learning in Continuous Action Spaces" by
        #                                       Hado van Hasselt and Marco A. Wiering
        #        output layer (actions)
        with tf.variable_scope("actor_nn"):
            # Create a first layer of size of state space as input and with 12 neurons on output
            input_weigth = tf.get_variable("input_layer", [self.state_space_dim, 20],
                                           initializer=tf.random_normal_initializer(mean=0.0, stddev=0.1))
            # Create a bias layer for the input layer
            bias1 = tf.get_variable("bias1_layer", [20], initializer=tf.constant_initializer(0))
            # Propagate state through input layer and bias
            hidden1 = tf.nn.tanh(tf.matmul(state, input_weigth) + bias1)
            # Weights of the hidden layer
            hidden_weigth = tf.get_variable("hidden_layer", [20, self.action_space_dim],
                                            initializer=tf.random_normal_initializer(mean=0.0, stddev=0.5))
            # Create a bias layer for the hidden layer
            bias2 = tf.get_variable("bias2_layer", [self.action_space_dim], initializer=tf.constant_initializer(0))
            action = tf.matmul(hidden1, hidden_weigth) + bias2
        return action

    def gaussian_exploration_policy(self, action, sigma):
        # Sample actions following a normal distribution law centered around "action" value with parameter sigma
        with tf.name_scope("actor_gaussian_policy"):
            action_exploration = []
            for i in range(self.action_space_dim):
                # Create a normal distribution tensor graph centered on action value (mu) and with parameter sigma
                normal_dist = tf.contrib.distributions.Normal(action[0][i], sigma)
                # Get sample
                sample = normal_dist.sample(1)
                # Append sample
                action_exploration.append(sample[0])
            action_exploration = tf.reshape(action_exploration, [1, self.action_space_dim])
            return action_exploration

    def uniform_exploration_policy(self):
        # Sample actions following a uniform distribution
        with tf.name_scope("actor_uniform_policy"):
            action_exploration = []
            for i in range(self.action_space_dim):
                uniform_dist = tf.contrib.distributions.Uniform(low=self.min_action_value[i], high=self.max_action_value[i])
                # Get sample
                sample =uniform_dist.sample(1)
                # Append sample
                action_exploration.append(sample[0])
            action_exploration = tf.reshape(action_exploration, [1, self.action_space_dim])
            return action_exploration

    def predict(self, state, sigma):
        # Predict the action
        state_reshape = np.reshape(state, (1,self.state_space_dim))
        feed_dict = {
            self.state: state_reshape,
            self.sigma: sigma
        }
        return self.session.run(self.predicted_action_sampled, feed_dict=feed_dict)

    def predict_no_sample(self, state):
        # Predict the action
        state_reshape = np.reshape(state, (1,self.state_space_dim))
        feed_dict = {
            self.state: state_reshape
        }
        return self.session.run(self.predicted_action, feed_dict=feed_dict)

    def gen_network(self):
        network_variables = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope="actor_nn")
        print("Saving network..")
        network = self.session.run(network_variables)
        print(network)
        with open('/tmp/network.txt', 'w') as net_file:
            net_file.write("void weightGenInit(int id, OUT float *weights_out, OUT float *bias_out) {\n")
            net_file.write("\tswitch(id) {\n")
            i = 0
            for layer in network:
                if i % 2 == 0:
                    net_file.write("\t\tcase {}:\n".format(int(i / 2)))
                    l_size = len(layer[0])
                    i_size = len(layer)
                    l_index = 0
                    i_index = 0
                    val = 0
                    while l_index < l_size:
                        i_index = 0
                        while i_index < i_size:
                            net_file.write("\t\t\tweights_out[{}] = {}f;\n".format(i_index + l_index*i_size, layer[i_index][l_index]))
                            i_index += 1
                            val += 1
                        l_index += 1
                else:
                    l_size = len(layer)
                    l_index = 0
                    while l_index < l_size:
                        net_file.write("\t\t\tbias_out[{}] = {}f;\n".format(l_index, layer[l_index]))
                        l_index += 1
                    net_file.write("\t\t\tbreak;\n")
                i += 1
            net_file.write("\t\tdefault:\n")
            net_file.write("\t\t\tfprintf(stderr, \"Unhandled ID init value: %d\", id);\n")
            net_file.write("\t}\n")
            net_file.write("}\n")
            print("network saved.")

    def print_network(self):
        network_variables = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope="actor_nn")
        print("network:")
        network = self.session.run(network_variables)
        print(network)

    def print_infos(self, state, action):
        state_reshape = np.reshape(state, (1, self.state_space_dim))
        action_reshape = np.reshape(action, (1, self.action_space_dim))
        loss = tf.losses.mean_squared_error(self.action, self.predicted_action)
        loss = tf.Print(loss, [loss], "loss: ")
        feed_dict = {
            self.state: state_reshape,
            self.action: action_reshape
        }
        self.session.run(loss, feed_dict=feed_dict)
        network_variables = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope="actor_nn")
        gradients = self.nn_optimizer.compute_gradients(loss, network_variables)
        gradients_val = self.session.run(gradients, feed_dict=feed_dict)
        print("gradients: ")
        i = 0
        for layer in gradients_val:
            if i%2 == 0:
                print("weights:")
            else:
                print("bias:")
            print(layer[0])
            i += 1

    def update_action(self, state, action):
        # Update the action when the TD error is positive
        state_reshape = np.reshape(state, (1, self.state_space_dim))
        action_reshape = np.reshape(action, (1, self.action_space_dim))
        # Build the dictionary of data token for the execution of the graph
        feed_dict = {
            self.state: state_reshape,
            self.action: action_reshape
        }
        self.session.run([self.learn_optimizer], feed_dict=feed_dict)

    def _sigma(self):
        return self.session.run(self.sigma)

