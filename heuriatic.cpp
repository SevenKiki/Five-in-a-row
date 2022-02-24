#include "heuriatic.h"
#include <QMouseEvent>
#include<windows.h>

heuriatic::heuriatic()
{

}

void heuriatic::mouseReleaseEvent(QMouseEvent *event){
    QPoint mousePoint = event->pos();
    bool ifwithin=within(mousePoint);//判断是否在有效范围之内
    int row,col;
    if(ifwithin){
        row = getRow(mousePoint);
        col = getCol(mousePoint);

        //如果棋盘格子上没有棋子
        if(chess[row][col] == 0){
            placeChess(row,col);
            //此时是人下棋，下一步是电脑下棋
            crntSide = -1;
            update();

            AISetChessGreedy();

            crntSide = 1;
            update();

        }
    }
    update();
}

void heuriatic::AISetChessGreedy(){
    int maxValue =0 ;
    int bestCol=0,bestRow=0;//价值最高的行和列
    //在已下棋盘周围一圈的棋子空格中找最优解（限制范围）
  if(minRow >=0 && minCol >=0 && maxRow <BOARD_SIZE && maxCol <BOARD_SIZE){
    for(int i=minRow-1; i<=maxRow+1 ; i++){
        for(int j= minCol-1; j<=maxRow+1; j++){
            if(chess[i][j] !=0) continue;//若棋格非空，继续搜索点
            int tmpValue = getValue(i,j,-1);
            if(tmpValue > maxValue){
                bestRow = i;
                bestCol = j;
                maxValue = tmpValue;
            }
        }
    }
  }


   else{
      int tmpValue;
        for(int i=0;i<=BOARD_SIZE;i++){
            for(int j=0;j<=BOARD_SIZE;j++){
                if(chess[i][j] !=0) continue;
                 else tmpValue = getValue(i,j,-1);//最后的价值要加上初始化的价值
                if(tmpValue >maxValue){
                    bestRow = i;
                    bestCol = j;
                    maxValue = tmpValue;
                }
            }
        }
    }
    //在价值最高的行和列放置棋子
    placeChess(bestRow , bestCol);
}


