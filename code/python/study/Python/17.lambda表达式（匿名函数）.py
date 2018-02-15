def ds(x):
    return 2 * x + 1
ds(5)

ds = lambda x : x * 2 + 1
ds(5)

# 上述两个程序的功能一样
# lambda表达式可以创建匿名函数
# 冒号（:）左边的为参数，冒号右边的为返回值

g = lambda x, y : x + y
g(3,4)
# 两个参数的匿名函数
