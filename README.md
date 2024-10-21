# Ball Physics 2

![warning](https://img.shields.io/badge/DISCLAIMER-Executable%20only%20works%20on%20macOS-red)  
![compile](https://img.shields.io/badge/Compile%20yourself%20if%20using%20a%20different%20OS-yellow) 

## Running

**To run the engine, run the ball_physics executable**

```console
./ball_physics
```

## Running pre-programmed simulations

**There are 6 pre-programmed simulations each cooresponding to a different number key** <br>
**To run a simulation just hold down any key 1-9** <br>
**When you want a simulation to stop**

| simulation 1    | simulation 2 | simulation 3    | simulation 4 | simulation 5 | simulation 6 | simulation 7 | simulation 8 | simulation 9 |
|-----------------|--------------|-----------------|--------------|--------------|--------------|--------------|--------------|--------------|
| Crazy movement  | Ball Tower   | Ball wall       | Firework     | Wave pattern | Tsunami      | empty slot   | empty slot   | empty slot   |
| 2 objects       | 601 objects  | 300 objects     | 100 objects  | 38 objects   | 600 objects  | empty slot   | empty slot   | empty slot   |

**If you don't want to run simulations you can just click to place a ball**

## Programming simulations

**To program a simulation just follow this simple format:**

```python
initial_x initial_y radius initial_acceleration_x initial_acceleration_y
```

**Or you could write a python script to generate patterns for you**
```python
import math

num_balls = 38
ball_radius = 10
ball_distance = 20 
wave_amplitude = 50
wave_frequency = 0.05 
gravity = 0.5
bounce_factor = 0.5

with open("simulations/7.ball", "w") as file:
    for i in range(num_balls):
        x = i * ball_distance + 20
        y = wave_amplitude * math.sin(wave_frequency * x) + 300 
        y += gravity * (i % 100) * bounce_factor
        file.write(f"{x} {y} {ball_radius} 0 0\n")
```
