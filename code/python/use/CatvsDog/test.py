import tensorflow as tf
import numpy as np
import os
import model
import getdata
from PIL import Image

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
config = tf.ConfigProto()
# 该程序差不多需要2600M的显存
config=tf.ConfigProto(gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.6))

# 图像标准化，将输入的图像转化为正方形矩阵
def imagenormalize(image_jpg):
    image_array = np.array(image_jpg)

    # 获取原图的尺寸信息
    height, width = image_array.shape[0],image_array.shape[1]
    # 获取长和宽的最小值
    length = np.min((height, width))

    # 生成目标图片矩阵
    image_square_array = np.zeros((length, length, 3), dtype=np.uint8)  # 一定要指定dtype

    # 将数据转化为整型
    row_origin = int((height - length) / 2)
    col_origin = int((width - length) / 2)

    # 将原始图像贴到方形图片上
    for i in range(0, length):
        for j in range(0, length):
            image_square_array[i][j] = image_array[i + row_origin][j + col_origin].copy()

    # 统一图片大小
    image_scr = Image.fromarray(image_square_array,'RGB')
    image_dst = image_scr.resize((200,200))

    image_dst_array = np.array(image_dst)

    # 将图像矩阵标准化
    mean = np.mean(image_dst_array)
    std = np.std(image_dst_array)
    image_dst_array = (image_dst_array - mean)/std

    # 将数组转化为float32型
    image_dst_array = np.array(image_dst_array,dtype=np.float32)

    return image_dst_array

# 定义各种变量
train_size = 16
test_size = 400

# 定义占位符
image_placeholder = tf.placeholder(tf.float32, [None, 200,200,3])  # 100*100

# 构建神经网络
prediction = model.get_prediction(image_placeholder)

# 创建保存器
saver = tf.train.Saver()

# 导入图片
filepath = input('Please input the path of your image:')

# 加载图片
image_jpg = Image.open(filepath)
image = imagenormalize(image_jpg)
image_input = np.array(image).reshape((1,200,200,3))

with tf.Session(config=config) as sess:
    saver.restore(sess, 'cnn_save/cnn_save.ckpt')

    pre = np.argmax(sess.run(prediction,feed_dict={image_placeholder:image_input})[0])

    if pre == 0:
        print('猫')
    else:
        print('狗')
