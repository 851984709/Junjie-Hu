import pickle
list = [123, 3.14, '啊哈哈', ['another list']]
file = open('pkl_file.pkl', 'wb')
# 文件的后缀名不影响文件的内容，只影响文件的打开方式
# 文件的后缀名可以任意设置

pickle.dump(list, file)
# 将list中的内容写入file中
# pickle.dump()函数可以将任意Python类型的数据写入文件中

file.close()
file = open('pkl_file.pkl', 'rb')
pickle.load(file)
# 导出文件中的内容
# pickle.load()函数可以将file中的数据按照它原本的类型导出
