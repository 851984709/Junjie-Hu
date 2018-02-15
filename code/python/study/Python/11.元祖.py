tuple = (1, 2, 3, 4)
tuple = 1, 2, 3, 4
tuple = ()
# 元祖（tuple）的创建可以使用小括号，也可以不用括号
# 创建空元祖是一定要用括号
    
tuple = 1,
tuple = (1,)
# 创建只有一个元素的元祖时要加逗号
tuple = 1
tuple = (1)
# 以上方法创建的是一个整形变量，不是元祖

tuple = ('你好', 'Hello', 'Sorry')
tuple = tuple[:2] + ('Hi',) + tuple[2:]
# 元祖的值和字符串一样，无法直接进行修改
# 只能通过将修改后的值赋值给同名变量将元祖的值进行更新

tuple = tuple[:2] + tuple[3:]
# 元祖只能通过切片的方法删除元素

del tuple
# 同样可以使用 del 语句对整个元祖进行删除

#——————————————Python对内存空间的管理——————————————#
#                                                                              #
#   使用 del 删除变量，并不会立刻将变量对应的内存空间进行删除。Python会定期对  #
# 变空间进行检查，当发现没有任何变量标签指向该空间时才会将该空间进行删除       # 

tuple  = (1, 2, 3, 4, 'Hello', (123, 234, 'Hi'))
tuple1 = (98, '哈哈',['你好', 234])
# Python的元祖和列表里面都可以包含元祖和列表

tuple2 = tuple + tuple1
tuple3 = tuple * 2
tuple4 = tuple[:]
tuple5 = tuple
tuple[0] and tuple[1]
tuple[1] < tuple[2]
# 元祖的拼接，重复，拷贝，逻辑，关系操作都和列表一样
