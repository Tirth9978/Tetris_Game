# 🎮 Tetris Game in C++ (IT206 DS Lab - Project 2) 🚀

## 📌 Table of Contents
- [🔥 Overview](#-overview)
- [✨ Features](#-features)
- [🎮 Controls](#-controls)
- [🕹️ Game Mechanics](#-game-mechanics)
- [💡 Code Structure & OOP Concepts](#-code-structure--oop-concepts)
- [⚙️ Technical Details](#-technical-details)
- [🛠️ Installation & Execution](#-installation--execution)
- [📁 Project Structure](#-project-structure)
- [🚀 Why Play This Tetris?](#-why-play-this-tetris)
- [🤝 Collaborators](#-collaborators)
- [📢 Share & Support](#-share--support)
- [🤝 Contributing](#-contributing)

---

## 🔥 Overview

A **console-based Tetris game** developed in **C++** using **Object-Oriented Programming (OOP)** principles. It includes the classic Tetris gameplay: falling tetrominoes, rotation, scoring, and a game-over state.

---

## ✨ Features

- 🎯 **Classic Tetrominoes**: Seven standard shapes — I, O, T, S, Z, J, L  
- 🧱 **Game Board**: 10×20 grid with smooth rendering  
- 🔄 **Piece Control**: Move left/right, rotate, soft drop, hard drop  
- ⚡ **Dynamic Speed**: Game speed increases with time  
- 🛑 **Collision Handling**: Prevents out-of-bounds or overlapping moves  
- 🧹 **Line Clearing**: Full rows are cleared for points  
- ☠️ **Game Over Detection**: Ends the game when the board fills up  

---

## 🎮 Controls

```
🎯 Left Arrow (←)   : Move left
🎯 Right Arrow (→)  : Move right
🎯 Up Arrow (↑)     : Rotate piece
🎯 Down Arrow (↓)   : Soft drop
🎯 Spacebar         : Hard drop
🎯 Escape (ESC)     : Pause or Quit
```
---


---

## 🕹️ Game Mechanics

- ⬇️ Tetrominoes fall automatically due to gravity  
- 🔄 Rotate pieces left or right to fit gaps efficiently  
- 🧱 Clear lines for points and to avoid a pile-up  
- ☠️ Game ends when a new piece can’t be placed  
- 🧠 Score increases with each line cleared and quicker reactions  

---

## 💡 Code Structure & OOP Concepts

Organized using core **OOP principles**:

- `Tetromino` class → Handles shape, rotation, and position  
- `Board` class → Manages the game grid, line clearing, and collisions  
- `Game` class → Controls game loop, rendering, scoring, and input  
- Concepts Used: **Encapsulation**, **Abstraction**, and **Modularity**  

---

## ⚙️ Technical Details

- 📦 Game grid implemented using **2D vectors**  
- 🕹️ Real-time keyboard input for responsive controls  
- 🖥️ Cross-platform: works on **Windows and Linux terminals**  
- 🧱 Designed with **C++17** or later standards for better structure  

---

## 🛠️ Installation & Execution

### ✅ Prerequisites
- C++ Compiler (e.g., **GCC**, **Clang**, **MSVC**)
- Optional: `make` utility for automated compilation

### ▶️ Steps
1. Clone or download the repository  
2. Compile the code using your C++ compiler  
3. Run the executable in a terminal window  
4. Enjoy the game!

---

## 📁 Project Structure

```
├── main.cpp          # Main source code file
├── project_2_tetris.pdf  # Project description & requirements
├── README.md         # Documentation & setup guide
```


---

## 🚀 Why Play This Tetris?

- 💡 No flickering = **ultra-smooth gameplay**
- 🧩 Works in terminal (Windows/Linux) — no graphics required
- 🎵 Retro feel with modern code design
- ⏱️ Reflex-building and addictive
- ⚡ Quick install — just compile and play!

---

## 🤝 Collaborators

- 👨‍💻 **Tirth Patel** (202401157)  
- 👨‍💻 **Raj Patel** (202401152)  
- 👨‍💻 **Shlok Patel** (202401156)
- 👨‍💻 **Prakriti Pandey** (202401164)
  
---

## 📢 Share & Support

If you liked this project, give it a ⭐ and share it with your friends!

---

## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
