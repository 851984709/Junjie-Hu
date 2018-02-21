import tensorflow as tf
import os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

input1 = tf.constant(3.0)
input2 = tf.constant(2.0)
input3 = tf.constant(5.0)

add = tf.add(input2,input3)
mul = tf.multiply(input1,add)

with tf.Session(config=config) as sess:
    # fetch：使用[]将多个op框起来，就可以同时运行多个op，并返回对应的多个结果组成的列表
    result = sess.run([mul,add])
    print(result)
