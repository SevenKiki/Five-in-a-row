#include "aiplay.h"
#include <QMouseEvent>
#include<windows.h>

AIplay::AIplay()
{

}

void AIplay::mouseReleaseEvent(QMouseEvent *event){
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
            if(crntSide == 1){
                crntSide = -1;
                update();
            }
            AISetChess();
                crntSide = 1;
                update();

        }
    }
    update();
}

QPoint AIplay::Minimax_Decision(int player){
    int min = 10000000;
    int a = -10000000;
    int b= 10000000;
    QPoint point;
     point.setX(-1);
     point.setY(-1);
    for(int i=minRow-1;i<maxRow+1 ; i++){
        for(int j=minCol-1;j< maxCol+1 ; j++){
            if(chess[i][j] == 0){
                chess[i][j] =player;

                int tmp = Minimax_value(i,j,DEPTH, player,a,b);

                chess[i][j] = 0;
                if(min > tmp){
                    min = tmp;
                    point.setX(i);
                    point.setY(j);

                }
            }
        }
    }

    return point;
}

/*int AIplay::Minimax_value(int row,int col,int depthh, int player){
    int min = 10000000;//初始化最小值
    int max = -10000000;//初始化最大值

    if(win(-1)) return -10000000;//棋局结束
    if(win(1))  return 100000000;
    int nextplayer = -player;
    for(int i=minRow-2;i<=maxRow+2;i++){
        for(int j=minCol-2;j<=maxCol+2;j++)
        {
            if(chess[i][j] == 0){
                chess[i][j] = nextplayer;

                int tmp;
                if(depthh-1 !=0)
                 tmp = Minimax_value(i,j,depthh-1,nextplayer);
                if(depthh-1 == 0){

                    tmp = 0.1*evaluate(i+1,j+1,-1,nextplayer,0)
                            +0.1 *evaluate(i+1,j-1,-1,nextplayer,0)
                            +0.1 *evaluate(i+1,j,-1,nextplayer,0)
                            +0.1 *evaluate(i-1,j+1,-1,nextplayer,0)
                            +0.1 *evaluate(i-1,j-1,-1,nextplayer,0)
                            +0.1 *evaluate(i-1,j,-1,nextplayer,0)
                            +0.1 *evaluate(i,j-1,-1,nextplayer,0)
                            +0.1 *evaluate(i,j+1,-1,nextplayer,0)
                            ;

                }

                if(nextplayer == -1){
                    if(min >tmp)
                        min = tmp;
                    }
                if(nextplayer == 1){
                    if(max <tmp  )
                          max = tmp;
                }

                chess[i][j] = 0;

                }
            }
        }
    if(nextplayer ==1) return max;
     else  return min;
    }

*/
void AIplay::AISetChess(){
    QPoint point =Minimax_Decision(-1);
    int chessrow=point.x();
    int chesscol=point.y();
    placeChess(chessrow,chesscol);
}

AIplay::Minimax_value(int i, int j, int depthh, int player, int a, int b){
    int value;
    if(player == -1) value = -1000000;
    if(player == 1)  value =1000000;
    int nextplayer = -player;
    if(depthh == 0)
        return getValue(i,j,nextplayer);

    for(int m=0;m<BOARD_SIZE;m++){
        for(int n=0;n<BOARD_SIZE;n++){
            if(player == -1){
                int tmpvalue = Minimax_value(m,n,depthh-1,-player,a,b);
                if(tmpvalue > value)
                    value = tmpvalue;
                if(value >b)
                    break;
                if(value >a)
                    a=value;

            }

            else{
                int tmpvalue = Minimax_value(m,n,depthh-1,-player,a,b);
                if(tmpvalue <value)
                    value = tmpvalue;
                if(value <a) break;
                if(value <b) b=value;

            }
        }
    }
    return value;
}
//AIplayer是自动移动的，也就是电脑
/*int minimax(state,deep,player,a,b){
   int value;
   if(player==AIplayer){
       value = -inf;
   }else{
       value = inf;
   }
   if(deep==0)
       return evaluate(state);
   for nextstate in childStates{
       if(player==AIplayer){
           value = max(value,minimax(state,deep-1,-player,a,b));
           if(value>b)
               break;
           if(value>a)
               a = value;
       }
       else{
           value = min(value,minimax(state,deep-1,-player,a,b));
           if(value<a)
               break;
           if(value<b)
               b = value;
       }
   }
   return value;
}*/
