#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 
#include <conio.h> // For _kbhit() and _getch() 
 
using namespace std; 
 
const int WIDTH = 10; 
const int HEIGHT = 20; 
 
vector<vector<int>> board(HEIGHT, vector<int>(WIDTH, 0)); // Game board 
int currentPiece[4][2]; // Current piece coordinates 
int currentPieceType; 
 
// Tetrimino shapes 
const int shapes[7][4][2] = { 
    {{0, 1}, {1, 1}, {2, 1}, {1, 0}}, // T 
    {{0, 1}, {1, 1}, {1, 0}, {1, 2}}, // J 
    {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, // L 
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // O 
    {{0, 1}, {1, 1}, {1, 0}, {2, 1}}, // S 
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}}, // Z 
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}}  // I 
}; 
 
void drawBoard() { 
    system("cls"); // Clear the console 
    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            if (board[i][j] == 1) { 
                cout << "#"; 
            } else { 
                cout << "."; 
            } 
        } 
        cout << endl; 
    } 
} 
 
bool checkCollision(int dx, int dy) { 
    for (int i = 0; i < 4; i++) { 
        int x = currentPiece[i][0] + dx; 
        int y = currentPiece[i][1] + dy; 
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || board[y][x] == 1) { 
            return true; 
        } 
    } 
    return false; 
} 
 
void placePiece() { 
    for (int i = 0; i < 4; i++) { 
        int x = currentPiece[i][0]; 
        int y = currentPiece[i][1]; 
        board[y][x] = 1; // Place the piece on the board 
    } 
} 
 
void clearLines() { 
    for (int i = HEIGHT - 1; i >= 0; i--) { 
        bool fullLine = true; 
        for (int j = 0; j < WIDTH; j++) { 
            if (board[i][j] == 0) { 
                fullLine = false; 
                break; 
            } 
        } 
        if (fullLine) { 
            for (int k = i; k > 0; k--) { 
                board[k] = board[k - 1]; // Move lines down 
            } 
            board[0] = vector<int>(WIDTH, 0); // Clear top line 
            i++; // Check the same line again 
        } 
    } 
} 
 
void rotatePiece() { 
    int temp[4][2]; 
    for (int i = 0; i < 4; i++) { 
        temp[i][0] = -currentPiece[i][1]; 
        temp[i][1] = currentPiece[i][0]; 
    } 
    for (int i = 0; i < 4; i++) { 
        currentPiece[i][0] = temp[i][0]; 
        currentPiece[i][1] = temp[i][1]; 
    } 
} 
 
void spawnPiece() { 
    currentPieceType = rand() % 7; // Random piece 
    for (int i = 0; i < 4; i++) { 
        currentPiece[i][0] = shapes[currentPieceType][i][0] + WIDTH / 2; 
        currentPiece[i][1] = shapes[currentPieceType][i][1]; // Spawn at top 
    } 
} 
 
int main() { 
    srand(time(0)); // Seed random number generator 
    spawnPiece(); 
    bool gameOver = false; 
 
    while (!gameOver) { 
        drawBoard(); 
 
        if (_kbhit()) { 
            char c = _getch(); 
            if (c == 'a') { // Move left 
                if (!checkCollision(-1, 0)) { 
                    for (int i = 0; i < 4; i++) currentPiece[i][0]--; 
                } 
            } else if (c == 'd') { // Move right 
                if (!checkCollision(1, 0)) { 
                    for (int i = 0; i < 4; i++) currentPiece[i][0]++; 
                } 
            } else if (c == 's') { // Move down 
                if (!checkCollision(0, 1)) { 
                    for (int i = 0; i < 4; i++) currentPiece[i][1]++; 
                } else { 
                    placePiece(); 
                    clearLines(); 
                    spawnPiece(); 
                    if (checkCollision(0, 0)) { 
                        gameOver = true; // Game over 
                    } 
                } 
            } else if (c == 'w') { // Rotate 
                rotatePiece(); 
                if (checkCollision(0, 0)) { 
                    rotatePiece(); // Undo rotation 
                } 
            } 
        } 
 
        // Move piece down automatically 
        if (!checkCollision(0, 1)) { 
            for (int i = 0; i < 4; i++) currentPiece[i][1]++; 
        } else { 
            placePiece(); 
            clearLines(); 
            spawnPiece(); 
            if (checkCollision(0, 0)) { 
                gameOver = true; // Game over 
            } 
        } 
 
        // Sleep for a short duration (you can adjust this) 
        _sleep(100); 
    } 
 
    cout << "Game Over!" << endl; 
     return 0;
}