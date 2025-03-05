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
            this->x = (this->width/2)-1;
            this->y=0;
		}

};

class Main : public Tetrominoes{
    public : 
        void Main_Board(){
            system(CLEAR);
            vector<vector<int>> tempBoard = board;
            
            for (int i=0;i<Piece.size();i++){
                
                for (int j=0;j<Piece[i].size();j++){
                    // cout << "Tirth\n";
                    if (Piece[i][j]){
                        tempBoard[y+i][x+j] = Piece[i][j];  
                    }
                }
            }
            cout << "<><><><><><><><><><><><>\n";
            for (int i=0;i<this->height;i++){
                cout<<"<>";
                for (int j=0;j<this->width;j++){
                    if (tempBoard[i][j]){
                        cout << "#" << " ";
                    }
                    else {
                        cout<<"  "; 
                    }
                }
                cout<<"<>";
                cout << endl;
            }
            cout << "<><><><><><><><><><><><>\n";
        }

        void clearFullRows() {
            for (int i = height - 1; i >= 0; i--) {
                bool fullRow = true;
                for (int j = 0; j < width; j++) {
                    if (board[i][j] == 0) {
                        fullRow = false;
                        break;
                    }
                }
                if (fullRow) {
                    board.erase(board.begin() + i);
                    board.insert(board.begin(), vector<int>(width, 0));
                    this->Score += 10;
                    i++; 
                }
            }
        }

        bool validMove(int dx,int dy,vector<vector<int>> newPiece = {}){
            if (newPiece.empty()) newPiece = Piece;
            for (int i=0;i<Piece.size();i++){
                for (int j=0;j<Piece[i].size();j++){
                    if (Piece[i][j]){
                        int newX = x + j + dx;
                        int newY = y + i + dy;
                        if (newX<0 || newX >= this->width || newY>=this->height || board[newY][newX]){
                            return false ;
                        }
                    }
                }
            }
            return true ;
        }

        void movePiece(int dx){
            if (validMove(dx,0)){
                x = x + dx;
            }
        }

        void dropPiece(){
            if (validMove(0,1)){
                y++;
            }
            else {
                placePiece();
                spawnNewPiece();
            }
        }

        void placePiece(){
            for (int i=0;i<Piece.size();i++){
                for (int j=0;j<Piece[i].size();j++){
                    if (Piece[i][j]){
                        board[i+y][x + j] = Piece[i][j];
                    }
                }
            }
            clearFullRows();
            spawnNewPiece();
        }

        void spawnNewPiece(){
            curPiece = rand() % (int)this->tetrominoes.size();
            Piece = tetrominoes[this->curPiece];
            x = (this->width/2)-1;
            y=0;
            if (!validMove(0,0,Piece)){
                cout << "Over \n";
                exit(0);
            }
        }

        vector<vector<int>> RotateRight(vector<vector<int>> mat){
            int row = mat.size();
            int col = mat[0].size();
            vector<vector<int>> temp(col,vector<int> (row));
            for (int i=0;i<row;i++){
                for (int j=0;j<col;j++){
                    temp[j][row-i-1] = mat[i][j];
                }
            }
            return temp;
        }

        vector<vector<int>> RotateLeft(vector<vector<int>> mat){
            int row = mat.size();
            int col = mat[0].size();
            vector<vector<int>> temp(col , vector<int>(row)) ;
            for (int i=0;i<row;i++){
                for (int j=0;j<col;j++){
                    temp[col-j-1][i]=mat[i][j];
                }
            }
            return temp;
        }

        void rotatePiece(bool Anticlockwise){
            vector<vector<int>> Rotated ;
            if (Anticlockwise){
                Rotated = RotateLeft(Piece);
            }
            else {
                Rotated = RotateRight(Piece);
            } 
            

            if (validMove(0,0,Rotated)){
                Piece = Rotated;
            }
        }

        // void user_Input(){
        //     while(!this->isGameOver){
        //         if (_kbhit()) {
        //             char ch = _getch();
        //             if (ch == 27) this->isGameOver = 1;
        //             if (ch == 'a' || ch == 75) movePiece(-1);
        //             if (ch == 'd' || ch == 77) movePiece(1);
        //             if (ch == 's' || ch == 80) dropPiece();
        //             if (ch == 'e') rotatePiece(false);  // Rotate right
        //             if (ch == 'q') rotatePiece(true); // Rotate left
        //         }
                
                
        //         Main_Board();
        //         dropPiece();
        //         #if defined(_WIN32) || defined(_WIN64)
        //             Sleep(500);

        //         #else 
        //             usleep(500*1000);

        //         #endif
        //     }
        // }

        void User_Input(){
            if (_kbhit()){
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == 27) this->isGameOver = 1;
                    if (ch == 'a' || ch == 75) movePiece(-1);
                    if (ch == 'd' || ch == 77) movePiece(1);
                    if (ch == 's' || ch == 80) dropPiece();
                    if (ch == 'e') rotatePiece(false);  // Rotate right
                    if (ch == 'q') rotatePiece(true); // Rotate left
                }
            }
        }

};

int main(){
    Main game;
    game.User_Input();
    while(1){
        game.User_Input();
        game.Main_Board();
        game.dropPiece();
        #if defined(_WIN32) || defined(_WIN64)
            Sleep(400);

        #else 
            usleep(400*1000);

        #endif
    }
    return 0;
}