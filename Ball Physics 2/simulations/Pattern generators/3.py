def create_grid(filename, rows, cols, x_spacing, y_spacing, radius):
    with open(filename, "w") as file:
        for row in range(rows):
            for col in range(cols):
                x = col * x_spacing + 20
                y = row * y_spacing + 20
                file.write(f"{x} {y} {radius} 0 0\n")

    print(f"Grid of balls saved to '{filename}' successfully.")

create_grid("simulations/3.ball", rows=15, cols=20, x_spacing=40, y_spacing=40, radius=20)
