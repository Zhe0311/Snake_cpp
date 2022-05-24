# Snake_cpp
A snake game written in C++, which is a small exercise for reviewing C++. 

## 游戏规则说明
- 初始时等级（Grade）为0，分数（Score）为0
- 每吃到一次食物，得100分
- 随着分数的增长，等级也会逐渐提高
- 碰壁或头部碰到身体则游戏结束

## 代码说明
1. 类说明
    - chessBoard：棋盘。包括初始化，生成食物，打印......
    - snake：蛇。包括移动，吃食物......
2. 环境 \
    代码是在M1芯片的MAC上写的，由于`getch()`、`system("cls")`和`kbhit()`等函数只适用于Windows环境，本代码都用了替代的方法，所以不建议Windows环境运行。若一定要在Windows环境下运行，请将代码中这些差别改为Windows下适用的形式。
