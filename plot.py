import matplotlib.pyplot as plt


x = []
y = []

names = []

with open("particules.txt") as f:
    for line in f:
        parts = line.split()
        x.append(float(parts[0]))
        y.append(float(parts[1]))
        names.append(parts[2])

fig = plt.figure()
ax = fig.add_subplot()


ax.scatter(x, y)

for i, name in enumerate(names):
    ax.text(x[i], y[i], name)

ax.set_xlabel("X")
ax.set_ylabel("Y")


plt.show()