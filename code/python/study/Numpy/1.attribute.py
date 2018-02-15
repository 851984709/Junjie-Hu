import numpy as np

# 生成简单的numpy的数组
array = np.array([[1,2,3],
                  [4,5,6]])

# numpy数组的属性
# 一、打印数组
print(array)
# 二、数组的维度
print("number of dim:", array.ndim)
# 三、数组的形状（长,宽）
print("shape:", array.shape)
# 四、数组的尺寸（元素的个数）
print("size:",array.size)