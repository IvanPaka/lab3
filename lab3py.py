import numpy as np
import matplotlib.pyplot as plt
a = []
with open("data_lagr.csv", "r") as f:
    for line in f:
        a.append(line[:-1].split(","))

z = np.zeros((len(a), 2))
for i in range(len(a)):
    for j in 0,1:
        z[i][j] = float(a[i][j])

plt.figure(figsize=(16,9))
plt.plot(z[:, 0], z[:, 1])
plt.plot(z[::10, 0], z[::10, 1], "ro")
plt.grid()
plt.show()

a = []
with open("data_n1.csv", "r") as f:
    for line in f:
        a.append(line[:-1].split(","))

z = np.zeros((len(a), 2))
for i in range(len(a)):
    for j in 0,1:
        z[i][j] = float(a[i][j])

plt.figure(figsize=(16,9))
plt.plot(z[:, 0], z[:, 1])
plt.plot(z[::10, 0], z[::10, 1], "ro")
plt.grid()
plt.show()

a = []
with open("data_n2.csv", "r") as f:
    for line in f:
        a.append(line[:-1].split(","))

z = np.zeros((len(a), 2))
for i in range(len(a)):
    for j in 0,1:
        z[i][j] = float(a[i][j])

plt.figure(figsize=(16,9))
plt.plot(z[:, 0], z[:, 1])
plt.plot(z[::10, 0], z[::10, 1], "ro")
plt.grid()
plt.show()

a = []
with open("data_appr.csv", "r") as f:
    for line in f:
        a.append(line[:-1].split(","))

z = np.zeros((len(a), 3))
for i in range(len(a)):
    for j in 0,1,2:
        z[i][j] = float(a[i][j])

plt.figure(figsize=(16,9))
plt.plot(z[:, 0], z[:, 1], "bo:", ms=3)
plt.plot(z[:, 0], z[:, 2], "r-", lw=2)
plt.grid()
plt.show()