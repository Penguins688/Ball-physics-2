import math
import random

# Configuration
num_planets = 10
ball_radius = 10
center_x, center_y = 400, 300  # Center of the orbits
max_distance = 200  # Maximum distance from the center
max_speed = 0.05  # Maximum speed of the orbit

# Create the orbiting planets simulation file
with open("simulations/7.ball", "w") as file:
    for i in range(num_planets):
        distance = random.uniform(30, max_distance)  # Random distance for each planet
        speed = random.uniform(0.01, max_speed)  # Random speed for each planet
        angle = i * (2 * math.pi / num_planets)  # Initial angle for even distribution
        
        # Generate initial position based on angle and distance
        x = center_x + distance * math.cos(angle)
        y = center_y + distance * math.sin(angle)

        # Write the initial position and speed to the file
        file.write(f"{x} {y} {ball_radius} {speed} {angle}\n")
