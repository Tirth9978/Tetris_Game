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
     protected : 
          int width ;
          int height ;
          vector<vector<int>> grid ;
          int score;
          bool isGameOver;

     public : 
          Game(){
               this->width = 10;
               this->height = 20;
               this->grid.resize(this->height , vector<int> (this->width,0));
               this->score = 0;
               this->isGameOver = false;
          }
};

class TetrisPieces : public Game { 
     protected : 
          int pieceX ;
          int pieceY ;
          vector<vector<vector<int>>> tetrominoes ;
          vector<vector<int>> currPiece;

     public : 
          TetrisPieces(){
               this->tetrominoes = {
                    {{1, 1, 1, 1}},              // I shape
                    {{1, 1}, {1, 1}},            // O shape
                    {{0, 1, 0}, {1, 1, 1}},      // T shape
                    {{0, 1, 1}, {1, 1, 0}},      // S shape
                    {{1, 1, 0}, {0, 1, 1}},      // Z shape
                    {{1, 0, 0}, {1, 1, 1}},      // L shape
                    {{0, 0, 1}, {1, 1, 1}}       // J shape
               };
          }

          void Generete() {
               int index = rand() % (int)tetrominoes.size();
               this->currPiece = tetrominoes[index];
               this->pieceX = (this->width/2) - (this->currPiece[0].size()/2);
               this->pieceY = 0;
          }

};

class Main : public TetrisPieces {
     protected :

     public : 
          void Main_Board(){
               for (int i=0;i<this->grid.size();i++){
                    for (int j=0;j<this->grid[0].size();j++){
                         
                    }
               }
          }
};

int main(){
     srand(time(NULL));
     return 0;
}