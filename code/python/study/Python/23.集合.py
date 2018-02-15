num = {}
type(num)
# 此时num的种类为dict字典
num = {1, 2, 3, 4, 5}
type(num)
# 此时num的种类为set集合
# 集合没有顺序

num = {1, 2, 3, 4, 5, 3, 4, 5, 6}
# 集合具有唯一性，每个元素只会出现一次

num = set((123, 234, 345))
num = set(['哈哈', '妖精', '初音ミク'])
# set工厂函数，建立集合

string = [1, 2, 3, 4, 2, 3, 4, 8, 9, ]
string = list(set(string))
# 删除列表中的重复元素
# 列表的顺序可能会发生改变

num = {0, 1, 2, 3, 4, 5}
num.add(6)
# 向集合中添加一个元素
num.remove(1)
# 删除集合中的一个指定元素
# 如果指定元素不存在，就会报错

num1 = frozenset([1, 2, 3, 4, 5])
num1.add(10)
# error!
# 用frozenset()创建不可变集合
