import tensorflow as tf
import numpy as np
import os
from PIL import Image

def read_and_decode(filename):
    # 根据文件名生成一个队列
    filename_queue = tf.train.string_input_producer([filename])

    # create a reader from file queue
    reader = tf.TFRecordReader()
    _, serialized_example = reader.read(filename_queue)  # 返回文件名和文件
    features = tf.parse_single_example(serialized_example,
                                       features={
                                           'image': tf.FixedLenFeature([], tf.string),
                                           'label': tf.FixedLenFeature([], tf.string)
                                       })

    image = tf.decode_raw(features['image'], tf.float32)
    image_queue = tf.reshape(image, [200 , 200, 3])
    label = tf.decode_raw(features['label'],tf.uint8)
    label = tf.cast(label,tf.float32)
    label_queue = tf.reshape(label,[2])

    return image_queue,label_queue

def get_batch(image_queue,label_queue,batch_size,capacity,min_after_dequeue):
    image_batch, label_batch = tf.train.shuffle_batch([image_queue, label_queue],
                                                      batch_size=batch_size, capacity=capacity,
                                                      min_after_dequeue=min_after_dequeue)
    return image_batch,label_batch