class Parent:
    def hello(self):
        print('正在调用父类的方法')
    def move(self):
        print('跑')

class Child(Parent):
    pass
# 在被定义的类名后加上"(需要继承的父类名)"来继承父类的属性和方法

class Child2(Parent):
    def move(self):
        print('爬')
# 如果子类中定义与父类同名的方法或属性，则会自动覆盖父类对应的方法或属性

import random as r

class Fish:
    def __init__(self):
        self.x = r.randint(0,10)
        self.y = r.randint(0,10)
    def move(self):
        print('我的位置是：%d, %d' % (self.x, self.y))
    
class Shark(Fish):
    def __init__(self):
        self.hungry = True
    def eat(self):
        if self.hungry == True:
            print('我正在吃东西')
            self.hungry = False
        else:
            print('我吃饱了，吃不下了')
            
shark = Shark()
shark.move()
# 如果子类又重新调用了__init__方法，则父类的构造函数将被覆盖，使得程序出错

import random as r

class Fish:
    def __init__(self):
        self.x = r.randint(0,10)
        self.y = r.randint(0,10)
    def move(self):
        print('我的位置是：%d, %d' % (self.x, self.y))
    
class Shark(Fish):
    def __init__(self):
        Fish.__init__(self)
        self.hungry = True
    def eat(self):
        if self.hungry == True:
            print('我正在吃东西')
            self.hungry = False
        else:
            print('我吃饱了，吃不下了')
            
shark = Shark()
shark.move()
# 使用未绑定的父类方法可以继承父类的构造函数
# Fish.__init__(self)语句中的self为子类Shark的实例对象本身（不是父类）

class Fish:
    def __init__(self):
        self.x = r.randint(0,10)
        self.y = r.randint(0,10)
    def move(self):
        print('我的位置是：%d, %d' % (self.x, self.y))
    
class Shark(Fish):
    def __init__(self):
        super().__init__()
        self.hungry = True
    def eat(self):
        if self.hungry == True:
            print('我正在吃东西')
            self.hungry = False
        else:
            print('我吃饱了，吃不下了')
            
shark = Shark()
shark.move()
# super函数可以自动找到基类的方法，而且还会自动传入self参数
# 使用super函数不用给定任何基类的名字，如果有多重继承，它会自动一层一层找出所有
# 基类里面对应的方法

#----------------------------------多重继承------------------------------------#

class Base1:
    def foo1(self):
        print('我是foo1')

class Base2:
    def foo2(self):
        print('我是foo2')

class Kid(Base1,Base2):
    pass

k = Kid()
# Python支持多重继承
# 在被定义的类名后面加上由多个父类构成的元祖来使用多重继承
