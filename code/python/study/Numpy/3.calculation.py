import numpy as np

# numpy运算

# 一、数列运算
# 数列运算支持两个数组形状相同，或者其中一个为一维数组
a = np.array([1,2,3,4])
b = np.array([10,20,30,40])
c = np.array(4)
# 1、加，减、乘、除
add = a + b
minus = b - c
multiply = b * c
divide = a / c
# 2、幂运算
power = b**c
# 3、三角运算
sin = np.sin(a)
cos = np.cos(b)
tan = np.tan(c)
# 4、条件判断,返回由True和False构成的array
judge = a > 2

# 二、矩阵运算
a = np.array([[1,1],
              [0,1]])
b = np.arange(1,5).reshape((2,2))
# 1、加、减、点乘、除，需要保证参数矩阵尺寸相同
add = a + b
minus = a - b
mutiply = a * b
matmul = np.matmul(a,b)
divide = a / b
# 2、叉乘
dot = np.dot(a,b)
# 2、转置
transpose = np.transpose(b)

# 补充：数列和矩阵中的乘法
# 一、数列：
#   由于数列属于一维数组，在进行乘法操作时，需要保证被乘数列的尺寸相同，且对应位相乘
s1 = np.array([1,2,3])
s2 = np.array([1,1,0])
# 1、使用 *，返回与输入数列尺寸相同的数列
mutiply1 = s1*s2
# 2、使用multiply，返回同上
mutiply2 = np.multiply(s1,s2)
# 3、使用dot，返回一个标量
mytiply3 = np.dot(s1,s2)
# 二、矩阵：
# 矩阵的乘法包括点乘和叉乘
m1 = np.array([[1,2,3],
              [4,5,6]])

m2 = np.array([[1,1,1],
               [0,0,0]])

m3 = np.array([[1],
              [1],
              [0]])

# 1、点乘，要求被乘矩阵尺寸相同，返回一个相同尺寸的矩阵
dotmutiply1 = m1*m2
dotmutiply2 = np.multiply(m1,m2)
# 2、叉乘，要求被乘矩阵1的列数与被乘矩阵2的行数相同，返回的矩阵行数与被乘矩阵1的行数相同，列数与被乘矩阵2的列数相同
crossmutiply = np.dot(m1,m3)

# 注意：numpy中矩阵点乘和叉乘的函数名起得特别奇怪，明明是叉乘，却叫dot，注意使用时要不要用错了

# 三、其他矩阵运算
a = np.array([[3,9,2],
              [7,5,1],
              [8,4,6]])
# 1、矩阵取值，返回矩阵中需要的目标值
sum = np.sum(a) # 和
max = np.max(a) # 最大值
min = np.min(a) # 最小值
mean = np.mean(a) # 平均值
median = np.median(a) # 中值
# 2、矩阵行、列取值，axis=1为行取值，axis=0为列取值，返回一维数组
sum_row = np.sum(a,axis=1)
max_row = np.max(a,axis=1)
min_col = np.min(a,axis=0)
# 3、获取索引
max_index = np.argmax(a)
min_index = np.argmin(a)
# 4、累加求和
cumsum = np.cumsum(a)
# 5、逐项求差，按行求每两个数之间的差
diff = np.diff(a)
# 6、查找非零数,返回分别代表非零数行和列的索引的两个一维矩阵
np.nonzero(a)
# 7、排序
sort = np.sort(a)
# 8、截取矩阵，将指定范围外的数字变为边界数字
clip = np.clip(a,2,5)

