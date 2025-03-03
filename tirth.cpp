#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// Tetromino shapes
vector<vector<vector<int>>> tetrominoes = {
    {{1, 1, 1, 1}}, // I
    {{1, 1}, {1, 1}}, // O
    {{0, 1, 0}, {1, 1, 1}}, // T
    {{0, 1, 1}, {1, 1, 0}}, // S
    {{1, 1, 0}, {0, 1, 1}}, // Z
    {{1, 0, 0}, {1, 1, 1}}, // J
    {{0, 0, 1}, {1, 1, 1}} // L
};

class Tetris {
private:
    vector<vector<int>> board;
    int currentPiece, x, y;
    vector<vector<int>> piece;

public:
    Tetris() : board(HEIGHT, vector<int>(WIDTH, 0)), x(WIDTH / 2 - 1), y(0) {
        currentPiece = rand() % tetrominoes.size();
        piece = tetrominoes[currentPiece];
    }

    void drawBoard() {
        system("cls");
        vector<vector<int>> tempBoard = board;
        
        for (int i = 0; i < piece.size(); i++) {
            for (int j = 0; j < piece[i].size(); j++) {
                if (piece[i][j]) {
                    tempBoard[y + i][x + j] = piece[i][j];
                }
            }
        }

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cout << (tempBoard[i][j] ? "#" : ".") << " ";
            }
            cout << endl;
        }
    }

    bool isValidMove(int dx, int dy) {
        for (int i = 0; i < piece.size(); i++) {
            for (int j = 0; j < piece[i].size(); j++) {
                if (piece[i][j]) {
                    int newX = x + j + dx;
                    int newY = y + i + dy;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || board[newY][newX]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void movePiece(int dx) {
        if (isValidMove(dx, 0)) {
            x += dx;
        }
    }

    void dropPiece() {
        if (isValidMove(0, 1)) {
            y++;
        } else {
            placePiece();
            spawnNewPiece();
        }
    }

    void placePiece() {
        for (int i = 0; i < piece.size(); i++) {
            for (int j = 0; j < piece[i].size(); j++) {
                if (piece[i][j]) {
                    board[y + i][x + j] = piece[i][j];
                }
            }
        }
    }

    void spawnNewPiece() {
        currentPiece = rand() % tetrominoes.size();
        piece = tetrominoes[currentPiece];
        x = WIDTH / 2 - 1;
        y = 0;
        if (!isValidMove(0, 0)) {
            cout << "Game Over!" << endl;
            exit(0);
        }
    }

    vector<vector<int>> rotateRight(const vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated[j][rows - i - 1] = mat[i][j];
            }
        }
        return rotated;
    }

    vector<vector<int>> rotateLeft(const vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated[cols - j - 1][i] = mat[i][j];
            }
        }
        return rotated;
    }

    void rotatePiece(bool clockwise) {
        vector<vector<int>> rotated = clockwise ? rotateRight(piece) : rotateLeft(piece);
        if (isValidMove(0, 0)) {
            piece = rotated;
        }
    }

    void gameLoop() {
        while (true) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 27) break;
                if (ch == 'a' || ch == 75) movePiece(-1);
                if (ch == 'd' || ch == 77) movePiece(1);
                if (ch == 's' || ch == 80) dropPiece();
                if (ch == 'e') rotatePiece(true);  // Rotate right
                if (ch == 'q') rotatePiece(false); // Rotate left
            }
            dropPiece();
            drawBoard();
            Sleep(500);
        }
    }
};

int main() {
    Tetris game;
    game.gameLoop();
    return 0;
}