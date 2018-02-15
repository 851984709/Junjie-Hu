import os

os.getcwd()
# 返回当前工作目录

os.chdir(path)
# 改变工作目录

os.listdir(path = '.')
# 列举目录中的文件名（'.'表示当前目录，'..'表示上一级目录）

os.mkdir()
# 创建单层目录，如该目录已存在抛出异常

os.remove(path)
# 删除文件，无法删除目录

os.rmdir(path)
# 删除目录，如果目录不为空，则出错

os.rename(old, new)
# 将文件old重命名为new

os.system('calc')
# 运行系统的shell命令

#---------------------------------os.path模块----------------------------------#

os.path.basename(path)
# 去掉路径，单独返回文件名

os.path.dirname(path)
# 去掉文件名，单独返回路径

os.path.join(path1,path2...)
# 将参数各部分组合乘一个路径名
os.path.join('C:\\','A','B')
# 如果要指定一个硬盘，应当在该硬盘后面加上':\\'

os.path.split(path)
os.path.split('E:\\A\\SEXY.AVI')
# 分割文件名语路径，返回(f_path, f_name)元祖。如果完全使用目录，它也会将最后一个
# 目录作为文件名分离，且不会判断文件或目录是否存在

os.path.splitext(path)
# 分离文件名语扩展名，返回(f_name, f_extension)元祖

os.path.getsize(file)
# 返回指定文件的尺寸，单位是字节

os.path.getatime(file)
import time
list(time.localtime(os.path.getatime('文件.txt')))
# 返回指定文件最近的访问时间（浮点型秒数，可用time模块的gmtime()或localtime()函
# 数换算）

os.path.getctime(file)
# 返回指定文件的创建时间

os.path.getmtime(file)
# 返回指定文件最新的修改时间

#---------------------------以下函数返回True或False----------------------------#

os.path.exists(path)
# 判断指定路径（目录或文件）是否存在

os.path.isabs(path)
# 判断指定路径是否为绝对路径

os.path.isdir(path)
# 判断指定路径是否存在且是一个目录

os.path.isfile(path)
# 判断指定路径是否存在且是一个文件

os.path.islink(path)
# 判断指定路径是否存在且是一个符号链接

os.path.ismount(path)
# 判断指定路径是否存在且是一个挂载点

os.path.samefile(path1, path2)
# 判断path1和path2两个路径是否指向同一个文件或目录
