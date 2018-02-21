import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import numpy as np
import os

# 1到10的数据
# 如果电脑上没有该数据包，就会在网上自动下载下来
# 如果有，就直接使用
mnist = input_data.read_data_sets('MNIST_data/',one_hot=True)

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

def add_layer(inputs,in_size,out_size,activation_function=None):
    # 推荐权重和偏置不为0
    Weights = tf.Variable(tf.random_normal([in_size,out_size]))
    biases = tf.Variable(tf.zeros([1,out_size]) + 0.1)
    Wx_plus_b = tf.matmul(inputs,Weights) + biases
    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
    return outputs

def compute_accuracy(v_xs,v_ys):
    global prediction
    y_pre = sess.run(prediction,feed_dict={xs:v_xs,keep_prob:1})
    correct_prediction = tf.equal(tf.argmax(y_pre,1),
                                  tf.argmax(v_ys,axis=1)) # tf.argmax和np.argmax一样
    accuracy = tf.reduce_mean(
        tf.cast(correct_prediction,tf.float32)) # cast：投射，将bool类型的数据转化为float
    result = sess.run(accuracy,feed_dict={xs:v_xs,ys:v_ys,keep_prob:1})
    return result

def weight_variable(shape):
    inital = tf.truncated_normal(shape,stddev=0.1)
    return tf.Variable(inital)

def bias_variable(shape):
    initial = tf.constant(0.1,shape=shape)
    return tf.Variable(initial)

def conv2d(x,W): # x为图片的全部信息，W为权重
    # strides [1,x_movement,y_movement,1]
    return tf.nn.conv2d(x,W,strides=[1,1,1,1],padding='SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x,ksize=[1,2,2,1],strides=[1,2,2,1],padding='SAME')

# 定义占位符
keep_prob = tf.placeholder(tf.float32)
xs = tf.placeholder(tf.float32,[None,784]) #28*28
ys = tf.placeholder(tf.float32,[None,10])
x_image = tf.reshape(xs,[-1,28,28,1])
# -1：暂时先不管reshape的维度，由后面导入的数据决定，-1可以理解为导入数据有多少个图片
# 1:channel，通道数
# print(x_image.shape) #[n_samples,28,28,1] n_sample:数据的个数

# conv1 layer
W_conv1 = weight_variable([5,5,1,32]) # in_size：5*5*1 out_size：1*1*32 32为卷积核个数
b_conv1 = bias_variable([32])
h_conv1 = tf.nn.relu(conv2d(x_image,W_conv1) + b_conv1) # out_size 28*28*32
h_pool1 = max_pool_2x2(h_conv1) # out_size 14*14*32

# conv2 layer
W_conv2 = weight_variable([5,5,32,64]) # in_size：5*5*32 out_size：1*1*64
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1,W_conv2) + b_conv2) # out_size 14*14*64
h_pool2 = max_pool_2x2(h_conv2) # out_size 7*7*64
 
# func1 layer 全连接
W_fc1 = weight_variable([7*7*64,1024])
b_fc1 = bias_variable([1024])
# [n_samples,7,7,64] ->> [n_samples,7*7*64]
h_pool2_flat = tf.reshape(h_pool2,[-1,7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat,W_fc1) + b_fc1)
h_fc1_drop = tf.nn.dropout(h_fc1,keep_prob)

# func2 layer 全连接
W_fc2 = weight_variable([1024,10])
b_fc2 = bias_variable([10])
prediction = tf.nn.softmax(tf.matmul(h_fc1_drop,W_fc2) + b_fc2)

cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys*tf.log(prediction),reduction_indices=[1]))

train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

init = tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    sess.run(init)
    for i in range(1000):
        batch_xs,batch_ys = mnist.train.next_batch(1000)
        sess.run(train_step,feed_dict={xs:batch_xs,ys:batch_ys,keep_prob:0.5})

        if i%50 ==0:
            # 显示精度
            print(compute_accuracy(mnist.test.images[:1000],mnist.test.labels[:1000]))


