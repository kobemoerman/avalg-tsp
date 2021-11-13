import random

n = 5000

with open(f"{n}.in", "w") as f: 
    f.write(f"{n}")
    f.write("\n")
    for _ in range(n): 
        x, y = round(random.random()*100,3), round(random.random()*100,3)
        f.write(f"{x} {y} \n")


