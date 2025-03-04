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
		vector<vector<int>> board ;
		int Score ;
		bool isGameOver ;

	public : 
		Game(){
			this->width = 10;
			this->height = 20;
			board.resize(this->height,vector<int> (this->width,0));
			this->Score = 0;
			this->isGameOver = 0;
		}
};	

class Tetrominoes : public Game {
	protected : 
		vector<vector<vector<int>>> tetrominoes = {
			{{1, 1, 1, 1}}, // I
			{{1, 1}, {1, 1}}, // O
			{{0, 1, 0}, {1, 1, 1}}, // T
			{{0, 1, 1}, {1, 1, 0}}, // S
			{{1, 1, 0}, {0, 1, 1}}, // Z
			{{1, 0, 0}, {1, 1, 1}}, // J
			{{0, 0, 1}, {1, 1, 1}} // L
		};
		int curPiece;
		int x , y;
		vector<vector<int>> Piece ;

	public :
		Tetrominoes(){
			this->curPiece = rand() % (int) tetrominoes.size();
			Piece = tetrominoes[this->curPiece];
		}

	
};

class Main : public Tetrominoes  { 
	protected :
	
	public : 
		void Main_Board(){
			system(CLEAR);
			vector<vector<int>> TempBoard = this->board;

			for (int i=0;i<this->Piece.size();i++){
				for (int j=0;j<this->Piece[i].size();i++){
					if (this->Piece[i][j]){
						TempBoard[this->y+i][this->x+j] = this->Piece[i][j];
					}
				}
			}
			for (int i=0;i<this->height;i++){
				for (int j=0;j<this->width;i++){
					if (TempBoard[i][j]){
						cout << "#" << " ";
					}
					else {
						cout << "  "; 
					}
				}
				cout << endl;
			}
		}

		bool validMove(int a,int b){
			for (int i=0;i<this->Piece.size();i++){
				for (int j=0;j<this->Piece[i].size();j++){
					if (Piece[i][j]){
						int newX = j + a + x;
						int newY = i + b + y;
						if (newX < 0 || newX >= this->width || newY >= this->height || board[newY][newX]){
							return false;
						}
					}
				}
			}
			return true;
		}

		void MovePiece(int a){
			if (validMove(a,0)){
				this->x+=a;
			}
		}
};	

int main(){
	srand(time(NULL));

	return 0;
}