# 2048 — C++ Console Edition

A console-based implementation of the classic 2048 puzzle game, written in C++. This version focuses on core game logic and file handling, including a persistent leaderboard system.

**Built by Muhammad Ali ([@ali4xk](https://github.com/ali4xk))**

> A graphical Python remake of this project (with a full Tkinter UI) is available [here](https://github.com/ali4xk/2048Game-Python).

---

## Features

- **Console-based gameplay** — runs entirely in the terminal
- **Three difficulty levels** with different grid sizes
  - Easy — 6×6 grid
  - Medium — 10×10 grid
  - Hard — 15×15 grid
- **Classic 2048 mechanics**
  - Slide and merge tiles using **W / A / S / D**
  - Score increases with every merge
  - Game ends when no empty cells remain and no merges are possible
- **File handling & persistent leaderboard**
  - Scores stored in a binary file (`leaderboard.bin`) for fast read/write
  - Human-readable copy maintained in `leaderboard.txt`
  - Leaderboard view results written to `leaderboardDisplay.txt`
  - Multiple leaderboard views:
    - View all players
    - View top N players overall
    - View top N scores for a specific player
    - Skip/exit without viewing

---

## Getting Started

### Requirements

- A C++ compiler (g++, MSVC, Clang, etc.)

### Build & Run

```bash
g++ -o game2048 game.cpp
./game2048
```

On Windows:

```bash
g++ -o game2048.exe game.cpp
game2048.exe
```

---

## How to Play

1. Run the program and choose a difficulty (Easy, Medium, or Hard) to set the grid size.
2. Use **W / A / S / D** to slide tiles up, left, down, or right.
3. Tiles with matching values merge into one when they collide, adding to your score.
4. The game ends when the board is full and no more merges are possible.
5. After the game ends, your score is written to the leaderboard files.
6. From the leaderboard menu, choose to view all players, top scores, or a specific player's history.

---

## Project Structure

```
.
├── game.cpp                 # Main game source code
├── leaderboard.bin          # Binary leaderboard data (auto-generated/updated)
├── leaderboard.txt          # Human-readable leaderboard records
├── leaderboardDisplay.txt   # Output of the most recent leaderboard view
└── README.md
```

---

## About

This project was built to practice core C++ concepts including 2D arrays, grid manipulation algorithms (transpose/reverse for tile movement), structs, and file I/O (binary and text). It later became the foundation for a [Python/Tkinter remake](https://github.com/ali4xk/Project2048-Python) with a graphical interface.

## License

This project is open source and available for anyone to use, modify, and learn from.
