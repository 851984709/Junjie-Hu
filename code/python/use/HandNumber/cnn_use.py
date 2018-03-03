import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
import cv2
import os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
# 设置为使用cpu运算
os.environ['CUDA_VISIBLE_DEVICES'] = ""


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

def predict_index(v_xs):
    global prediction
    y_pre = sess.run(prediction, feed_dict={xs: v_xs, keep_prob: 1})
    return sess.run(tf.argmax(y_pre,1))

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


# 定义占位符
keep_prob = tf.placeholder(tf.float32)
xs = tf.placeholder(tf.float32, [None, 784])  # 28*28
ys = tf.placeholder(tf.float32, [None, 10])
x_image = tf.reshape(xs, [-1, 28, 28, 1])
# -1：暂时先不管reshape的维度，由后面导入的数据决定，-1可以理解为导入数据有多少个图片
# 1:channel，通道数
# print(x_image.shape) #[n_samples,28,28,1] n_sample:数据的个数

# conv1 layer
W_conv1 = weight_variable([5, 5, 1, 32])  # in_size：5*5*1 out_size：1*1*32 32为卷积核个数
b_conv1 = bias_variable([32])
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)  # out_size 28*28*32
h_pool1 = max_pool_2x2(h_conv1)  # out_size 14*14*32

# conv2 layer
W_conv2 = weight_variable([5, 5, 32, 64])  # in_size：5*5*32 out_size：1*1*64
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)  # out_size 14*14*64
h_pool2 = max_pool_2x2(h_conv2)  # out_size 7*7*64

# func1 layer 全连接
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])
# [n_samples,7,7,64] ->> [n_samples,7*7*64]
h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * 64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

# func2 layer 全连接
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])
prediction = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

# 创建保存器
saver = tf.train.Saver()

# 导入图片
filepath = input('Please input the path of your image:')

# 加载图片
image = cv2.imread(filepath)
image = cv2.resize(image,(28,28))
image = cv2.cvtColor(image,cv2.COLOR_RGB2GRAY)
image = np.array(image).reshape(1,28*28)

# 初始化所有变量
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    # 提取神经网络参数
    saver.restore(sess, 'cnn_save/cnn_save.ckpt')
    # 使用神经网络检测图片
    print(predict_index(image))

image = image.reshape((28,28))
plt.imshow(image,cmap='gray')
plt.xticks(())
plt.yticks(())
plt.show()


