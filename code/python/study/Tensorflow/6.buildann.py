import tensorflow as tf
import  numpy as np
import matplotlib.pyplot as plt
import os

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

x_data = np.linspace(-1,1,300)[:,np.newaxis]
# [:,np.newaxis]在列上添加一个维度，生成一个300行，1列的矩阵
noise = np.random.normal(0,0.05,x_data.shape)
y_data = np.square(x_data) - 0.5 + noise

fig = plt.figure()
# 绘图最好在axis上绘制，方便随后调用
ax = fig.gca()
ax.scatter(x_data,y_data)

plt.ion()
plt.show()

# 创建类型为float，行数不限，列数为一的占位符
xs = tf.placeholder(tf.float32,[None,1])
ys = tf.placeholder(tf.float32,[None,1])

# 隐藏层
l1 = add_layer(xs,1,10,activation_function=tf.nn.relu)
# 输出层
prediction = add_layer(l1,10,1,activation_function=None)

loss = tf.reduce_mean(tf.reduce_sum(tf.square(ys - prediction),reduction_indices=[1]))

train_step = tf.train.GradientDescentOptimizer(0.1).minimize(loss)

init =tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    sess.run(init)
    for i in range(1000):
        sess.run(train_step,feed_dict={xs:x_data,ys:y_data})
        if i%50 == 0:
            prediction_value = sess.run(prediction,feed_dict={xs:x_data})
            # 可视化
            try:
                ax.lines.remove(lines[0])
            except Exception:
                pass
            lines = ax.plot(x_data,prediction_value,'r-',lw=5)
            plt.pause(0.1)

