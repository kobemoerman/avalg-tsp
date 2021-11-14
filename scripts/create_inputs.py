import sys
import random

n = int(sys.argv[1])

with open(f"../data/{n}.in", "w") as f:
    f.write(f"{n} \n")
    for _ in range(n):
        x, y = round(random.random()*100, 3), round(random.random()*100, 3)
        f.write(f"{x} {y} \n")
