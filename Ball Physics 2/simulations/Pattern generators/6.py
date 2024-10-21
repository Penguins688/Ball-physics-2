import math

with open("simulations/6.ball", "w") as file:
    for i in range(600):
        file.write(f"{700 + math.sin(i)*10} {i} 10 -100 0\n")