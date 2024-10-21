import random
import math

def create_firework(filename, num_balls, center_x, center_y, speed_range, radius):
    with open(filename, "w") as file:
        for _ in range(num_balls):
            angle = random.uniform(0, 2 * math.pi)
            speed = random.uniform(*speed_range)
            vx = speed * math.cos(angle)
            vy = speed * math.sin(angle)
            file.write(f"{center_x} {center_y} {radius} {vx} {vy}\n")

    print(f"Firework of balls saved to '{filename}' successfully.")

create_firework(
    "simulations/4.ball", 
    num_balls=100,  
    center_x=400, 
    center_y=300, 
    speed_range=(50, 200), 
    radius=10            
)
