def odd(x):
    return x % 2
temp = range(10)
show = filter(odd, temp)
list(show)

# 程序的功能为返回从0到9的奇数
# filter为过滤函数，它的第一个参数是函数,第二个参数为列表或元祖
# filter函数返回参数二中所有的能在第一个参数的作用下返回true的元素形成的列表

list(filter(lambda x : x % 2, range(10)))
# filter函数和lambda语句结合使用
