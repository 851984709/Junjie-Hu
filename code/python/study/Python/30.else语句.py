def MaxFactor(num):
    count = num // 2 # 地板除
    while count > 1:
        if num % count == 0:
            print('%d的最大约数是%d' % (num, count))
            break
        count -= 1
    else:
        print('%d是素数' % num)
MaxFactor(10)
# else可以和while结合使用
# 如果while的循环全部被执行，没有被break，就会执行else的内容
# for语句与else语句结合使用的情况和while语句是一样的

try:
    int('abc')
except ValueError as reason:
    print('出错了：' + str(reason))
else:
    print('么有任何异常')

try:
    int('123')
except ValueError as reason:
    print('出错了：' + str(reason))
else:
    print('没有任何异常')
# 当try语句中没有出现异常时，执行else的内容
