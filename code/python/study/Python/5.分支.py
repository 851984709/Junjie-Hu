score = int(input('请输入分数\n'))
if (score > 100) or (score < 0):
    print('输入错误')
elif score >= 90:
    print('A')
elif score >= 80:
    print('B')
elif score >= 70:
    print('C')
elif 70  >  score >= 60:
    print('D')
elif 60  >  score >= 0:
    print('E')
else:
    print('输入错误')
