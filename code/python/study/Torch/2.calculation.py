import torch

# torch运算

tensor1 = torch.FloatTensor([[-1,-2],
                             [1,2]])
tensor2 = torch.FloatTensor([[1,2],
                             [3,4]])

# 一、基本运算
# 1、点乘
dot1 = torch.dot(tensor1,tensor2)
dot2 = tensor*tensor
# 2、差乘
mm = torch.mm(tensor1,tensor2)
# 3、转置
transpose = torch.t(tensor1)

# 二、其他运算
# 1、绝对值
abs = torch.abs(tensor1)
# 2、三角函数
sin = torch.sin(tensor1)
