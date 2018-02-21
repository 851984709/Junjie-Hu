import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config.gpu_options.allow_growth=True

def add_layer(inputs,in_size,out_size,n_layer,activation_function=None):
    layer_name = 'layer%s'%n_layer
    with tf.name_scope('layer'):
        with tf.name_scope('Weights'):
            Weights = tf.Variable(tf.random_normal([in_size,out_size]),name='W')
            # 在tensorboard中创建Weight的柱状图
            tf.summary.histogram(layer_name+'/Weights',Weights)
        with tf.name_scope('biases'):
            biases = tf.Variable(tf.zeros([1,out_size]) + 0.1,name='b')
            tf.summary.histogram(layer_name+'/biases',biases)
        with tf.name_scope('Wx_plus_b'):
            Wx_plus_b = tf.matmul(inputs,Weights) + biases
        if activation_function is None:
            outputs = Wx_plus_b
        else:
            outputs = activation_function(Wx_plus_b)
        tf.summary.histogram(layer_name+'/outputs',outputs)
        return outputs

# 创建输入伪数据
x_data = np.linspace(-1,1,300)[:,np.newaxis]
noise = np.random.normal(0,0.05,x_data.shape)
y_data = np.square(x_data) - 0.5 + noise

with tf.name_scope('inputs'):
    xs = tf.placeholder(tf.float32,[None,1],name='x_input')
    ys = tf.placeholder(tf.float32,[None,1],name='y_input')

l1 = add_layer(xs,1,10,n_layer=1,activation_function=tf.nn.relu)

prediction = add_layer(l1,10,1,n_layer=2,activation_function=None)

with tf.name_scope('loss'):
    loss = tf.reduce_mean(tf.reduce_sum(tf.square(ys - prediction),reduction_indices=[1]))
    # 在tensorboard中创建loss的标量图
    tf.summary.scalar('loss',loss)

with tf.name_scope('train'):
    train_step = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

init =tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    # 打包程序中所有的结构
    merged = tf.summary.merge_all()
    # 创建tensorboard文件
    writer = tf.summary.FileWriter('logs/',sess.graph) # 'logs/'为目标event文件路径

    sess.run(init)
    for i in range(1000):
        sess.run(train_step,feed_dict={xs:x_data,ys:y_data})
        if i%50 == 0:
            # merged操作也需要被run
            result = sess.run(merged,feed_dict={xs:x_data,ys:y_data})
            writer.add_summary(result,i)

# 查看tensorboard视图的方法：
# 1、打开tenminal，cd到logs目录的父目录
# 2、在terminal输入：tensorboard --logdir='logs'，获取网址，这里为http://junjie-Toplap:6006
# 3、用浏览器打开网址即可查看tensorboard视图
# 注意：
# 1、tensorflow为goole开发的module，所以最好使用chrome打开网址，使用其他浏览器可能会出现兼容的问题
# 2、在部分windows系统的电脑上，使用终端获取的网址可能出现一些问题，
#    可以将网址更换为：http://127.0.0.1:6006或http://localhost:6006，即本机IP的6006端口
# 3、由于运行时环境变量的原因，有的电脑使用tensorboard时，
#    需要将los目录放在python编译器（python或python3）的启动目录里
# 4、在使用tensorboard视图时，不能关闭terminal中tensorboard的进程
