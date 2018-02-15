try:
    f = open('data.txt')
except OSError as reason:
    print('出错了：', str(reason))
finally:
    f.close()
# 如果指定文件不存在，f的创建就会失败。由于finally的语句始终都会执行，对一个创建
# 失败的变量（未定义变量）进行文件关闭处理，程序依然会出错

try:
   with open('data.txt') as f:
       f.read()
except OSError as reason:
    print('出错了：', str(reason))
# with语句用于简化try-except-finally的处理流程，对程序中的一些操作进行善后处理
# 对于一些需要预先设置，事后要清理的一些任务，with提供了一种非常方便的表达
# 这里使用with语句便不需要再手动关闭f文件了
