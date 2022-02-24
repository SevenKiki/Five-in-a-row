#ifndef SUNAFA3_H
#define SUNAFA3_H
#include "board.h"


class sunafa3:public board
{
public:
    sunafa3();
    void mouseReleaseEvent(QMouseEvent *event);

    void setChess();
    void AI(int *p, int *q);
    int positionValue(int row, int col) ;
    int chessType(int n, int p, int q) ;
    void goStep(int n, int *i, int *j);

};

#endif // SUNAFA3_H
