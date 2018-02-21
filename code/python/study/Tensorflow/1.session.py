import tensorflow as tf
import os

# 设定各种环境变量
# 忽略烦人的警告
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
# 在Python代码中指定GPU
os.environ['CUDA_VISIBLE_DEVICES'] = "0"
# 设置定量的GPU使用量
config=tf.ConfigProto(gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.3)) # 占用GPU30%的显存

# 创建一个常量operation
m1 = tf.constant([[3,3]])
# 创建一个常量op
m2 = tf.constant([[2],[3]])
# 创建一个矩阵乘法op，把m1和m2传入
product = tf.matmul(m1,m2)

# 定义一个会话，启动默认的图
# 方法一：
sess = tf.Session(config=config) # Session为一个Object，需要被大写
result = sess.run(product)
print(result)
sess.close()

# 方法二：
with tf.Session(config=config) as sess: # 使用with方法就不需要手动关闭session
    # 调用sess的run方法来执行矩阵乘法op
    # run(product)触发了图中3个op
    result = sess.run(product)
    print(result)

# 知识点：
# tensorflow对数据的各种操作都只是定义了对应该操作的结构，只有run以后，程序才会执行该操作。
# 这是tensorflow的思考模式。

# 注意：
# 这里讲的主要是使用tensorflow-gpu的一些注意事项
# 一、在我的这台电脑上，我只安装了tensorflow的gpu版，在不加“os.environ['CUDA_VISIBLE_DEVICES'] = "0"”这句话时，电脑也是使用gpu进行运算的。可能在同时安装了cpu和gpu版本的电脑上需要使用这句话来设置为gpu版，所以我在该系列学习笔记中统一保留这句话。
# 二、tensorflow默认在使用时会占用全部的gpu，设置gpu占用率的方法：
#	1、config = tf.ConfigProto()
#	   config.gpu_options.per_process_gpu_memory_fraction = 0.3
#	2、config=tf.ConfigProto(gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.3))
# 三、这是我觉得配置gpu运算时最最坑大的一点：
#	在tensorflow前一部分的学习中，都没有遇到较大的问题，但是在使用cnn时，我的程序弹出了：
#		E tensorflow/stream_executor/cuda/cuda_dnn.cc:385] could not create cudnn handle: CUDNN_STATUS_INTERNAL_ERROR
#		E tensorflow/stream_executor/cuda/cuda_dnn.cc:352] could not destroy cudnn handle: CUDNN_STATUS_BAD_PARAM
#		F tensorflow/core/kernels/conv_ops.cc:717]
#                Check failed: stream->parent()->GetConvolveAlgorithms(
#                conv_parameters.ShouldIncludeWinogradNonfusedAlgo<T>(), &algorithms)
#	于是我就根据这个错误在网上寻找错误发生的原因，网上大多数的解释都是，cuda和cudnn的版本不兼容（我的cuda版本为9.0,
# cudnn版本为cudnn7.0.4,tensorflow1.5），为此我前后重新配置tensorflow-cuda-cudnn不下十余次,前后差不多耗时5天
# ，都没有解决问题，最后我发现原来是由于我设置的占用参数太大。如果申请0.9的gpu内存，由于其他的应用也会占用gpu内存，
# 理所当然的会申请失败，这也在只能说我太粗心了。同样的，申请的内存也不能太小，否则又会达不到想要训练的神经网络的要求，
# 所以应当合理设置内存占用参数。
#	为了方便起见，我在后面的内存设置上统一使用：config.gpu_options.allow_growth=True，让程序自己合理申请内存，
# 免去手动设置的麻烦

# 小技巧：
#	1、产看gpu使用情况：nvidia-smi
#	2、事实查看gpu使用情况：nvidia-smi -l






















