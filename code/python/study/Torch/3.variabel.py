import torch
from torch.autograd import Variable

# variable

tensor = torch.FloatTensor([[1,2],
                            [3,4]])
variable = Variable(tensor,requires_grad=True) # 设置需要计算梯度

t_out = torch.mean(tensor*tensor)
v_out = torch.mean(variable*variable)

v_out.backward()
# v_out = 1/4*sum(variable*variable)
# d(v_out)/d(variable) = 1/2*variable 求导

