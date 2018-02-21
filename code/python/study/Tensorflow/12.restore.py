import tensorflow as tf
import  os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

# restore variable
# redefine the same shape and same type for your variables
W = tf.Variable(tf.zeros([2,3]),dtype=tf.float32,name='weight')
b = tf.Variable(tf.zeros([1,3]),dtype=tf.float32,name='biases')

# not need init step
saver = tf.train.Saver()
with tf.Session() as sess:
    saver.restore(sess,'my_net/save_net.ckpt')
    print('weight:',sess.run(W))
    print('biases:',sess.run(b))
