import matplotlib.pyplot as plt
import numpy as np
data = np.loadtxt("lab.dat")
r = data[:,0]
U = data[:,1]

plt.plot(r,U)
plt.axhline(0, linestyle='--')

plt.xlabel("Distance r")
plt.ylabel("Potentiel U(r)")
plt.title("Potentiel en fonction de la Distance")

plt.grid()
plt.show()