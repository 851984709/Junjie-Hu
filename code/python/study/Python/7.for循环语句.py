string = 'string'
for i in string:  #遍历in后面的数组
    print(i)      #使用print每次都会换行

member = ['你好','谢谢','再见']
for each in member:
    print(each,len(each))

range(0,5)     #生成从0到5，但不包括5的数组
range(5)       #同上 range 默认从零开始,差为1
range(0,10,2)  #生成从0到10，差为2，不包括10的数组

for i in range(2,5):
    print(i)
