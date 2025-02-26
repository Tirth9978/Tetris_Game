#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std ;


#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>   
    #include<windows.h>
    // #include<mmsystem.h>
    // #pragma comment(lib, "winmm.lib")
    #define CLEAR "cls"

#else 
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #define CLEAR "clear"

    int _kbhit() {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }

    int _getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();

        if (ch == 27) {
            if (getchar() == '[') {
                switch (getchar()) {
                    case 'A': ch = 'w'; break;  // Up Arrow
                    case 'B': ch = 's'; break;  // Down Arrow
                    case 'C': ch = 'd'; break;  // Right Arrow
                    case 'D': ch = 'a'; break;  // Left Arrow
                }
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

#endif

class Game {
    private :
        vector<vector<int>> grid;
        vector<vector<int>> curPiece;
        int width;
        int height;
        int pieceX;
        int pieceY;
        int score;
        bool isGameOver;
        vector<vector<vector<int>>> tetrominoes ;

    public : 
        Game(){
            this->width = 10;
            this->height = 20;
            this->grid.resize(this->height, vector<int> (this->width, 0));
            this->score = 0;
            this->isGameOver = false;
            this->tetrominoes = {
                {{1, 1, 1, 1}},              // I shape
                {{1, 1}, {1, 1}},            // O shape
                {{0, 1, 0}, {1, 1, 1}},      // T shape
                {{0, 1, 1}, {1, 1, 0}},      // S shape
                {{1, 1, 0}, {0, 1, 1}},      // Z shape
                {{1, 0, 0}, {1, 1, 1}},      // L shape
                {{0, 0, 1}, {1, 1, 1}}       // J shape
            };
            generateTetrominoes();
        }

        void generateTetrominoes(){
            int idx = rand() % (int)tetrominoes.size();
            this->curPiece = tetrominoes[idx];
            this->pieceX = (this->width/2) - (this->curPiece[0].size()/2);
            this->pieceY = 0;
            if (isColliding(this->pieceX,this->pieceY,this->curPiece)) {
                
            }
        }

        bool isColliding(int X,int Y,vector<vector<int>> piece){
            for(int i=0;i<piece.size();i++){
                for (int j=0;j<piece[0].size();j++){
                    if (piece[i][j]==1){
                        int currX = j+X;
                        int currY = i+Y;
                        if (currX < 0 || currX >= this->width || currY>=this->height){
                            return true;
                        }
                        if (currY > 0 && grid[currY][currX] == 1){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
};

int main(){
    srand(time(NULL));

    return 0;
}