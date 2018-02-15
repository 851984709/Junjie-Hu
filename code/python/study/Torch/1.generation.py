import numpy as np
import torch

# 生成tensor

list = [[1,2],
        [3,4]]

# 一、使用list生成tensor
tensor1 = torch.FloatTensor(list) # 32bit

# 二、使用numpy的array生成tensor
array = np.array(list)
tensor2 = torch.from_numpy(array)
