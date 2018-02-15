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

# while循环
#
# while 语句:
#   语句
