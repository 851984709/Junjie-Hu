import random                  #导入random模块
secret = random.randint(1,10)  #生成随机数

print("\t\t\t\twhile猜数字")
temp = input("猜猜我在想哪一个数字\n")
answer = int(temp)
while answer != secret:
    if answer > secret:
        print("大了")
    else :
        print("小了")
    temp = input("算错了，请重新输入\n")
    answer = int(temp)
print("正确")
