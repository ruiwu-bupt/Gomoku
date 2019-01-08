import tensorflow as tf
import tensorflow.contrib.slim as slim

# 根据alphago zero论文, filter一直是256, 不需要考虑降采样与通道填充
# 参数的初始方式?scope命名?
def pre_conv(input_tensor, is_train=True):
    input_tensor = slim.conv2d(input_tensor, 256, [3, 3])
    input_tensor = tf.layers.batch_normalization(input_tensor, training=is_train)
    input_tensor = tf.nn.relu(input_tensor)
    return input_tensor

def bottleneck(input_tensor, is_train=True):
    data = input_tensor
    data = slim.conv2d(data, 256, [3, 3])
    data = tf.layers.batch_normalization(data, training=is_train)
    data = tf.nn.relu(data)

    data = slim.conv2d(data, 256, [3, 3])
    data = tf.layers.batch_normalization(data, training=is_train)
    data += input_tensor
    data = tf.nn.relu(data)
    return data

def policy_head(input_tensor, board_sz, is_train=True):
    input_tensor = slim.conv2d(input_tensor, 2, [1, 1])
    input_tensor = tf.layers.batch_normalization(input_tensor, training=is_train)
    input_tensor = tf.nn.relu(input_tensor)
    input_tensor = slim.fully_connected(input_tensor, board_sz*board_sz)
    return input_tensor

def value_head(input_tensor, is_train=True):
    input_tensor = slim.conv2d(input_tensor, 1, [1, 1])
    input_tensor = tf.layers.batch_normalization(input_tensor, training=is_train)
    input_tensor = tf.nn.relu(input_tensor)
    input_tensor = slim.fully_connected(input_tensor, 256)
    input_tensor = tf.nn.relu(input_tensor)
    input_tensor = slim.fully_connected(input_tensor, 1)
    input_tensor = tf.nn.tanh(input_tensor)
    return input_tensor
