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

def add_layer(inputs,in_size,out_size,layer_name,activation_function=None):
    # 推荐权重和偏置不为0
    Weights = tf.Variable(tf.random_normal([in_size,out_size]))
    biases = tf.Variable(tf.zeros([1,out_size]) + 0.1)
    Wx_plus_b = tf.matmul(inputs,Weights) + biases

    # 使用dropout功能暂时丢弃一些节点
    Wx_plus_b = tf.nn.dropout(Wx_plus_b,keep_prob)

    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
        # 使用scalar前需要先使用histogram，否者就会报错
        tf.summary.histogram(layer_name+'/outputs',outputs)
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
keep_prob = tf.placeholder(tf.float32)
xs = tf.placeholder(tf.float32,[None,784]) #28*28
ys = tf.placeholder(tf.float32,[None,10])

# 添加一层隐藏层
# 使用tanh时的精度更高
hiddenlayer = add_layer(xs,784,50,layer_name='l1',activation_function=tf.nn.tanh)

# 添加输出层
# 分类的激活函数最好使用softmax
# softmax返回归一化后的概率矩阵
prediction = add_layer(hiddenlayer,50,10,layer_name='l2',activation_function=tf.nn.softmax)

# 交叉熵，预测数值相对于真实值的误差
cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys*tf.log(prediction),reduction_indices=[1]))

tf.summary.scalar('loss',cross_entropy)

train_step = tf.train.GradientDescentOptimizer(0.6).minimize(cross_entropy)

init = tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    # 打包程序中所有的结构
    merged = tf.summary.merge_all()

    train_writer = tf.summary.FileWriter('logs/train',sess.graph)
    test_writer = tf.summary.FileWriter('logs/test',sess.graph)

    sess.run(init)
    for i in range(1000):
        batch_xs,batch_ys = mnist.train.next_batch(1000)
        sess.run(train_step,feed_dict={xs:batch_xs,ys:batch_ys,keep_prob:1})

        if i%50 ==0:
            train_result =sess.run(merged,feed_dict={xs:mnist.train.images,
                                                     ys:mnist.train.labels,
                                                     keep_prob:1})
            test_result = sess.run(merged,feed_dict={xs:mnist.test.images,
                                                     ys:mnist.test.labels,
                                                     keep_prob:1})

            train_writer.add_summary(train_result,i)
            test_writer.add_summary(test_result,i)


