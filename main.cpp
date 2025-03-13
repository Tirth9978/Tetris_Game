#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<map>
// #include<windows.h>
#include <chrono>
#include <thread>

// using namespace std::thread;
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
        string name; 

		Game() {
			this->width = 10;
			this->height = 20;
			board.resize(this->height,vector<int> (this->width,0));
			this->Score = 0;
			this->isGameOver = 0;
            // this->name = str ;
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
		vector<vector<int>> Piece;

	public :
		Tetrominoes() {
			this->curPiece = rand() % (int) tetrominoes.size();
			Piece = tetrominoes[this->curPiece];
            this->x = (this->width/2)-1;
            this->y=0;
		}
};

class Main : public Tetrominoes {
    public : 
    
        #if defined(_WIN32) || defined(_WIN64)
            void Main_Board(int maxScore) {
                static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                static SMALL_RECT windowSize = {0, 0, 20 * 2 + 2, 20 + 3}; // Grid size (20x10) with spacing
                static COORD bufferSize = {22 * 2, 23};  // Buffer size (width + padding)
                static CHAR_INFO screenBuffer[22 * 2 * 23]; // Screen buffer

                // Clear buffer
                for (int i = 0; i < 22 * 2 * 23; i++) {
                    screenBuffer[i].Char.AsciiChar = ' ';
                    screenBuffer[i].Attributes = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
                }

                // Draw game border
                for (int i = 0; i < height; i++) {
                    screenBuffer[i * (22 * 2)].Char.AsciiChar = '<';
                    screenBuffer[i * (22 * 2) + width * 2 + 1].Char.AsciiChar = '>';
                }
                for (int i = 0; i < width * 2 + 2; i++) {
                    screenBuffer[i].Char.AsciiChar = '<';
                    screenBuffer[(height) * (22 * 2) + i].Char.AsciiChar = '>';
                }

                // Copy game board to buffer (with spacing)
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        if (board[i][j]) {
                            screenBuffer[i * (22 * 2) + (j * 2) + 1].Char.AsciiChar = '#';
                            screenBuffer[i * (22 * 2) + (j * 2) + 2].Char.AsciiChar = ' ';  // Space for better visibility
                            screenBuffer[i * (22 * 2) + (j * 2) + 1].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
                        }
                    }
                }

                // Copy Tetromino piece to buffer (with spacing)
                for (int i = 0; i < Piece.size(); i++) {
                    for (int j = 0; j < Piece[i].size(); j++) {
                        if (Piece[i][j]) {
                            int posX = x + j;
                            int posY = y + i;
                            screenBuffer[posY * (22 * 2) + (posX * 2) + 1].Char.AsciiChar = '#';
                            screenBuffer[posY * (22 * 2) + (posX * 2) + 2].Char.AsciiChar = ' ';  // Add space between blocks
                            screenBuffer[posY * (22 * 2) + (posX * 2) + 1].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        }
                    }
                }

                // Display score
                string scoreText = "Score: " + to_string(Score);
                string maxScoreText = "Max: " + to_string(maxScore);
                for (int i = 0; i < scoreText.size(); i++) {
                    screenBuffer[(height + 1) * (22 * 2) + 2 + i].Char.AsciiChar = scoreText[i];
                }
                for (int i = 0; i < maxScoreText.size(); i++) {
                    screenBuffer[(height + 2) * (22 * 2) + 2 + i].Char.AsciiChar = maxScoreText[i];
                }

                // Write buffer to console (flicker-free)
                WriteConsoleOutput(hConsole, screenBuffer, bufferSize, {0, 0}, &windowSize);
            }

        #else 

        void Main_Board(int maxScore) {

            system(CLEAR);
            vector<vector<int>> tempBoard = board;
            
            for (int i=0; i<Piece.size(); i++) {
                for (int j=0; j<Piece[i].size(); j++) {
                    if (Piece[i][j]) {
                        tempBoard[y+i][x+j] = Piece[i][j];  
                    }
                }
            }   

            cout << "<><><><><><><><><><><><>\n";

            for (int i=0; i<this->height; i++) {
                cout<<"<>";

                for (int j=0; j<this->width; j++) {
                    if (tempBoard[i][j]) {
                        cout << "#" << " ";
                    }
                    else {
                        cout<<"  "; 
                    }
                }

                cout<<"<>";
                if (i==2) cout << "      --------------------------------------";
                if (i==3) cout << "      | a : Move Left    | d : Move Right  |" ;
                if (i==4) cout << "      | e : Rotate Right | q : Rotate Left |";
                if (i==5) cout << "      | Space : Hard Drop|Esc: Exit        |";
                if (i==6) cout << "      ---------*---------*--------*---------";

                if (i==7) cout << "      | "<<this->name<<"'s Score : " << this->Score ;
                if (i==8) cout << "      | "<<this->name<<"'s MaxScore : " << maxScore ;

                cout << endl;
            }

            cout << "<><><><><><><><><><><><>\n";
        } 

        #endif 
        

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
                    this->Score += 5;
                    i++; 
                }
            }
        }

        bool validMove(int dx,int dy,vector<vector<int>> newPiece = {}) {
            if (newPiece.empty()) newPiece = Piece;

            for (int i=0; i<Piece.size(); i++) {
                for (int j=0; j<Piece[i].size(); j++) {
                    if (Piece[i][j]) {
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

        void movePiece(int dx) {
            if (validMove(dx,0)) {
                x = x + dx;
            }
        }

        void dropPiece() {
            if (validMove(0,1)) {
                y++;
            }
            else {
                placePiece();
                spawnNewPiece();
            }
        }

        void placePiece() {
            for (int i=0; i<Piece.size(); i++) {
                for (int j=0; j<Piece[i].size(); j++) {
                    if (Piece[i][j]) {
                        board[i+y][x + j] = Piece[i][j];
                    }
                }
            }
            clearFullRows();
            spawnNewPiece();
        }

        void spawnNewPiece() {
            curPiece = rand() % (int)this->tetrominoes.size();
            Piece = tetrominoes[this->curPiece];

            x = (this->width/2)-1;
            y = 0;

            if (!validMove(0,0,Piece)) {
                // cout << "Over \n";
                this->isGameOver=1;
                // exit(0);
            }
        }

        vector<vector<int>> RotateRight(vector<vector<int>> mat) {
            int row = mat.size();
            int col = mat[0].size();

            vector<vector<int>> temp(col,vector<int> (row));

            for (int i=0; i<row; i++) {
                for (int j=0; j<col; j++) {
                    temp[j][row-i-1] = mat[i][j];
                }
            }

            return temp;
        }

        vector<vector<int>> RotateLeft(vector<vector<int>> mat) {
            int row = mat.size();
            int col = mat[0].size();

            vector<vector<int>> temp(col , vector<int>(row));

            for (int i=0; i<row; i++) {
                for (int j=0; j<col; j++) {
                    temp[col-j-1][i]=mat[i][j];
                }
            }

            return temp;
        }

        void hardDrop() {
            while (validMove(0, 1)) {  
                y++;
            }

            placePiece();
            spawnNewPiece();
        }

        void rotatePiece(bool Anticlockwise) {
            vector<vector<int>> Rotated ;

            if (Anticlockwise) {
                Rotated = RotateLeft(Piece);
            }
            else {
                Rotated = RotateRight(Piece);
            } 
            
            if (validMove(0, 0, Rotated)) {
                Piece = Rotated;
            }
        }

        void User_Input() {

            if (_kbhit()) {
                
                char ch = _getch();

                if (ch == 27) {
                    this->isGameOver = 1;
                }
                if (ch == 'a' || ch == 75) {
                    movePiece(-1);
                }
                if (ch == 'd' || ch == 77) {
                    movePiece(1);
                }
                if (ch == 's' || ch == 80) {
                    dropPiece();
                }
                if (ch == 'e') {
                    rotatePiece(false);  // Rotate right
                }
                if (ch == 'q') {
                    rotatePiece(true); // Rotate left
                }
                if (ch == ' ') {
                    hardDrop();
                }
            }
        }

        bool IsOver() {
            return this->isGameOver;
        }

        void Com(int &Max) {
            if (Max < Score) {
                Max = this->Score;
            }
            return ;
        }

        void SpeedContorl(int &diff) {
            diff-=10;
        }

        int getScore() {
            return this->Score;
        }
};

// Loading Animation part 
void animation(string name) {
    
    system(CLEAR);

    cout << "\n\n\n";
    cout << "          *************************************************************************\n\n";
    cout << "                                      T E T R I S  G A M E\n\n";
    cout << "                                      Get Ready, " << name << "..!!\n\n";
    cout << "          *************************************************************************\n\n\n\n\n\n\n";

    cout << "                                    L O A D I N G ";
    
    for (int i = 0; i < 5; i++) {
        cout << "." << flush;

        #if defined(_WIN32) || defined(_WIN64)
            Sleep(700);
        #else
             usleep(750 * 1000);
        #endif
    }

    for (int i = 3; i >= 0; i--) {
        system(CLEAR);

        cout << "\n\n\n\n\n";
        cout << "\r                                    Starting in:\n\n\n";

        if(i == 3) {
            cout << R"(
                                         ____
                                        |___ \ 
                                          __) |  
                                         |__ <    
                                         ___) |    
                                        |____/     
            )" << flush;

            #if defined(_WIN32) || defined(_WIN64)
                Sleep(900); // Delay so the user can see the countdown
            #else
                usleep(900 * 1000);
            #endif

        } 
        else if(i == 2) {
            cout << R"(
                                        ______
                                       / ____ \
                                       \/   / /
                                           / / 
                                          / /___
                                         /______| 
            )" << flush;

            #if defined(_WIN32) || defined(_WIN64)
                Sleep(900); // Delay so the user can see the countdown
            #else
                usleep(900 * 1000);
            #endif

        } else if(i == 1) {
            cout << R"(
                                          _ 
                                         / |
                                         | |
                                         | |
                                         | |
                                         |_|
            )" << flush;

            #if defined(_WIN32) || defined(_WIN64)
                Sleep(900); // Delay so the user can see the countdown
            #else
                usleep(900 * 1000);
            #endif

        } else {
            system(CLEAR);
            cout << "\n\n\n\n\n\n" R"(
                          _____   _______      __      _____     _______ 
                         / ____| |_______|    /  \     |  __ \  |_______|
                        | (___      | |      / _  \    | |__) |    | |
                         \___ \     | |     / / \  \   |  _  /     | |
                         ____) |    | |    /  ____  \  | | \ \     | |
                        |_____/     |_|   /__/    \__\ |_|  \_\    |_|
            )" << flush;
            
            #if defined(_WIN32) || defined(_WIN64)
                Sleep(900); // Delay so the user can see the countdown
            #else
                usleep(900 * 1000);
            #endif

        }

        // system(CLEAR);

        // #if defined(_WIN32) || defined(_WIN64)
        //     Sleep(2000);
        // #else
        //      usleep(2000 * 1000);
        // #endif
    }
    system(CLEAR);
}

