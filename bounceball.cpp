// Bouncing Ball with Catcher program version 4
// (c) 2020/2021/2022 by Engr. Andre Nixon Delgado
//
// Filename: bouncingBallwithCatcherForECPE202Sample2022.cpp

#include <iostream>
#include <conio.h>

#include "ecpe202.h"

using namespace std;

const int maxCol = 120; // screen or window dimension as shown in windows properties
const int maxRow = 30;
const int catcherLength = 20;
int life = 5, score = 0;

struct catcherstruct
{
   int col;
   int row;
   int length;
};

void initBall(ballstruct &B, int initRowPos, int initColPos, bool initDirDown, bool initDirRight, int delay);
void processBall(ballstruct &B);
void processCatcher(catcherstruct &C, char ch);
void createCatcher(catcherstruct &C, int row, int col, int length);
void showCatcher(catcherstruct &C);
void hideCatcher(catcherstruct &C);

int main()
{

   ballstruct curBall;
   catcherstruct myCatcher;

   clearScreen();
   gotoxy(0, 29);
   cout << "Life: " << life;
   gotoxy(50, 29);
   cout << "Score: " << score;

   //createBQ(ballQ);

   // initialize ball and add to the Ball Queue

   createCatcher(myCatcher, 28, (maxCol - catcherLength) / 2, catcherLength); // length of the catcher here is 20
   showCatcher(myCatcher);

   initBall(curBall, 0, 0, true, true, 5000); // 5000 as slowest is alright for my computer, 1500 is fastest

   // Ball Movement Scheduler
   while (FOREVER)
   {
      if (kbhit())
      { // Detect a key press
         char ch = getch();
         if (ch == 'q' || ch == 'Q' || ch == '\x1B') // quit when Q is pressed or <ESC> ASCII 1B hex
            break;
         else if (ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D')
            processCatcher(myCatcher, ch); // move the Ball Catcher
         else if (ch == -32)
         { // for Arrows Key and Function Keys  (arrow UP is 72, arrow DOWN is 80
            ch = getch();
            switch (ch)
            {
            case 75:
               ch = 'a'; // ASCII code 75 is Arrow Left
               processCatcher(myCatcher, ch);
               break;
            case 77:
               ch = 'd'; // ASCII code 77 is Arrow Right
               processCatcher(myCatcher, ch);
               break;
            }
         }
      }

      // Retrieve ball from Ball Queue

      // Process ball (retrieved from Ball Queue) for bouncing schedule
      processBall(curBall);

      // Add ball back to Ball Queue
   }

   return 0;
}

void initBall(ballstruct &B, int initRowPos, int initColPos, bool initDirDown, bool initDirRight, int delay)
{
   B.curRow = initRowPos;
   B.curCol = initColPos;
   B.curDirDown = initDirDown;
   B.curDirRight = initDirRight;
   B.delay = delay;
   B.curDelayCount = 0;
}

void processBall(ballstruct &B)
{
   B.curDelayCount++;
   if (B.curDelayCount >= B.delay)
   {                              // next move
      gotoxy(B.curCol, B.curRow); // clear ball
      cout << " ";
      if ((B.curDirDown == false) && (B.curDirRight == true))
      {
         if (B.curRow == 0)
         { // Vertical Direction Component: bounce at row 0
            B.curRow++;
            B.curDirDown = true;
         }
         else
            B.curRow--; // keep going up
         if (B.curCol == maxCol - 1)
         { // Horizontal Direction Component: if maxCow is 120, bounce at col 119 because col starts at 0
            B.curCol--;
            B.curDirRight = false;
         }
         else
            B.curCol++; // keep going rightward
      }
      else if ((B.curDirDown == false) && (B.curDirRight == false))
      {
         if (B.curRow == 0)
         { // Vertical Direction Component: bounce at row 0
            B.curRow++;
            B.curDirDown = true;
         }
         else
            B.curRow--; // keep going up
         if (B.curCol == 0)
         { // Horizontal Direction Component: bounce at col 0
            B.curCol++;
            B.curDirRight = true;
         }
         else
            B.curCol--; // keep going leftward
      }
      else if ((B.curDirDown == true) && (B.curDirRight == true))
      {
         if (B.curRow == maxRow - 2)
         { // Vertical Direction Component: if maxRow is 30, bounce at row 28
            B.curRow--;
            B.curDirDown = false;
            life--;
            gotoxy(0, 29);
            cout << "Life: " << life;
            gotoxy(50, 29);
            cout << "Score: " << score;
         }
         else
            B.curRow++; // keep going down
         if (B.curCol == maxCol - 1)
         { // Horizontal Direction Component: if maxCow is 120, bounce at col 119 because col starts at 0
            B.curCol--;
            B.curDirRight = false;
         }
         else
            B.curCol++; // keep going rightward
      }
      else if ((B.curDirDown == true) && (B.curDirRight == false))
      {
         if (B.curRow == maxRow - 2)
         { // Vertical Direction Component: if maxRow is 30, bounce at row 28
            B.curRow--;
            B.curDirDown = false;
         }
         else
            B.curRow++; // keep going down
         if (B.curCol == 0)
         { // Horizontal Direction Component: bounce at col 0
            B.curCol++;
            B.curDirRight = true;
         }
         else
            B.curCol--; // keep going leftward
      }
      gotoxy(B.curCol, B.curRow); // show the ball in new position now
      cout << "0";
      gotoxy(0, 0); // move the cursor away from the ball

      B.curDelayCount = 0; // reset Delay Counter after the ball has moved
   }
}

void showCatcher(catcherstruct &C)
{
   gotoxy(C.col, C.row);
   for (int i = 1; i <= C.length; i++)
      cout << "=";
}
void hideCatcher(catcherstruct &C)
{
   gotoxy(C.col, C.row);
   for (int i = 1; i <= C.length; i++)
      cout << " ";
}

void createCatcher(catcherstruct &C, int row, int col, int length)
{
   C.row = row;
   C.col = col;
   C.length = length;
}

void processCatcher(catcherstruct &C, char ch)
{
   switch (ch)
   {
   case 'a':
   case 'A':
      if (C.col > 0)
      {
         gotoxy(C.col, C.row);
         hideCatcher(C);
         C.col--;
         gotoxy(C.col, C.row);
         showCatcher(C);
      }
      break;
   case 'd':
   case 'D':
      if (C.col < maxCol - C.length)
      {
         gotoxy(C.col, C.row);
         hideCatcher(C);
         C.col++;
         gotoxy(C.col, C.row);
         showCatcher(C);
      }
      break;
   }
}
