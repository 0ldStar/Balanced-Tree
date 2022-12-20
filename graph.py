import matplotlib.pyplot as plt
import scipy.optimize as opt
import numpy as np


def func(x, c):
    return c * x * np.log(x)


def model(x):
    return 2.8 * x * np.log(x)


data = np.transpose(np.loadtxt('../Rand1.txt'))
N = data[0]
theoretical = data[1]
insert = data[2]
delete = data[3]
search = data[4]

data2 = np.transpose(np.loadtxt('../Rand2.txt'))
N2 = data2[0]
theoretical2 = data2[1]
insert2 = data2[2]
delete2 = data2[3]
search2 = data2[4]

plt.plot(N, 2.8 * theoretical, 'r-', label='theory')
plt.plot(N, insert, 'y-D', label='insert', )
plt.plot(N, delete, 'b.-', label='delete')
plt.plot(N, search, 'g-x', label='search')
plt.plot(N2, theoretical2, 'r-', label='theoreticalOrd', )
plt.plot(N2, insert2, 'y-D', label='insertOrd', )
plt.plot(N2, delete2, 'b.-', label='deleteOrd')
plt.plot(N2, search2, 'g-x', label='searchOrd')
plt.yscale('log')
plt.xlabel('N')
plt.ylabel('iteration`')
plt.grid()
plt.legend()
plt.show()