int main() {
    // cout << "\033[2J\033[H";
    system(CLEAR);

    cout << "\n\n\n";
    cout << "          **************************************************************************************\n\n";
    cout << "                                 W E L C O M E  T O  T E T R I S  G A M E ! !\n\n";
    cout << "          **************************************************************************************\n\n\n\n";
    
    string str;
    cout << "\n\nEnter your Name : ";
    getline(cin, str);

    int diff = 0;

    cout << "\n\n";
    cout << "Difficulty Levels : " << endl;
    cout << "1. Easy\n2. Medium\n3. Hard\n\n";
    cout << "NOTE : If You Press Key Other than 1, 2 or 3 then Difficulty Will Set Automatically to Medium..\n\n";
    cout << "Set Difficulty Level : ";
    cin >> diff;

    if(diff == 3) {
        diff = 200;
    } else if(diff == 2) {
        diff = 300;
    } else if(diff == 1) {
        diff = 400;
    } else {
        diff = 300;
    }
    cout <<"\n\n";

    srand(time(NULL)); 

    int play = 1;

    while(play) {

        Main game;
        game.name=str;

        animation(str);

        int maxScore = 0;
        
        while(!game.IsOver()) {

            game.User_Input();
            game.Main_Board(maxScore);
            game.dropPiece();
            game.Com(maxScore);

            
            #if defined(_WIN32) || defined(_WIN64)
                Sleep(diff);

            #else 
                usleep(diff*1000);

            #endif


        }
        
        system(CLEAR);

        cout << "\n\n\n";
        cout << R"(
                              _____                         ____                 
                             / ____|                       / __ \                
                            | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
                            | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
                            | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
                             \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   
        )" << "\n\n\n\n\n";

        cout << "                                        ";
        cout << "G A M E  O V E R  ! ! ! \n\n\n\n\n";

        #if defined(_WIN32) || defined(_WIN64)
            Sleep(400);

        #else 
            usleep(400000);

        #endif

        // cout << "Your Highest Score : " << max_score << "\n\n\n";
        cout << "\n\nDo You Want To Play Again..?\n\n";
        cout << "NOTE : If You Press Key Other Than 0 or 1 Then Computer will treat it as 0..\n";
        cout << "Enter 1 For \"YES\" and 0 For \"NO\" : ";

        cin >> play;
    }
    
    return 0;
}
