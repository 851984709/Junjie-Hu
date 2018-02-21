import tensorflow as tf
import os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

# 创建占位符
input1 = tf.placeholder(tf.float32)
input2 = tf.placeholder(tf.float32)
output = tf.multiply(input1,input2)

with tf.Session(config=config) as sess:
    # feed：先使用占位符定义所需op，在run时，使用feed方法传参，数据以字典的形式传入
    print(sess.run(output,feed_dict={input1:[7.0],input2:[2.0]}))
