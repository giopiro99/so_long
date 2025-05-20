# so_long
So_long is a small 2D game built with simple graphics where the player navigates a map, collects items, and reaches an exit while avoiding obstacles.

--------------------------------------
so_long is a simple 2D game developed in C using the MiniLibX graphics library. The player controls a character that must collect all collectibles on the map and reach the exit to win.

## Features

- Player movement with arrow keys or WASD
- Map validation to ensure correct layout and path
- Collectibles scattered throughout the map
- Exit door that opens only after all collectibles are gathered
- Enemy AI that moves randomly and causes game over on contact (Bonus)
- Smooth animations for player and enemies (Bonus)
- Display of the number of moves made by the player (Bonus)

## How to run

1. Compile the project with `make`.
2. Prepare a valid map file.
3. Run the game with:

```bash
./so_long maps/your_map.ber

