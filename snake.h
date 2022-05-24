#ifndef SNAKE_CPP_SNAKE_H
#define SNAKE_CPP_SNAKE_H

#include <iostream>
#include <vector>
#include <queue>

class chessBoard {
public:
    int boardSize_;
    char** board_; // the chess board
    int score_{0}; // total score
    int grade_{0}; // current grade
    std::pair<int, int> food_;

    chessBoard(int size=22); // initialize
    void addFood();  // add food randomly
    void prt(int grade, int score, int gameSpeed);
};

class snake : public chessBoard {
public:
    int moveSpeed_{300000}; // the speed of the snake
    char direction_{'d'}; // the moving direction of the snake
    int len_{4};
    std::queue<std::pair<int, int>> position_;

    snake(); // initialize
    bool move(char direction);
    void beginGame();
};

#endif //SNAKE_CPP_SNAKE_H