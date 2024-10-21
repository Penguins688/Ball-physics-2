import math

# Configuration
num_balls = 38
ball_radius = 10
ball_distance = 20  # Distance between each ball
wave_amplitude = 50  # Amplitude of the wave
wave_frequency = 0.05  # Frequency of the wave
gravity = 0.5  # Gravity effect
bounce_factor = 0.5  # How much the balls bounce back

# Create the bouncing wave simulation file
with open("simulations/5.ball", "w") as file:
    for i in range(num_balls):
        x = i * ball_distance + 20
        # Calculate the y position with gravity effect
        y = wave_amplitude * math.sin(wave_frequency * x) + 300  # Base position to keep balls on screen
        # Apply gravity (this is just a simulation for initial positions)
        y += gravity * (i % 100) * bounce_factor  # Vary the effect based on the index
        file.write(f"{x} {y} {ball_radius} 0 0\n")
