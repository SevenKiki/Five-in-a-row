#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>

extern int CHESS_R;
extern int GRID_SIZE;
extern int BOARD_SIZE;
extern int DEPTH;
# define SPA 0//在C或C++语言源程序中允许用一个标识符来表示一个字符串，称为“宏”。 “define”为宏定义命令。
# define MAN -1
# define COM 1

class board:public QMainWindow
{
    Q_OBJECT

public:
     board();
    ~board();

    virtual void mouseReleaseEvent(QMouseEvent *);//鼠标释放事件

    void placeChess(int row,int col);//在某行某列放置一个棋子
    void initialBoard();//清空棋盘

    bool win(int _side);//赢了吗
    void paintEvent(QPaintEvent *);//设置背景颜色，画棋子，画棋盘
    void drawChess(QPainter *painter);//画棋子
    void drawBoard(QPainter *painter);//画棋盘

    QPoint center(int row,int col);//棋子中央点
    bool within(QPoint point);//判断鼠标点击的点是否在哪一个格子的范围内
    int getRow(QPoint point);//根据鼠标点击的点确定行
    int getCol(QPoint point);//根据鼠标点击的点确定列

    int chess[15][15];//用来保存棋子的数据，0为空，1为黑子，-1为白子，黑子是人，白子是电脑
    int chessR;//棋子半径
    QPoint point;//坐标基点
    int firstSide;//先出棋子的一方
    int crntSide;//现在出棋的一方

    //void AISet();
    int getValue(int row,int col,int player);
    int evaluate(int row,int col,int ai,int player,int type);
     int getLine(int row,int col,int i,int j);
     int getStateValue(int row,int col,int player);

    int minRow;//棋盘现在状态最上边棋子的行数
    int maxRow;//棋盘现在状态最下边棋子的行数

    int minCol;//棋盘现在状态最左边棋子的行数
    int maxCol;//棋盘现在状态最右边棋子的行数

};

#endif // BOARD_H
