import numpy as np

# array索引

# 一、一维数组索引,numpy从0开始索引
a = np.arange(3,15)
print(a[2]) # a数组中索引为2的数

# 二、矩阵
a = np.arange(3,15).reshape((3,4))
# 1、a矩阵中的第二行、第二列的数
print(a[2][2])
print(a[2,2])
# 2、切片索引
print(a[1][1:3])
# 3、遍历矩阵中的每一行
for row in a:
    print(row)
# 4、遍历矩阵中的每一列
for col in a.T:
    print(col)
# 5、遍历矩阵中的每一项
for item in a.flat:
    print(item)
