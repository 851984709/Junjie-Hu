# 使用神经网络处理回归问题
# 该程序只使用numpy进行简单的数据处理，配合matplotlib模块进行可视化

# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

n_x = 50 # 输入数列的长度
rate_disorderrate = 0.2 # 混乱度
n_layer = 1 # 隐藏层的层数
rate_learning = 0.0001

# 生成伪数据
x = np.arange(n_x)
y = x + np.random.rand(x.size)*10*rate_disorderrate

plt.ion() # 设置为实时打印
plt.scatter(x,y)
plt.show()

# 随即初始化神经网络权重
w1 = np.random.rand(n_layer,n_x)
w2 = np.random.rand(n_layer,n_x)

# 训练1000次
for t in range(100):
    # 计算预测值
    h = x * w1 # 隐藏层
    h_relu = np.maximum(h,0) # 激活
    y_pre = h_relu * w2 # y的预测值

    # 计算误差
    loss = np.square(y_pre - y).sum()
    print(t,loss)

    # 误差反向传递
    grad_y_pre = 2 * (y_pre - y)
    grad_w2 = h_relu * grad_y_pre
    grad_h_relu = w2 * grad_y_pre
    grad_h = grad_h_relu.copy()
    grad_h[h < 0] = 0
    grad_w1 = x * grad_h

    # 更新权重
    w1 -= rate_learning * grad_w1
    w2 -= rate_learning * grad_w2

    # 可视化
    if t % 5 == 0:
        # plot and show learning process
        plt.cla()
        plt.scatter(x, y)
        plt.plot(x, y_pre[0], 'r-', lw=5)
        plt.text(0.5, 0, 'loss=%.4f' % loss.data[0], fontdict={'size': 20, 'color': 'red'})
        plt.pause(0.1)

# # N is batch size; D_in is input dimension;
# # H is hidden dimension; D_out is output dimension.
# N, D_in, H, D_out = 64, 1000, 100, 10
#
# # Create random input and output data
# x = np.random.randn(N, D_in)
# y = np.random.randn(N, D_out)
#
# # Randomly initialize weights
# w1 = np.random.randn(D_in, H)
# w2 = np.random.randn(H, D_out)
#
# learning_rate = 1e-6
# for t in range(500):
#     # Forward pass: compute predicted y
#     h = x.dot(w1)
#     h_relu = np.maximum(h, 0)
#     y_pred = h_relu.dot(w2)
#
#     # Compute and print loss
#     loss = np.square(y_pred - y).sum()
#     print(t, loss)
#
#     # Backprop to compute gradients of w1 and w2 with respect to loss
#     grad_y_pred = 2.0 * (y_pred - y)
#     grad_w2 = h_relu.T.dot(grad_y_pred)
#     grad_h_relu = grad_y_pred.dot(w2.T)
#     grad_h = grad_h_relu.copy()
#     grad_h[h < 0] = 0
#     grad_w1 = x.T.dot(grad_h)
#
#     # Update weights
#     w1 -= learning_rate * grad_w1
#     w2 -= learning_rate * grad_w2
