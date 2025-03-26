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
- [🤝 Collaborators](#-collaborators-)  
- [📢 Share & Support](#-share--support)  
- [🚀 Future Enhancements](#-future-enhancements)  
- [🤝 Contributing](#-contributing)

---

## 🔥 Overview

This project is a **console-based Tetris game** developed in **C++**, following object-oriented programming principles. The game features **classic Tetris mechanics**, including falling tetrominoes, piece rotation, scoring, and game-over conditions.

---

## ✨ Features

- 🎯 **Classic Tetris Gameplay**: Includes seven standard tetrominoes (I, O, T, S, Z, J, L)  
- 🎮 **Game Board**: A **10x20** grid representation for smooth gameplay  
- 🔄 **Piece Movements**: Move left, right, rotate, and drop pieces  
- ⚡ **Gravity & Speed Increase**: Tetrominoes fall at a constant speed, increasing as the game progresses  
- 🛑 **Collision Detection**: Prevents pieces from overlapping or moving out of bounds  
- 🧹 **Line Clearing & Scoring**: Full rows are removed, and points are awarded  
- ☠️ **Game Over Detection**: Ends when blocks reach the top  

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

## 🕹️ Game Mechanics

- ⬇️ **Gravity** causes tetrominoes to fall automatically  
- 🔄 **Rotation** helps fit pieces into gaps  
- 🧱 **Line clearing** gives points and frees up space  
- ☠️ **Game Over** occurs when a new piece cannot be placed  
- 🧠 **Scoring system** rewards speed and precision  

---
---

## 💡 Code Structure & OOP Concepts

This game is built using Object-Oriented Programming for clean and modular code:

- 🧱 `Tetromino` class: Manages shape, rotation, and current state  
- 🗃️ `Board` class: Handles grid, line clearing, collision detection  
- 🎮 `Game` class: Controls game loop, score, timing, and rendering  
- 🎯 Encapsulation and abstraction used for better scalability  

---

## 🛠️ Installation & Execution

### 📌 Prerequisites

- ✅ **C++ Compiler** (GCC, Clang, or MSVC supporting C++17 or later)
- ✅ **Make (Optional)**

## 📁 Project Structure

```
├── main.cpp          # Main source code file
├── project_2_tetris.pdf  # Project description & requirements
├── README.md         # Documentation & setup guide
```

## ⚙️ Technical Details

🔹 Uses **2D vectors** for the game grid representation.  
🔹 Implements **real-time user input handling** for smooth gameplay.  
🔹 Supports both **Windows and Linux** platforms with cross-platform compatibility.  
🔹 **Object-Oriented Design (OOP)** ensures modular and extensible code.  

## 🤝 Contributing

💡 Have ideas or improvements? Fork this repository and submit a pull request! Let's build an even better Tetris together. 🎉

---
🚀 **Developed for IT206 Data Structures Lab - Project 2** 🎮



---

## 🤝 Collaborators 🏆
- 👨‍💻 **Tirth Patel (202401157)**
- 👨‍💻 **Raj Patel (202401152)**
- 👨‍💻 **Shlok Patel (202401156)**
- 👨‍💻 **Prakriti Pandey (202401164)**
- 👏 **Special thanks to all contributors!**



---

## 🚀 Why Play This Tetris? 🔥
- No flickering issues, making it **super smooth** 🏎️
- Works directly in **Windows & Linux terminals** 📟
- Classic **Tetris mechanics** for a nostalgic experience 🎵
- **Easy to install and play** – just **compile & run** 🎯
- Improve your reflexes and **challenge yourself!** 🏆

---

## 📢 Share & Support ❤️
If you like this project, **star the repository**, share it with your friends, and enjoy endless Tetris fun! 🎉

**Happy Coding & Gaming! 🎮🔥**
