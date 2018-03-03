import tensorflow as tf
import numpy as np
import os
import getdata

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
config=tf.ConfigProto(gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.6))

def add_layer(inputs, in_size, out_size, activation_function=None):
    # 推荐权重和偏置不为0
    Weights = tf.Variable(tf.random_normal([in_size, out_size]))
    biases = tf.Variable(tf.zeros([1, out_size]) + 0.1)
    Wx_plus_b = tf.matmul(inputs, Weights) + biases
    if activation_function is None:
        outputs = Wx_plus_b
    else:
        outputs = activation_function(Wx_plus_b)
    return outputs

def compute_accuracy(v_xs, v_ys):
    global prediction
    y_pre = sess.run(prediction, feed_dict={xs: v_xs, keep_prob: 1})
    correct_prediction = tf.equal(tf.argmax(y_pre, 1),
                                  tf.argmax(v_ys, axis=1))  # tf.argmax和np.argmax一样
    accuracy = tf.reduce_mean(
        tf.cast(correct_prediction, tf.float32))  # cast：投射，将bool类型的数据转化为float
    result = sess.run(accuracy, feed_dict={xs: v_xs, ys: v_ys, keep_prob: 1})
    return result


def weight_variable(shape):
    inital = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(inital)


def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)


def conv2d(x, W):  # x为图片的全部信息，W为权重
    # strides [1,x_movement,y_movement,1]
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

def max_pool_5x5(x):
    return tf.nn.max_pool(x, ksize=[1, 5, 5, 1], strides=[1, 5, 5, 1], padding='SAME')

# 定义占位符
keep_prob = tf.placeholder(tf.float32)
xs = tf.placeholder(tf.float32, [None, 200,200,3])  # 100*100
ys = tf.placeholder(tf.float32, [None, 2])

with tf.name_scope('Conv'):
    with tf.name_scope('conv1'):
        # conv1 layer
        W_conv1 = weight_variable([3, 3, 3, 16])  # in_size：3*3*3 out_size：1*1*16 16为卷积核个数
        b_conv1 = bias_variable([16])
        h_conv1 = tf.nn.relu(conv2d(xs, W_conv1) + b_conv1)  # out_size 200*200*16
        h_pool1 = max_pool_2x2(h_conv1)  # out_size 100*100*16
    with tf.name_scope('conv2'):
        # conv2 layer
        W_conv2 = weight_variable([3, 3, 16, 32])  # in_size：3*3*16 out_size：1*1*32
        b_conv2 = bias_variable([32])
        h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)  # out_size 100*100*32
        h_pool2 = max_pool_2x2(h_conv2)  # out_size 50*50*32
with tf.name_scope('Full'):
    with tf.name_scope('fun1'):
        # func1 layer 全连接
        W_fc1 = weight_variable([50 * 50 * 32, 32])
        b_fc1 = bias_variable([32])
        h_pool2_flat = tf.reshape(h_pool2, [-1, 50 * 50 * 32])
        h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)  # out_size 64
    with tf.name_scope('func2'):
        # func2 layer 全连接
        W_fc2 = weight_variable([32, 8])
        b_fc2 = bias_variable([8])
        h_fc2 = tf.nn.relu(tf.matmul(h_fc1, W_fc2) + b_fc2)
        h_fc2_drop = tf.nn.dropout(h_fc2, keep_prob)
    with tf.name_scope('func3'):
        # func3 layer 全连接
        W_fc3 = weight_variable([8, 2])
        b_fc3 = bias_variable([2])
        prediction = tf.nn.softmax(tf.matmul(h_fc2_drop, W_fc3) + b_fc3)
with tf.name_scope('train_step'):
    cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys * tf.log(prediction), reduction_indices=[1]))

    train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

# 获取训练数据
train_size = 16
test_size = 400

with tf.name_scope('data_queue'):
    # 根据文件名生成一个队列
    filename_queue = tf.train.string_input_producer(['data'])

    # create a reader from file queue
    reader = tf.TFRecordReader()
    _, serialized_example = reader.read(filename_queue)  # 返回文件名和文件
    features = tf.parse_single_example(serialized_example,
                                       features={
                                           'image': tf.FixedLenFeature([], tf.string),
                                           'label': tf.FixedLenFeature([], tf.string)
                                       })

    image = tf.decode_raw(features['image'], tf.float32)
    image = tf.reshape(image, [200, 200, 3])
    label = tf.decode_raw(features['label'], tf.uint8)
    label = tf.cast(label, tf.float32)
    label = tf.reshape(label, [2])
with tf.name_scope('data_train'):
    image_train, label_train = tf.train.shuffle_batch([image, label],
                                                      batch_size=train_size, capacity=100,
                                                      min_after_dequeue=50)
with tf.name_scope('data_test'):
    image_test, label_test = tf.train.shuffle_batch([image, label],
                                                    batch_size=test_size, capacity=500,
                                                    min_after_dequeue=50)

init = tf.global_variables_initializer()

# 创建保存器
saver = tf.train.Saver()

with tf.Session(config=config) as sess:
    sess.run(init)
    # 开启训练批队列进程
    threads = tf.train.start_queue_runners(sess=sess)

    # 打包程序中所有的结构
    merged = tf.summary.merge_all()
    # 创建tensorboard文件
    writer = tf.summary.FileWriter('logs/', sess.graph)  # 'logs/'为目标event文件路径

    for i in range(10000):
        train_xs, train_ys = sess.run([image_train,label_train])

        sess.run(train_step, feed_dict={xs: train_xs, ys: train_ys, keep_prob: 0.5})

        if i % 1000 == 0:
            # 每1000步保存一次神经网络参数
            saver.save(sess, 'cnn_save/cnn_save.ckpt')

        if i % 500 == 0:
            # 显示精度
            test_xs,test_ys = sess.run([image_test,label_test])
            print(compute_accuracy(train_xs, train_ys))

        if i % 5 == 0:
            # merged操作也需要被run
            result = sess.run(merged)
            writer.add_summary(result, i)