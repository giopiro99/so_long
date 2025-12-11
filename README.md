# 🐬 So_long - A Small 2D Game

**So_long** is a project from the **42 School** curriculum. The objective is to develop a small top-down 2D video game using the school's graphics library (**MiniLibX**).

The player controls a character who must collect all collectibles on the map and reach the exit, avoiding obstacles and enemies, in the minimum number of moves possible.

## 📑 Overview

The game is written entirely in C and focuses on event handling (keyboard/mouse), texture/sprite rendering, and map validation algorithms (such as Flood Fill).

### 🎮 Gameplay
The protagonist moves within a 2D grid. To win the level:
1.  Collect all **Coins (C)**.
2.  Avoid **Enemies (M)** (if present on the map).
3.  Reach the **Exit Door (E)**, which unlocks only after collecting everything.

---

## ✨ Technical Features

* **MiniLibX:** Usage of the graphics library to open windows, handle images, and capture events.
* **Map Parsing:** Reading `.ber` files with strict checks:
    * The map must be rectangular and surrounded by walls.
    * It must contain at least 1 Exit, 1 Start, and 1 Collectible.
* **Path Checking:** Implementation of the **Flood Fill** algorithm to ensure a valid path exists to reach all collectibles and the exit.
* **Sprite Management:** Loading `.xpm` textures for walls, floor, player, and items.
* **Smooth Movement:** Keyboard input handling (WASD / Arrows).

### 🌟 Bonus Features (if enabled)
* **Patrol Enemies:** Presence of enemies that move and kill the player upon contact.
* **Animations:** Animated sprites for the player or enemies.
* **Move Counter:** Display of the number of steps directly on the screen.

---

## 🕹️ Controls

| Key | Action |
| :---: | :--- |
| `W` / `▲` | Move Up |
| `S` / `▼` | Move Down |
| `A` / `◀` | Move Left |
| `D` / `▶` | Move Right |
| `ESC` / `X` | Close Game |

---

## 🚀 Installation & Usage

### Prerequisites
* GCC or Clang
* Make
* MiniLibX library (included or installed on the system)

### Compilation
Clone the repository and compile the project:

```bash
git clone [https://github.com/giopiro99/so_long.git](https://github.com/giopiro99/so_long.git)
cd so_long
make
```

### Execution

Run the game by passing the path to a valid .ber map file as an argument:

./so_long maps/map.ber

🗺️ Map Configuration (.ber)
```text
The game accepts maps described in text files with the .ber extension. The allowed characters are:
1: Wall
0: Floor (Empty)
P: Player (Start)
E: Exit
C: Collectible
M: Enemy (Monster - Bonus)

Example of a valid map:

1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

### 📂 Project Structure
```text
so_long/
├── Makefile
├── so_long.h           # Main header file
├── libft/              # Helper library (string parsing, etc.)
├── i/                  # Assets Folder (.xpm images)
│   ├── P.xpm           # Player
│   ├── E.xpm           # Exit
│   ├── C.xpm           # Collectible
│   ├── 1.xpm           # Wall
│   └── ...
├── parsing.c           # .ber file reading
├── check_the_map.c     # Map rules validation
├── check_P_E_C.c       # Component counting (Player, Exit, Collectibles)
├── flood_fill.c        # Algorithm to check for valid path
├── draw.c              # Image rendering graphics
├── mlx_graphic.c       # Window and mlx initialization
├── mlx_moves.c         # Keyboard input and movement handling
└── free_all.c          # Memory cleanup management
```

🧠 What I Learned

2D Graphics: How pixel buffers work, texture loading, and the rendering loop.

Event Handling: Managing asynchronous events like key presses or window closing hooks.

Algorithms: Practical application of Flood Fill (or BFS/DFS) to solve reachability problems in a matrix.

Memory Management: Preventing memory leaks by correctly allocating and freeing graphical resources and map data structures.
