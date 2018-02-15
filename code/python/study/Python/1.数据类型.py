print("\t\t\t\twhile循环语句")
temp = input("3+4=?\n")
answer = int(temp)
while answer != 7:
    if answer > 7:
        print("大了")
    else :
        print("小了")
    temp = input("算错了，请重新输入\n")
    answer = int(temp)
print("正确")


# Python的数据类型分为：整形，浮点型，e型，字符串型等等

# 整数、字符串、浮点数可以通过：int()、str()、float()进行转换

# type()可以用来判断传入参数的类型
# 如：type(1)    int
#     type(1.1)  float
#     type('1')  str
#     type(True) bool
#     type(int)  type

# isinstance()也可以判断传入参数的类型
# 例如：isinstance(1,int)   True
#       isinstance(1,float) False
