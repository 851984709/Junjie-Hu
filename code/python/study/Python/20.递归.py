def fun(n):
    if n == 1 :
        return 1
    else :
        return n * fun(x - 1)

import sys
sys.setrecursionlimit(100)
# 该模块可以设置递归的深度

#-------------------------斐波那契（fibonacci）数列----------------------------#

def Fib(n):
    if n == 1 or n == 2:
        return 1
    else :
        return Fib(n - 1) + Fib(n - 2)
# 生成斐波那契数列的第n个数

def FibList(n):
    string = [1]
    if n == 1:
        return string
    else :
        string = FibList(n - 1)
        string.append(Fib(n))
        return string
# 生成含有n个数的斐波那契数列
