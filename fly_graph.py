import numpy as np
import matplotlib.pyplot as plt
plt.rcParams["mathtext.fontset"] = "cm"

fname = "fly_data.txt"
gname = "graph.png"
gformat = "png"
dpi = 300

data = np.loadtxt(fname)
t = data[:,0]
x = data[:,1]
y = data[:,2]
vx = data[:,3]
vy = data[:,4]

plt.plot(x,y)
plt.title("$\mathrm{Orbit}$", fontsize=20)
plt.xlabel("$x$", fontsize=18)
plt.ylabel("$y$", fontsize=18)
plt.savefig(gname, format=gformat, dpi=dpi)
#plt.show()