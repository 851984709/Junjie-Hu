def MyFirstFunction():
    print('这是我写的第一个函数')

def MyName(name):
    print('名字：' + name)
# 字符串做输入参数

def add(num1, num2):
    result = num1 + num2
    print(result)
# 数值和字符串做输入参数皆可

def add2(num1, num2):
    return num1 + num2
# 返回结果

#--------------------------形参、实参、函数文档--------------------------------#

def FunDoc(name):
    '函数定义过程中的name是形参' #这一行是函数文档
    #因为它只是一个形式，表示占据一个参数位置
    print('传递进来的' + name + '叫做实参，因为它是具体的参数值')

# 函数文档：函数第一行的文字,类似于Matlab的帮助行

FunDoc.__doc__
help(FunDoc)
# 调用函数的帮助文档

#------------------------------关键字参数--------------------------------------#

def SaySome(name, words):
    print(name + " says '" + words + "'.")

SaySome('He', 'Fuck you ``')
# 正常情况
SaySome('Fuck you ``','He')
# 参数位置改变，输出结果改变
SaySome(name = 'He',words = 'Fuck you ``')
# 使用关键字参数，输出指定结果

#-------------------------------默认参数---------------------------------------#

def SaySome(name = 'She', words = 'I love you !'):
    print(name + " says '" + words + "'.")

SaySome()
# 不传递参数，函数使用默认参数执行
SaySome('He', 'Fuck you ``')
# 传递参数，函数使用传递的参数执行

#-------------------------------收集参数---------------------------------------#

def Test(*params):
    print('参数的长度是：', len(params))
    print('第二个参数是：', params[1])
# Python将标志为收集参数的元素用一个元祖收集起来

def Test(exp, *params):
    print('收集参数的长度是：', len(params))
    print('第二个参数是：', params[1])
    print('定制参数是：', exp)

# 如果收集参数后面还要加上其他定制的参数，应当使用关键字参数
# 关键字参数与收集参数的位置应当一一对应

#------------------------------函数返回值--------------------------------------#

def Hello():
    print('Hello')

temp = Hello()
print(temp)
type(temp)

# Python的默认返回值为None，类型为NoneType

def back():
    return [1,'哈哈哈', 3.14]
# 但会一个列表

def back():
    return 1,'哈哈哈', 3.14
# 返回一个元祖，可以用这种方法返回多个返回值
