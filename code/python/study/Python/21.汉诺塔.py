def Han(n):
    if n == 1:
        return 1
    else :
        return Han(n - 1) * 2 + 1
# 计算n层圆盘全部移完所需要的次数

def hanoi(n, x, y, z):
    if n == 1:
        print(x, ' --> ', z)
    else:
        hanoi(n-1, x, z, y)  # 将n-1层圆盘从x移动到y上
        print(x, ' --> ', z) # 将最低层圆盘从x移动到z上
        hanoi(n-1, y, x, z)  # 将y上的圆盘移动到z上
# 显示汉诺塔的步骤
