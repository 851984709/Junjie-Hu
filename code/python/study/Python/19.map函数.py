def double(x):
    return x * 2
temp = range(10)
show = map(double, temp)
list(show)

# 程序的功能为生成从0到9的数乘2后的列表
# map为映射函数，它的参数类型和filter函数的参数类型一样
# map函数返回参数二中的所有元素在参数一函数的作用下产生的所有元素形成的列表

list(map(lambda x : x * 2, range(10)))
# map函数和lambda语句结合使用
