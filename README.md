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

## 🎮 Tetris Game

Welcome to the **Tetris Game** developed as part of the IT206 - Data Structures Lab at DA-IICT. This project implements a console-based version of the classic Tetris game using **C++** and leverages various data structures and algorithms to manage game logic and rendering efficiently.

---

## 📚 Project Overview

- **Platform:** Console (Terminal-based)  
- **Supported OS:** Windows & Linux  
- **Language:** C++  

---

## 🧩 Game Features

👉 Classic Tetris functionality with different shapes  
👉 Real-time piece rotation and movement  
👉 Score tracking and level progression  
👉 Game pause and resume feature  
👉 Terminal-based UI for smooth gameplay  

---

## ⚙️ How to Run

1. **Clone the Repository:**
```bash
git clone https://github.com/Tirth9978/Tetris_Game.git
```

2. **Navigate to the Directory:**
```bash
cd Tetris_Game
```

3. **Compile the Code:**
```bash
g++ tetris.cpp -o tetris
```

4. **Run the Game:**
```bash
./tetris
```

---

## 🛠️ Data Structures Used

### 1. **2D Vector (Board Representation)**
- **Type:** `vector<vector<int>>`
- **Purpose:** Stores the game grid where the pieces are placed.
- **Usage:**
```cpp
vector<vector<int>> board(height, vector<int>(width, 0));
```
- `height` - Number of rows in the board  
- `width` - Number of columns in the board  

---

### 2. **Vector (Piece Representation)**
- **Type:** `vector<vector<int>>`
- **Purpose:** Represents the current active Tetris piece.  
- **Usage:**
```cpp
vector<vector<int>> Piece;
```
- Used during piece placement and rotation.

---

### 3. **Pair (Piece Positioning)**
- **Type:** `pair<int, int>`
- **Purpose:** Tracks the x and y coordinates of the active piece.  
- **Usage:**
```cpp
int x, y;  // Current position of the piece
```

---

### 4. **Queue (Future Pieces Queue)**
- **Type:** `queue<vector<vector<int>>>`
- **Purpose:** Maintains a queue of upcoming pieces.  
- **Usage:**
```cpp
queue<vector<vector<int>>> nextPieces;
```

---

### 5. **Map (Piece Rotation Management)**
- **Type:** `map<int, vector<vector<int>>>`
- **Purpose:** Stores different rotations of each piece for easy access.  
- **Usage:**
```cpp
map<int, vector<vector<int>>> rotations;
```

---

## 🔢 Key Variables Used

| **Variable** | **Type**              | **Purpose**                           |
|--------------|----------------------|--------------------------------------|
| `board`      | `vector<vector<int>>` | Stores the current game board        |
| `Piece`      | `vector<vector<int>>` | Represents the active piece          |
| `x, y`       | `int`                 | Position of the current piece        |
| `width`      | `int`                 | Width of the game board              |
| `height`     | `int`                 | Height of the game board             |
| `score`      | `int`                 | Tracks the player's score            |
| `maxScore`   | `int`                 | Stores the highest score achieved    |
| `isPaused`   | `bool`                | Checks if the game is paused         |
| `nextPieces` | `queue<vector<vector<int>>>` | Holds upcoming Tetris pieces |
| `rotations`  | `map<int, vector<vector<int>>>` | Stores rotations of pieces |

---

## 🔄 Game Logic Overview

1. **Initialization:**
   - Initializes the board, piece queue, and other variables.
   - Generates the first piece and sets the starting position.

2. **Piece Movement:**
   - Handles left, right, and downward movements.
   - Validates boundary conditions to prevent overlap.

3. **Rotation:**
   - Uses `RotateLeft()` and `RotateRight()` to change piece orientation.
   - Ensures rotated piece fits within the grid.

4. **Collision Detection:**
   - Checks for collision with other pieces or grid boundaries.

5. **Line Clearance:**
   - Detects full rows and clears them, updating the score.

6. **Game Pause/Resume:**
   - Toggles game state between paused and active.

---

## 🔄 Piece Rotation Logic

### Rotate Left
```cpp
vector<vector<int>> RotateLeft(vector<vector<int>> mat) {
    int row = mat.size();
    int col = mat[0].size();
    vector<vector<int>> temp(col, vector<int>(row));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            temp[col - j - 1][i] = mat[i][j];
        }
    }
    return temp;
}
```

---


---

## 🎨 Terminal UI

- `#` - Represents a filled cell  
- `.` - Represents an empty cell  
- `<><>` - Board boundaries  

---

## 📄 File Structure

```
📦 Tetris_Game
 └── 💚 tetris.cpp     → Main game logic
 └── 💚 README.md      → Project documentation
 └── 💚 Makefile       → Build automation (optional)
```

---

## 🤝 Contribution Guidelines

- Fork the repo and submit a PR with your changes.  
- Ensure the code follows best C++ practices.  
- Add comments and document new functionality.  

---

## 💎 Contact

📌 **Author:** Tirth Patel  
📌 **GitHub:** [Tirth9978](https://github.com/Tirth9978)  

---

🎉 Enjoy playing Tetris and feel free to contribute or suggest improvements!

---

📆 **SEO Optimized**  
🔀 **Clear Structure**  
📖 **Documentation with Proper Formatting**


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
