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
    y_pre = sess.run(prediction,feed_dict={xs:v_xs})
    correct_prediction = tf.equal(tf.argmax(y_pre,1),
                                  tf.argmax(v_ys,axis=1)) # tf.argmax和np.argmax一样
    accuracy = tf.reduce_mean(
        tf.cast(correct_prediction,tf.float32)) # cast：投射，将bool类型的数据转化为float
    result = sess.run(accuracy,feed_dict={xs:v_xs,ys:v_ys})
    return result

# 定义占位符
xs = tf.placeholder(tf.float32,[None,784]) #28*28
ys = tf.placeholder(tf.float32,[None,10])

# 添加输出层
# 分类的激活函数最好使用softmax
# softmax返回归一化后的概率矩阵
prediction = add_layer(xs,784,10,activation_function=tf.nn.softmax)

# 交叉熵，预测数值相对于真实值的误差
cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys*tf.log(prediction),reduction_indices=[1]))

train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

init = tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    sess.run(init)
    for i in range(1000):
        batch_xs,batch_ys = mnist.train.next_batch(1000)
        sess.run(train_step,feed_dict={xs:batch_xs,ys:batch_ys})

        if i%50 ==0:
            # 显示精度
            print(compute_accuracy(mnist.test.images,mnist.test.labels))


