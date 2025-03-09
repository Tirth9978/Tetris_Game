# 🎮 Tetris Game in C++ (Terminal Version)

A **flicker-free** Tetris game written in **C++**, running in the Windows terminal. 🕹️
This game uses **double buffering** for smooth rendering and **optimized console updates** to avoid screen flickering. 🚀

---

## 🌟 Features
- ✅ **Smooth gameplay** (No flickering, optimized screen updates)
- 🎨 **Classic 20x10 grid with spacing for better visuals**
- 🎚️ **Multiple difficulty levels** (Easy, Medium, Hard)
- 🎯 **Rotating, moving, and hard-dropping tetrominoes**
- 🏆 **Score tracking** with high-score comparison
- 🖥️ **Fully playable in the Windows Command Prompt**

---

## 🎮 Controls 🎯
| 🔑 Key | 🎭 Action |
|------|----------------|
| `A` / Left Arrow ⬅️ | Move Left |
| `D` / Right Arrow ➡️ | Move Right |
| `S` / Down Arrow ⬇️ | Soft Drop |
| `Space` ⏬ | Hard Drop |
| `E` 🔄 | Rotate Right |
| `Q` 🔄 | Rotate Left |
| `ESC` ❌ | Quit Game |

---

## 🛠 Installation & Usage 📥
### 🏁 Windows
1. **Clone or Download** the repository.
2. Open a terminal (`cmd` or `PowerShell`).
3. Compile the code using **MinGW g++**:
   ```sh
   g++ main.cpp -o tetris.exe -static-libgcc -static-libstdc++
   ```
4. Run the game:
   ```sh
   tetris.exe
   ```

### 🐧 Linux
1. Clone the repository.
2. Install `g++` if not installed:
   ```sh
   sudo apt install g++
   ```
3. Compile and run:
   ```sh
   g++ main.cpp -o tetris
   ./tetris
   ```

---

## 🖥️ Gameplay Preview 🎥
```
<>  #  #     #  #
<>  #        #  #
<>  #  #     #  #
<>  #        #  #
```
---

## 📜 Code Explanation 🧑‍💻
### **Optimized Rendering (No Flickering) 🚀**
Instead of `system("cls")`, we use:
```cpp
WriteConsoleOutput(hConsole, screenBuffer, bufferSize, {0, 0}, &windowSize);
```
This method updates only the required part of the screen, making the game smooth.

### **Double Buffering for Efficient Updates**
The game screen is drawn **in memory first**, then rendered to avoid tearing:
```cpp
static CHAR_INFO screenBuffer[22 * 23];
```

---

## 🤝 Collaborators 🏆
- 👨‍💻 **Tirth Patel** (Lead Developer)

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
