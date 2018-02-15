brand  = ['李宁', '耐克', '阿迪达斯']
slogan = ['一切皆有可能', 'Just do it', 'Impossible is nothing']
print(slogan[brand.index('耐克')])
# Python可以通过索引值的方法来建立映射
# 字典没有顺序

dict1 = {'李宁':'一切皆有可能',
        '耐克':'Just do it',
        '阿迪达斯':'Impossible is nothing'}
print(dict1['李宁'])
# 字典是Python语言中唯一的映射类型
# 字典由大括号{}定义
# 冒号(:)左边为键(key,关键字)，右边为值(value)

dict2 = {1:'哈哈', 'Hello':[1, 2, 3], (1, 2):3.14}
print(dict2[(1, 2)])
# 键的值可以为数字，字符串，元祖等等
# 键的值必须是不可变的，而列表是本地可变的，所以不能用list来做键

dict3 = dict((('F',70), ('i',105), ('s',115), ('h',104)))
dict4 = dict(诸葛亮='我从未见过如此厚颜无耻之人', 董大伟='deep dark fantasy')
# dict()工厂函数
# Python还可以通过以上方法创建字典

dict4['诸葛亮'] = '鞠躬尽瘁，死而后已'
# 改变字典中键对应的值

dict4['比利·海灵顿'] = '森の妖精'
# 向字典中添加映射

#-------------------字典的BIF(built-infunctions,内置函数)----------------------#

dict5 = {}
dict5 = dict5.fromkeys((1, 2, 3))
# 向字典中加入键，默认每个键对应的值为None
dict5 = dict5.fromkeys((1, 2, 3), '哈哈哈')
dict5 = dict5.fromkeys(range(32),'初音ミク')
# 向字典中加入键，并给每一个键赋值为第二个参数

dict5.keys()
# 返回字典中所有的键
dict5.values()
# 返回字典中所有的值
dict5.items()
# 返回字典中的所有项（映射），并用元祖的形式表示
dict5.get('123')
# 返回字典中键为123的值，如果键不存在，返回None
31 in dict5
32 in dict5
# 两个表达式分别返回True和False
# 可以通过成员操作符来判断键是否在字典中
dict5.clear()
# 清空字典
