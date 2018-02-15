import numpy as np

# 生成array
# 一、初始化array的的dtype
# numpy有自己特有的数据类型，如：bool,int,uint,float,complex。后面加上数据类型的位数
a = np.array([1,2,3],dtype=np.int32)
print("dtype: ",a.dtype)

# 二、生成特殊矩阵
#   1、零矩阵
zeros = np.zeros((3,4)) # shape的参数为元组
#   2、一矩阵
ones = np.ones((2,6))
#   3、空矩阵（非常接近于零的数字）
empty = np.empty((2,2))

# 三、用arange和reshape配合生成矩阵
arange = np.arange(10,20).reshape((2,5))

# 四、用linspace生成均匀分布的矩阵
linspace = np.linspace(2,5,5)

# 五、用random模块的random函数生成(0~1)之间的随机矩阵
random = np.random.random((2,2))
