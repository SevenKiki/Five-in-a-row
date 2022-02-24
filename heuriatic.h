#ifndef HEURIATIC_H
#define HEURIATIC_H
#include "board.h"


class heuriatic:public board
{
public:
    heuriatic();
    void mouseReleaseEvent(QMouseEvent *event);

    void AISetChessGreedy();



};

#endif // HEURIATIC_H
