# TensorFlow
import tensorflow as tf
from tensorflow.python.framework import ops
from tensorflow.python.ops import math_ops
# Numpy
import numpy as np
# Sys module
import sys


class Critic:
    def __init__(self, env, session, learning_rate=0.01, alpha=1e-5):
        self.session = session
        # Definition of state space size and limits
        self.state_space_dim = env.observation_space.shape[0]
        # Neural Network optimizer
        self.nn_optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate)
        # Initialization of variables
        with tf.name_scope("critic_inputs"):
            self.state = tf.placeholder(tf.float32, (None, self.state_space_dim), name="state")
            self.target = tf.placeholder(tf.float32, (None, 1), name="target")
        # Initialize actor predictor graph
        # Define the first executed actor (dataflow) as the neural network
        self.value = self.neural_network(self.state)
        # self.value = tf.clip_by_value(self.value, -1, 1)
        # Get the variables from the network
        self.alpha = alpha
        self.max_gradient = sys.maxsize
        network_variables = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope="critic_nn")
        with tf.name_scope("critic_loss"):
            self.loss = tf.losses.mean_squared_error(self.target, self.value)
        with tf.name_scope("critic_train"):
            gradients = self.nn_optimizer.compute_gradients(self.loss, network_variables)
            for i, (grad, var) in enumerate(gradients):
                if grad is not None:
                    gradients[i] = (self.loss * grad, var)
                    # gradients[i] = (self.alpha * self.loss * grad, var)#(tf.clip_by_norm(self.alpha * self.loss * grad, self.max_gradient), var)
            self.learn_optimizer = self.nn_optimizer.apply_gradients(gradients)
        self.session.run(tf.global_variables_initializer())
        tf.summary.scalar("state", self.state)
        tf.summary.scalar("value", self.value)
        tf.summary.scalar("target", self.target)
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
        with tf.variable_scope("critic_nn"):
            # Create a first layer of size of state space as input and with 12 neurons on output
            input_weigth = tf.get_variable("input_layer", [self.state_space_dim, 20],
                               initializer=tf.contrib.layers.xavier_initializer())
            # Create a bias layer for the input layer
            bias1 = tf.get_variable("bias1_layer", [20], initializer=tf.constant_initializer(0))
            # Propagate state through input layer and bias
            hidden1 = tf.nn.tanh(tf.matmul(state, input_weigth) + bias1)
            # Weights of the hidden layer
            hidden_weigth = tf.get_variable("hidden_layer", [20, 1],
                               initializer=tf.contrib.layers.xavier_initializer())
            # Create a bias layer for the hidden layer
            bias2 = tf.get_variable("bias2_layer", [1], initializer=tf.constant_initializer(0))
            value = tf.matmul(hidden1, hidden_weigth) + bias2
        return value

    def predict(self, state):
        # Predict the value
        state_reshape = np.reshape(state, (1,self.state_space_dim))
        feed_dict = {
            self.state: state_reshape
        }
        return self.session.run(self.value, feed_dict=feed_dict)

    def update_critic(self, state, target):
        # Update the action when the TD error is positive
        state_reshape = np.reshape(state, (1, self.state_space_dim))
        # Build the dictionary of data token for the execution of the graph
        feed_dict = {
            self.state: state_reshape,
            self.target: target
        }
        self.session.run([self.learn_optimizer], feed_dict=feed_dict)

