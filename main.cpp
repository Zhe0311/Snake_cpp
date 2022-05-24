#include "snake.h"
#include<iostream>

int main(void) {
    chessBoard myChessBoard;
    myChessBoard.prt(1,2,4);
    snake s;
    s.beginGame();
    return 0;
}
