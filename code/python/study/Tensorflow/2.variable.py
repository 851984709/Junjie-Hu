import tensorflow as tf
import os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

# 创建一个变量，初始化为0，变量的名字为counter
# tensorflow只有定义一个数据是变量，它才是变量
state = tf.Variable(0,name='counter')
# 创建一个常量
one = tf.constant(1)
# 创建一个使state加1的op
new_value = tf.add(state,one)
# 赋值op，在tensorflow中无法使用=来进行赋值
update = tf.assign(state,new_value)
# 初始化所有变量
# tensorflow中所有的变量都需要初始化
init = tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    sess.run(init)
    print(sess.run(state))
    for _ in range(5):
        sess.run(update)
        print(sess.run(state))
