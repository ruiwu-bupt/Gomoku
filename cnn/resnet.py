import tensorflow as tf
import tensorflow.contrib.slim as slim
from tensorflow.contrib import layers
from config import *
import block
import pdb

# resnet类,包含构造函数,训练,推导,保存模型,载入模型等方法
class resnet39:
    def __init__(self, sess):
        self.sess = sess
        # create reset39 network
        self.inputs, self.outputs = self.create_resnet39()
        self.labels = tf.placeholder(tf.float32, [None, self.outputs.get_shape()[-1]])
        self.network_params = \
            tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES)

        # 损失函数
        self.loss = tf.losses.softmax_cross_entropy(self.outputs[:-1], self.labels[:-1])
        self.loss += (self.outputs[-1] - self.labels[-1]) ** 2
        regularizer = layers.l2_regularizer(C)
        # pdb.set_trace()
        layers.apply_regularization(regularizer, tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES))
        self.loss += tf.reduce_sum(tf.get_collection(tf.GraphKeys.REGULARIZATION_LOSSES))
        self.train_op = tf.train.MomentumOptimizer(L, M).minimize(self.loss)

    def create_resnet39(self):
        inputs = tf.placeholder(tf.float32, [None, N, N, 17])
        conv0 = block.pre_conv(inputs)
        conv1 = conv0
        for i in range(19):
            conv1 = block.bottleneck(conv1)
        policy = block.policy_head(conv1, N)
        value = block.value_head(conv1)
        # pdb.set_trace()
        return inputs, tf.concat([policy, value], 1)

    def train(self, inputs, labels):
        self.sess.run(self.train_op, feed_dict={self.inputs: inputs, self.labels: labels})

    def predict(self, inputs):
        return self.sess.run(self.outputs, feed_dict={self.inputs: inputs})
