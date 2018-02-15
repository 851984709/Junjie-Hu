def fun1():
    print("fun1()正在被调用。")
    def fun2():
        print("fun2()正在被调用。")
    fun2()
# Python支持内嵌函数

fun2()
# 程序出错。在函数内部定义的函数无法再函数外部被调用

def fun1(x):
    def fun2():
        print(x)
    fun2()
# 内嵌函数可以调用被嵌函数的变量（此时x属于外部变量）

#-------------------------------------闭包-------------------------------------#
    
def funx(x):
    def funy(y):
        return x * y
    return funy

i = funx(2)
type(i)
i(5)
funx(4)(3)
# i的类型为函数，类似于c语言中的函数指针

funy(6)
# 程序出错，无法在外部函数的外面对内部函数进行调用

def fun1():
    x = 5
    def fun2():
        x *= x
        return x
    return fun2()
# 程序报错，内部函数只能访问外部变量，不能改变外部变量

def fun1():
    x = 5
    def fun2():
        nonlocal x
        x *= x
        return x
    return fun2()
# 使用nonlocal后，就可以对外部变量进行修改
