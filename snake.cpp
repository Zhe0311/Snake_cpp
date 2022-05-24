#include "snake.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>

chessBoard::chessBoard(int size) {
    boardSize_ = size;
    board_ = new char*[size];
    for (int i = 0; i < size; i++){
        board_[i] = new char[size];
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size-1 || j == 0 || j == size-1) {
                board_[i][j] = '#';
            }
            else board_[i][j] = ' ';
        }
    }
    addFood();
}

void chessBoard::addFood() {
    srand(time(0));
    int x = 0;
    int y = 0;
    do {
        x = rand() % (boardSize_-3) + 1;
        y = rand() % (boardSize_-3) + 1;
    } while (board_[x][y] != ' ');
    board_[x][y] = '$';
    food_.first = x;
    food_.second = y;
}

void chessBoard::prt(int grade,int score,int gameSpeed)
{
    system("clear");
    std::cout << std::endl;
    for(int i = 0; i < boardSize_; i++)
    {
        std::cout << "\t";
        for(int j = 0; j < boardSize_; j++)
            std::cout << board_[i][j] << ' ';
        if(i==0) std::cout << "\tGrade:" << grade;
        if(i==2) std::cout << "\tScore:" << score;
        std::cout << std::endl;
    }
}

snake::snake() {
    auto startTime = clock();
    while (clock() - startTime <= 3 * 1000);
    system("clear");
    for (int i = 1; i <= 3; i++) {
        board_[1][i] = '*';
        position_.push(std::make_pair(1, i));
    }
    board_[1][4] = '@';
    position_.push(std::make_pair(1, 4));
    len_ = 4;
}

bool snake::move(char direction) {
    auto head = position_.back();
    int xHead = head.first;
    int yHead = head.second;
    int newXHead = 0;
    int newYHead = 0;
    switch (direction) {
        case 119: newXHead = xHead-1; newYHead = yHead; break; // w
        case 115: newXHead = xHead+1; newYHead = yHead; break; // s
        case 97: newXHead = xHead; newYHead = yHead-1; break; // a
        case 100: newXHead = xHead; newYHead = yHead+1; break; // d
    }
    if (newXHead == 0 || newXHead == boardSize_-1) return false;
    else if (newYHead == 0 || newYHead == boardSize_-1) return false;
    else if (board_[newXHead][newYHead] == '*') return false;
    else if (newXHead == food_.first && newYHead == food_.second) {
        len_ ++;
        score_ += 100;
        if (len_ % 15 == 0) {grade_ ++; moveSpeed_ = std::max(20000, moveSpeed_-5000);}
        addFood();
    }
    else {
        auto tail = position_.front();
        board_[tail.first][tail.second] = ' ';
        position_.pop();
    }
    position_.push(std::make_pair(newXHead, newYHead));
    board_[newXHead][newYHead] = '@';
    board_[xHead][yHead] = '*';
    chessBoard::prt(grade_, score_, moveSpeed_);
    return true;
}

int _kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false; if (! initialized)
    {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    } int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;

}

void snake::beginGame() {
    while (move(direction_)) {
        auto startTime = clock();
        while(((clock() - startTime) <= moveSpeed_) && (_kbhit() == 0));
        if (_kbhit() != 0)
        {
            system("stty -icanon");
            direction_ = getchar();
        }
    }
    std::cout << "GAME OVER!" << std::endl;
}