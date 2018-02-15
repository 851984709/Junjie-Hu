first   = 'Hello World!'
#单引号和双引号都可以，但是要对应

second  = '1\n2'
third   = '123\\n'
forth   = r'123\n'
#字符串前加r表示原始字符串，原始字符串结尾不能加\

fifth   = """123"""
sixth   = '他说：“你好”'
seventh = 'He said "Hello"' 
eighth  = "'单引号'"
#如果在Python用单号那么在字符串中就可以直接收写双引号了，反之亦然

ninth   = '''"双引号"和'单引号'\n'单引号'和"双引号"'''
#三引号的形式用来输入多行文本，也就是说在三引号之间输入的内容将被
#原样保留，之中的单号和双引号不用转义，其中的不可见字符比如/n和/t
#都会被保留，这样的好处是你可以替换一些多行的文本。

print('first:',   first)
print('second:',  second)
print('third:',   third)
print('forth:',   forth)
print('fifth:',   fifth)
print('sixth:',   sixth)
print('seventh:', seventh)
print('eighth:',  eighth)
print('ninth:',   ninth)

'123' + '456'
# 字符串的加法即将两个字符串拼接在一起

'123' * 2
# 字符串的乘法即将字符串内容进行重复
