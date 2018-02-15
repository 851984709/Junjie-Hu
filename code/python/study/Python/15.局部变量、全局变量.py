def discounts(price, rate):
    final_price = price * rate
# 这里的price和rate是局部变量
    return final_price

old_price = float(input('请输入原价：'))
rate      = float(input('请输入折扣率：'))
new_price = discounts(old_price, rate)
# old_price、rate和new_price为全局变量
print('打折后的价格是：', new_price)

#------------------------------------------------------------------------------#

def discounts(price, rate):
    final_price = price * rate
# 这里的price和rate是局部变量
    return final_price

old_price = float(input('请输入原价：'))
rate      = float(input('请输入折扣率：'))
new_price = discounts(old_price, rate)
# old_price、rate和new_price为全局变量
print('打折后的价格是：', new_price)
print('局部变量price的值是：', price)
# 这里试图访问局部变量price的值，程序会报错

#------------------------------------------------------------------------------#

def discounts(price, rate):
    final_price = price * rate
    print('这里试图打印全局变量old_price的值：'，old_price)
# 函数可以访问全局变量的值
    return final_price

old_price = float(input('请输入原价：'))
rate      = float(input('请输入折扣率：'))
new_price = discounts(old_price, rate)
print('打折后的价格是：', new_price)

#------------------------------------------------------------------------------#
def discounts(price, rate):
    final_price = price * rate
    old_price = 50
    return final_price

old_price = float(input('请输入原价：'))
rate      = float(input('请输入折扣率：'))
new_price = discounts(old_price, rate)
#print('修改后old_price的值是：', old_price)
print('打折后的价格是：', new_price)

# 该程序执行后输出的打折后的值任然是正确的值
# Python的函数只能引用全局变量的值，不能改变全局变量的值
# 在引用全局变量时，会生成一个与全局变量相同的局部变量。修改这个同名局部变量的 #
# 值无法改变全局变量的值                                                       #

#------------------------------global关键字------------------------------------#

number = 5
def fun():
    number = 10
fun()
print(number)
# 此时，由于number为全局变量，number的值并未改变

number = 5
def fun(count):
    count = 10
fun(number)
print(number)
# 此时，由于count是形式参数的原因，number的值也不会改变

number = 5
def fun():
    global number
    number = 10
fun()
print(number)
# 加上global关键字后，就可以对全局变量进行修改

print(number)
