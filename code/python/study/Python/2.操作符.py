a =  2
a += 2

1 // 2
# 真实除法

3 ** 4
# 3的4次方
# **（幂运算符）的优先级比它左侧的单目运算符高，比右侧的单目运算符低
# 如： -3 ** -2 的值为 -0.1111111
#      等价于 -（3 ** （-2））

1 and 0
0 or  3
not 1
# and  与
# or   或
# not  非

3 < 4 < 5
# 等价于 (3 < 4) and (4 < 5)

x, y = 4, 5
# Python的赋值语句

small = x if x < y else y
# 三元操作符
# 等价于：  if x < y:
#               small = x
#           else:
#               small = y
    
assert 4 > 3
# 关键字 assert（断言）
# 当 assert 后面的条件为假时，程序自动崩溃并抛出 AssertionError 的异常
