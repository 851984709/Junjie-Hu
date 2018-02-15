try:
    f = open('这算是一个文件.txt')
    print(f.read())
    f.close
except OSError:
    print('文件不存在')
# try-except语句可以监测程序执行过程中某些类型的错误
# 如果程序出现的错误和指定错误类型一致，则执行except Error:后面的语句

try:
    f = open('这算是一个文件.txt')
    print(f.read())
    f.close
except OSError as reason:
    print('错误的原因' + str(reason))
# except Error语句后面可以加上as reason语句来获取发生错误的具体原因
# 出现没有被except监测的错误时，程序依然会报错
# reason为TypeError类型的变量
# reason数据在except语句执行完后会被清除

try:
    num = 1 + '1'
    f = open('这算是一个文件.txt')
    print(f.read())
    f.close
except OSError as reason:
    print('错误的原因' + str(reason))
except TypeError as reason:
    print('错误的原因' + str(reason))
# 一个try语句可以和多个except语句联合使用
# 一旦try语句的执行范围内检测到一个错误，程序就会跳出try语句，直接执行对应的exc-
# ept语句，try内错误后面的内容将不再执行

try:
    num = 1 + '1'
    f = open('这算是一个文件.txt')
    print(f.read())
    f.close
except (OSError, TypeError) as reason:
    print('错误的原因' + str(reason))
# 可以使用元祖来同时监测多个错误
# 同样的，except只会对被；检测到的第一个错误做出反应

try:
    f = open('try-except测试文件.txt', 'w')
    f.write('我存在了')
    num = 1 + '1'
except (OSError, TypeError) as reason:
    print('错误的原因' + str(reason))
finally:
    f.close()
# finally语句
# 无论错误是否发生，finally语句都会被执行
# finally语句通常用在打开文件，但因文件不存在而出现错误时，无法关闭文件的情况
    
try:
    num = 1 + '1'
    f = open('这算是一个文件.txt')
    print(f.read())
    f.close
except:
    print('程序出错')
# 如果except后面不加错误类型，则程序出现任何出错误都会执行except后面的语句
# except后面不加错误类型，也就无法使用as语句来获取错误的详细信息
# 不建议使用这种做法
