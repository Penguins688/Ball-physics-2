import math

num_balls = 38
ball_radius = 10
ball_distance = 20 
wave_amplitude = 50
wave_frequency = 0.05 
gravity = 0.5
bounce_factor = 0.5

with open("simulations/5.ball", "w") as file:
    for i in range(num_balls):
        x = i * ball_distance + 20
        y = wave_amplitude * math.sin(wave_frequency * x) + 300 
        y += gravity * (i % 100) * bounce_factor
        file.write(f"{x} {y} {ball_radius} 0 0\n")
