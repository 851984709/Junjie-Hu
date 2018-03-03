import matplotlib.pyplot as plt
import tensorflow as tf
import numpy as np
from PIL import Image
import os

# 设定各种环境变量
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
os.environ['CUDA_VISIBLE_DEVICES'] = '0'

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
    image_bytes = image_dst_array.tobytes()

    return image_bytes

def getpathnames():
    # 获取目标路径
    # pathname = '/home/junjie/图片/CatandDog'
    pathname = input('Please input target path containing the resources of cats and dogs: ')
    dataname = input('Please input the target data filename: ')

    print('Maybe you will wait a munite untill the process finished.')

    # 如果获取文件夹路径异常，就报错
    if pathname is '':
        print('Pathname error!')
        os._exit()

    # 判断目标文件夹是否包含猫和狗的文件夹
    folderlist = os.listdir(pathname)

    if 'cat' not in folderlist:
        print("The folder dosn't contain folder 'cat'!")
        os._exit()
    if 'dog' not in folderlist:
        print("The folder dosn't contain folder 'dog'!")
        os._exit()

    cat_pathname = pathname + '/' + 'cat'
    dog_pathname = pathname + '/' + 'dog'

    return cat_pathname,dog_pathname,dataname

# 获取文件名和文件路径名
cat_pathname,dog_pathname,dataname = getpathnames()

cat_filenamelist = os.listdir(cat_pathname)
dog_filenamelist = os.listdir(dog_pathname)

cat_number = len(cat_filenamelist)
dog_number = len(dog_filenamelist)

c_int = 0
d_int = 0

writer = tf.python_io.TFRecordWriter(dataname)

while (c_int < cat_number) and (d_int < dog_number):
    randn = np.random.randint(0,2)
    if randn == 0:
        image_jpg = Image.open(cat_pathname+'/'+cat_filenamelist[c_int])
        # 标准化/////////////////////
        image_bytes = imagenormalize(image_jpg)
        # 猫的标签为[1,0]
        label_bytes = np.array([1,0],dtype=np.uint8).tobytes()
        example = tf.train.Example(
            features=tf.train.Features(
                feature={'image':
                             tf.train.Feature(bytes_list=tf.train.BytesList(value=[image_bytes])),
                         'label':
                             tf.train.Feature(bytes_list=tf.train.BytesList(value=[label_bytes]))}))

        writer.write(example.SerializeToString())  # 序列化为字符串
        c_int += 1

    elif randn == 1:
        image_jpg = Image.open(dog_pathname + '/' + dog_filenamelist[d_int])
        # 标准化
        image_bytes = imagenormalize(image_jpg)
        # 狗的标签为[0,1]
        label_bytes = np.array([0, 1],dtype=np.uint8).tobytes()
        example = tf.train.Example(
            features=tf.train.Features(
                feature={'image':
                             tf.train.Feature(bytes_list=tf.train.BytesList(value=[image_bytes])),
                         'label':
                             tf.train.Feature(bytes_list=tf.train.BytesList(value=[label_bytes]))}))

        writer.write(example.SerializeToString())  # 序列化为字符串
        d_int += 1

writer.close()