import tensorflow as tf
import numpy as np
import os
import model
import getdata

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
# 该程序差不多需要2600M的显存
config=tf.ConfigProto(gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.6))

# 定义各种变量
train_size = 16
test_size = 400

# 定义占位符
image_placeholder = tf.placeholder(tf.float32, [None, 200,200,3])  # 100*100
label_placeholder = tf.placeholder(tf.float32, [None, 2])

# 获取训练数据和测试数据
with tf.name_scope('data_queue'):
    image_queue, label_queue = getdata.read_and_decode('data')
with tf.name_scope('data_train'):
    image_train, label_train = getdata.get_batch(
        image_queue, label_queue, train_size, capacity=100, min_after_dequeue=50)
with tf.name_scope('data_test'):
    image_test, label_test = getdata.get_batch(
        image_queue, label_queue, test_size, capacity=500, min_after_dequeue=50)

# 构建神经网络
pretiction = model.get_prediction(image_placeholder)
train_step = model.get_train_step(pretiction,label_placeholder)
accuracy = model.get_accuracy(pretiction,label_placeholder)

# 创建保存器
saver = tf.train.Saver()

init = tf.global_variables_initializer()

with tf.Session(config=config) as sess:
    sess.run(init)
    # 开启训练批队列进程
    threads = tf.train.start_queue_runners(sess=sess)
    # 打包程序中所有的结构
    merged = tf.summary.merge_all()
    # 创建tensorboard文件
    writer = tf.summary.FileWriter('logs/', sess.graph)  # 'logs/'为目标event文件路径

    for i in range(10000):
        image,label = sess.run([image_train,label_train])
        sess.run(train_step,
                 feed_dict={image_placeholder:image,label_placeholder:label})

        if i % 1000 == 0:
            # 每1000步保存一次神经网络参数
            saver.save(sess, 'cnn_save/cnn_save.ckpt')

        if i % 500 == 0:
            # 显示精度
            image,label = sess.run([image_test,label_test])
            print(sess.run(accuracy,
                           feed_dict={image_placeholder:image,label_placeholder:label}))

        if i % 5 == 0:
            # merged操作也需要被run
            result = sess.run(merged)
            writer.add_summary(result, i)