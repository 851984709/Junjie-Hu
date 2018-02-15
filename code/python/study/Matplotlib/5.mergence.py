import numpy as np

# array合并
a = np.array([1,2,3])
b = np.array([4,5,6])

# 一、方法一
# 1、垂直合并 vertical stack
vertical_1 = np.vstack((a,b))
# 2、水平合并 horizontal stack
# 如果参数都为数列，返回数列
# 如果参数为矩阵，返回矩阵
horizontal_1 = np.hstack((a,b,a))

# 二、方法二
a = a[np.newaxis,:]
b = b[np.newaxis,:]
# 1、垂直合并
vertical_2 = np.concatenate((a,b),axis=0)
# 2、水平合并
horizontal_2 = np.concatenate((a,b),axis=1)

# 注意：
# 在进行数组的合并操作时，需要保证参数数组的尺寸对应

# 补充知识点
a = np.array([1,2,3])
# 一维数组，即数列，无法使用转置(transpose)来使其变成纵向的矩阵
# 需要使用以下方法进行变换
# 1、reshape
b = a.reshape((3,1))
# 2、newaxis
c = a[np.newaxis,:] # 在水平方向增加一个维度
d = a[:,np.newaxis] # 在垂直方向增加一个维度
