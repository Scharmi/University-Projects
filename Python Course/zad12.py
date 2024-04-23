import numpy as np

A = np.array([1.0, 2.2, 2.0, 1.5, 3.2])
B = np.array([1.3, 1.1, 2.4, 3.2, 1.2])
Y = np.array([0.0, 1.0, 1.0, 0.0, 1.0])
W_1 = np.arange(0, 1.1, 0.1)
W_2 = np.arange(2, 3.1, 0.1)

def M_w1_w2(w1, w2, a, b):
    return 1/(1 + np.exp(-w1*a - w2*b))

def MSE(a, y):
    return np.mean((a - y)**2)

W_1_grid, W_2_grid = np.meshgrid(W_1, W_2)

A = A[:, np.newaxis, np.newaxis]
B = B[:, np.newaxis, np.newaxis]
Y = Y[:, np.newaxis, np.newaxis]

M_output = 1 / (1 + np.exp(-W_1_grid * A - W_2_grid * B))

MSE_values = np.mean((M_output - Y)**2, axis=0)

print(MSE_values)




