import matplotlib.pyplot as plt
import numpy as np

lines = np.loadtxt("../matching.dat")
plt.plot(lines) 
plt.show()

lines = np.loadtxt("../costs.dat")
plt.plot(lines) 
plt.show()