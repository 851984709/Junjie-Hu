import torch
from torch.autograd import Variable
import torch.nn.functional as F
import matplotlib.pyplot as plt

x = torch.unsqueeze(torch.linspace(-1,1,100),dim=1)
# 因为torch只能处理二维的数据，所以需要使用torch.unsqueeze给伪数据添加一个维度，dim表示添加在第几维
y = x.pow(2) + 0.2*torch.rand(x.size())
# torch.rand返回的是[0,1)之间的均匀分布

x,y = Variable(x),Variable(y)

# plt.scatter(x.data.numpy(),y.data.numpy())
# plt.show()

class Net(torch.nn.Module):
    def __init__(self,n_feature,n_hidden,n_output):
        super(Net,self).__init__() # 固定的标准写法，用于继承父类的初始化函数
        self.hidden = torch.nn.Linear(n_feature,n_hidden)
        self.predict = torch.nn.Linear(n_hidden,n_output)

    def forward(self,x):
        x = F.relu(self.hidden(x))
        x = self.predict(x)
        return x

net = Net(1,10,1)

print(net)

plt.ion() # 设置为实时打印
plt.show()

# 定义油优化器
optimizer = torch.optim.SGD(net.parameters(),lr=0.5) # learning rate 学习率
# 定义误差函数
loss_func = torch.nn.MSELoss()

# 训练100次
for t in range(100):
    prediction = net(x) # 输入x，并基于x进行预测

    loss = loss_func(prediction,y)

    optimizer.zero_grad() # 清除梯度

    loss.backward() # 反向传递，计算梯度

    optimizer.step() # 使用梯度进行优化

    # 可视化
    if t % 5 == 0:
        # plot and show learning process
        plt.cla()
        plt.scatter(x.data.numpy(),y.data.numpy())
        plt.plot(x.data.numpy(),prediction.data.numpy(),'r-',lw=5)
        plt.text(0.5,0,'loss=%.4f'%loss.data[0],fontdict={'size':20,'color':'red'})
        plt.pause(0.1)

plt.ioff()
plt.show()
