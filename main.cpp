#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
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
                case 'A':
                    ch = 'w';
                    break; // Up Arrow
                case 'B':
                    ch = 's';
                    break; // Down Arrow
                case 'C':
                    ch = 'd';
                    break; // Right Arrow
                case 'D':
                    ch = 'a';
                    break; // Left Arrow
                }
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

#endif

class Game {

    protected:
        int width;
        int height;
        vector<vector<int>> board;
        int Score;
        bool isGameOver;

    public:
        Game() {
            this->width = 10;
            this->height = 20;
            board.resize(this->height, vector<int>(this->width, 0));
            this->Score = 0;
            this->isGameOver = 0;
        }
};

class Tetrominoes : public Game {
    protected:
        vector<vector<vector<int>>> tetrominoes = {
            {{1, 1, 1, 1}},         // I
            {{1, 1}, {1, 1}},       // O
            {{0, 1, 0}, {1, 1, 1}}, // T
            {{0, 1, 1}, {1, 1, 0}}, // S
            {{1, 1, 0}, {0, 1, 1}}, // Z
            {{1, 0, 0}, {1, 1, 1}}, // J
            {{0, 0, 1}, {1, 1, 1}}  // L
        };
        int curPiece;
        int x, y;
        vector<vector<int>> Piece;

    public:
        Tetrominoes() {
            this->curPiece = rand() % (int)tetrominoes.size();
            Piece = tetrominoes[this->curPiece];
        }
};

class Main : public Tetrominoes {
    protected:
    public:
        void Main_Board() {
            system(CLEAR);
        }
};

// Loading Animation part 
void animation(string name) {
    system(CLEAR);

    cout << "\n\n\n";
    cout << "          *************************************************************************\n\n";
    cout << "                                      S N A K E  G A M E\n\n";
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
        } else if(i == 2) {
            cout << R"(
                                        ______
                                       / ____ \
                                       \/   / /
                                           / / 
                                          / /___
                                         /______| 
            )" << flush;
        } else if(i == 1) {
            cout << R"(
                                          _ 
                                         / |
                                         | |
                                         | |
                                         | |
                                         |_|
            )" << flush;
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
        }

        #if defined(_WIN32) || defined(_WIN64)
            Sleep(900);
        #else
             usleep(950 * 1000);
        #endif
    }
}

int main() {
     
    system(CLEAR);

    cout << "\n\n\n";
    cout << "          **************************************************************************************\n\n";
    cout << "                                 W E L C O M E  T O  T E T R I S  G A M E ! !\n\n";
    cout << "          **************************************************************************************\n\n\n\n";
    
    string name;
    cout << "\n\nEnter your Name : ";
    getline(cin, name);

    srand(time(NULL)); // Like Seed For rand() Function;

    // Game Part;

    cout << "\n\n\n\n\nOkay, Byee...  ";

    cout << "Thank You " << name << " For Playing Our Game..!!\n\n\n\n";

    return 0;
}
