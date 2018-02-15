class Turtle:#Python中类名约定以大写字母开头
    #属性
    color = 'green'
    weight = 10
    legs = 4
    shell = True
    mouth = '大嘴'

    #方法
    #在class定义的函数叫方法
    def climb(self):
        print('我正在很努力地向前爬......')

    def run(self):
        print('我正在飞快地向前跑......')

    def bite(self):
        print('咬死你咬死你！！')

    def eat(self):
        print('有得吃，真满足^_^')

    def sleep(self):
        print('困了，睡了，晚安，Zzzz')

#-------------------------------------继承-------------------------------------#

class Kidturtle(Turtle):
    pass
# 让Kidturtle继承Turtle的属性和方法
# pass语句什么也不做，一般作为占位符或者创建占位程序，pass语句不会执行任何操作

#-------------------------------------多态-------------------------------------#

class A:
    def fun(self):
        print('我是A')

class B:
    def fun(self):
        print('我是B')

a = A()
b = B()
a.fun()
b.fun()
# 类A和类B可以使用相同的函数名定义函数，但是它们之间的功能互不影响

#-------------------------------------self-------------------------------------#

class Ball1:
    def setName(self, name):
        self.name = name
    def kick(self):
        print('我叫%s，该死的，谁踢我....' % self.name)

a = Ball1()
a.setName('球A')
print(a.name)
a.kick()
# Python的self指的是类实例对象本身（不是类本身）
# self类似于C++中类的this指针
# self只有在类的方法中才会有，独立的函数或方法是不比带有self的
# self应该放在第一个参数的位置上

class Ball2:
    def fun():
        print('fun')

b = Ball2()
b.fun
# self在定义类的方法是时必须的，虽然在调用时不必传入参数
# 如果函数没有使用self参数，在调用该函数是会出错

class Ball3:
    def setname(this,name):
        this.name = name
    def putname(this):
        print(this.name)

c = Ball3()
c.setname('球C')
c.putname()
# self的名称不是必须的，在Python中self不是关键词，它可以被定义成a或b或其他名字，
# 但是约定俗成，最好定义成self

#-----------------------------------构造函数-----------------------------------#

class Ball4:
    def __init__(self,name):
        self.name = name
    def kick(self):
        print('我叫%s，该死的，谁踢我....' % self.name)
d = Ball4('球D')
d.kick()
# __init__函数为Python中的实例初始化函数，类似于C++中的构造函数
# 当对象被创建时，程序就会自动调用__init__函数来对该对象进行初始化

#----------------------------------公有与私有----------------------------------#

class Person:
    name = 'name'
p = Person()
p.name
# 此时name为公有，可以在外部访问

class Person:
    __name = 'name'
q = Person()
q.__name
# 此时__name为私有，无法在外部被访问
# Python中只要在变量名或函数名前加上'__'两个下划线，这个函数或变量就变成私有的了

class Person:
    __name = 'name'
    def getName(self):
        return self.__name
r = Person()
r.getName()

class Person:
    __name = 'name'
    def putName(self):
        print(self.__name)
s = Person()
s.putName()
# 私有变量可以在对象内部被访问

s._Person__name
# 对象名._类名__私有变量名
# 通过这种方法可以调用名字为__name的私有成员变量
# Python的私有机制其实是伪私有，它的类是没有权限控制的
# 原理：Python会将带有'__'的变量名修改为‘对象名._类名__私有变量名’的形式，从而
#       使得外部访问变量时出错
