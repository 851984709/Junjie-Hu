import tensorflow as tf
import numpy as np
import os

def add_layer(inputs, in_size, out_size, activation_function=None):
    # 推荐权重和偏置不为0
    Weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1)
    Wx_plus_b = tf.matmul(inputs, Weights) + biases
    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
    return outputs

def weight_variable(shape):
    inital = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(inital)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W):  # x为图片的全部信息，W为权重
    # strides [1,x_movement,y_movement,1]
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

def get_prediction(image_batch):
    with tf.name_scope('Conv'):
        with tf.name_scope('conv1'):
            # conv1 layer
            W_conv1 = weight_variable([3, 3, 3, 16])  # in_size：3*3*3 out_size：1*1*16 16为卷积核个数
            b_conv1 = bias_variable([16])
            h_conv1 = tf.nn.relu(conv2d(image_batch, W_conv1) + b_conv1)  # out_size 200*200*16
            h_pool1 = max_pool_2x2(h_conv1)  # out_size 100*100*16
        with tf.name_scope('conv2'):
            # conv2 layer
            W_conv2 = weight_variable([3, 3, 16, 32])  # in_size：3*3*16 out_size：1*1*32
            b_conv2 = bias_variable([32])
            h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)  # out_size 100*100*32
            h_pool2 = max_pool_2x2(h_conv2)  # out_size 50*50*32
    with tf.name_scope('Full'):
        with tf.name_scope('fun1'):
            # func1 layer 全连接
            W_fc1 = weight_variable([50 * 50 * 32, 32])
            b_fc1 = bias_variable([32])
            h_pool2_flat = tf.reshape(h_pool2, [-1, 50 * 50 * 32])
            h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)  # out_size 64
        with tf.name_scope('func2'):
            # func2 layer 全连接
            W_fc2 = weight_variable([32, 8])
            b_fc2 = bias_variable([8])
            h_fc2 = tf.nn.relu(tf.matmul(h_fc1, W_fc2) + b_fc2)
            h_fc2_drop = tf.nn.dropout(h_fc2, keep_prob=1)
        with tf.name_scope('func3'):
            # func3 layer 全连接
            W_fc3 = weight_variable([8, 2])
            b_fc3 = bias_variable([2])
            prediction = tf.nn.softmax(tf.matmul(h_fc2_drop, W_fc3) + b_fc3)

    return prediction

def get_train_step(prediction,label_batch):
    with tf.name_scope('train_step'):
        cross_entropy = tf.reduce_mean(-tf.reduce_sum(label_batch * tf.log(prediction), reduction_indices=[1]))

        train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

    return train_step

def get_accuracy(prediction,label_batch):
    with tf.name_scope('accuracy'):
        correct_prediction = tf.equal(tf.argmax(prediction, 1),
                                      tf.argmax(label_batch, axis=1))  # tf.argmax和np.argmax一样
        accuracy = tf.reduce_mean(
            tf.cast(correct_prediction, tf.float32))  # cast：投射，将bool类型的数据转化为float

    return accuracy