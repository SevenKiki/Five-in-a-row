#ifndef AIPLAY_H
#define AIPLAY_H
#include "board.h"


class AIplay : public board
{
public:
    AIplay();

    void mouseReleaseEvent(QMouseEvent *event);

    void AISetChess();

    QPoint Minimax_Decision(int player);//Qpoint 的x是棋子的行，y是棋子的列
    int Minimax_value(int row,int col ,int depthh, int player,int a,int b);//


};

#endif // AIPLAY_H
