# This file can check whether MPC weight matrix Q is a positive matrix or not
#
# Author: Yinuo Wang
# Date: 03/19/21
# Email: dbdxwyn@163.com
import numpy as np

r = 4e-5
q = np.array([1,   1,    1, 0, 0, 50, 0,  0, 1,    1,  1,   1])
Q = np.zeros((12,12))
R = np.zeros((12,12))
for i in range(12):
    Q[i][i] = q[i]
    R[i][i] = r
# print(Q)
for i in range(12):
    Q_new = Q[0:(i+1),0:(i+1)]
    R_new = R[0:(i+1),0:(i+1)]
    x = np.linalg.det(Q_new)
    y = np.linalg.det(R_new)
    # print(Q_new)
    if x >= 0 and y >= 0:
        print(i," OK  ",x,y,"\n")
    else:
        print(i," Error  ",x,y,"\n")


