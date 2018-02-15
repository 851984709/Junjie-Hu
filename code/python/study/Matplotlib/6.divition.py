import numpy as np

# array分割

# 一、均匀分割
a = np.arange(12).reshape((3,4))
# 1、行分割
[m,n] = np.split(a,2,axis=1)
# 2、列分割
[m,n,o] = np.split(a,3,axis=0)

# 二、大概分割
a = np.arange(15).reshape((3,5))
# 1、行分割
[m,n,o] = np.array_split(a,3,axis=1)
# 2、列分割
[m,n] = np.array_split(a,2,axis=0)

# 三、简单分割
a = np.arange(12).reshape((3,4))
# 1、行分割
[m,n] = np.hsplit(a,2)
# 2、列分割
[m,n,o] = np.vsplit(a,3)
