import math

WIDTH=1366
HEIGHT=768

Cx, Cy = WIDTH/2, HEIGHT/2
ORBITAL_DISTANCE = 100
M0 = 2000

n_planets = int((HEIGHT - Cy) / ORBITAL_DISTANCE)

print(", ".join([ str(_) for _ in [M0, Cx, Cy, 0, 0, 0, 0, 7, "#ff0000ff" ] ]))

for i in range(1, n_planets + 1):
    short_semiaxis = i * ORBITAL_DISTANCE
    long_semiaxis = short_semiaxis * 1.5
    m = 1

    px = Cx
    py = Cy + short_semiaxis
    pz = 0

    sx = math.sqrt(M0 *((2 / short_semiaxis) - (1 / long_semiaxis)))
    sy = 0
    sz = 0

    radius = 1
    color = "#000000ff"

    print(", ".join([ str(_) for _ in [m, px, py, pz, sx, sy, sz, radius, color ] ]))


