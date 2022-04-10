#include "dos.h"
#include<windows.h>
#define MAXSTACK 100
#define FOREVER TRUE
#define MAXQUEUE 200

using namespace std;

struct ballstruct {
    int curCol, curRow;
    int delay; // speed
    int curDelayCount;
    bool curDirDown, curDirRight;
    char directionX, directionY;
};

void gotoxy(int x, int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void clearScreen()   {
    system("CLS");
}
