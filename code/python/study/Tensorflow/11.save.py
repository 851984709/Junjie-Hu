import tensorflow as tf
import numpy as np
import  os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

# Save to file
W = tf.Variable([[1,2,3],[3,4,5]],dtype=tf.float32,name='weight')
b = tf.Variable([[1,2,3]],dtype=tf.float32,name='biases')

init = tf.global_variables_initializer()

saver = tf.train.Saver()

with tf.Session() as sess:
    sess.run(init)
    save_path = saver.save(sess,'my_net/save_net.ckpt')
    print('Save to path:',save_path)
