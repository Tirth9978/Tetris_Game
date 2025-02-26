#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<vector>
#include<map>

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

class position{
     public :  
          int row , column;
          position(int row,int column){
               this->row = row;
               this->column = column;
          }
};   

class Game{
     protected  :
          int width;
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

          void ref(){
          }
};

class Blocks : public Game {

     protected :
          vector<vector<pair<int,int>>> block;
          vector<pair<int,int>> curr;
     public : 
          Blocks(){
               this->block = {
                    {{0,4},{0,5},{1,4},{1,5}},
                    {{0,4},{0,5},{0,6},{1,5}},
                    {{0,4},{1,4},{2,4},{3,4}},
                    {{0,5},{1,5},{2,5},{2,4}},
                    {{0,5},{1,5},{2,5},{2,6}},
                    {{0,3},{0,4},{1,4},{1,5}},
                    {{0,5},{0,6},{1,5},{1,4}},
               };
          }
          void Generate(){
               int idx = rand() % (int)this->block.size();
               curr = block[idx];
          }    

};

class Main : public Blocks {
     public :
          void Main_Board(){
               cout << "----------" << endl;;
               int k=0;

               for (int i=0;i<20;i++){
                    for (int j=0;j<10;j++){
                         if (i == curr[k].first && j == curr[k].second){
                              cout << "T";
                              k++;
                         }
                         else cout << " ";
                    }
                    cout << endl;
               }
               cout << "----------" << endl;;
          }
};

int main(){
     srand(time(NULL));
     Main m;
     Blocks b;
     b.Generate();
     m.Main_Board();
     return 0;
}