#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <istream>
#include <QMessageBox>
#include <QMenuBar>
#include<QMenu>
#include<QAction>
using namespace std;

int  CHESS_R = 18;
int GRID_SIZE = 40;
int BOARD_SIZE =14;
int DEPTH = 2;

board::board()

{


    initialBoard();//每次构造都需要初始化棋盘
    chessR = CHESS_R;//棋子半径
    setMinimumSize(600,600);//窗口大小

    firstSide = 1;
    minRow=100;
    maxRow=-100;
    minCol=100;
    maxCol=-100;
    crntSide = firstSide;

    update();
}

board::~board()
{

}


void board::placeChess(int row, int col){
    if(chess[row][col]!=0)//这个格子有棋子
        return ;
    else if(row <0 || row >= BOARD_SIZE+1 || col < 0 || col >= BOARD_SIZE+1)//超出棋盘范围
        return ;
    chess[row][col] = crntSide;//放置
    //重置最大最小行数，最大最小列数
    if(row < minRow) minRow = row;
    if(row > maxRow) maxRow = row;
    if(col < minCol) minCol = col;
    if(col > maxCol) maxCol = col;
}

void board::initialBoard(){
    for(int i=0;i<BOARD_SIZE+1;i++)
        for(int j=0;j<BOARD_SIZE+1;j++)
            chess[i][j] = 0;
}

bool board::win(int _side){
    for(int i=0;i<BOARD_SIZE+1;i++)
        for(int j=0;j<BOARD_SIZE+1;j++)
        {
            if(chess[i][j]!=_side)continue;
            int dx=1,dy=0;//从这颗棋子向右五颗都是相同的颜色（连成横线）
            for(int k=0;k<=5;++k)
                {
                if(k==5)return true;
                int tx=i+dx*k,ty=j+dy*k;
                if(tx<0||tx>=BOARD_SIZE+1||ty<0||ty>=BOARD_SIZE+1||chess[tx][ty]!=_side)break;
                }
            dx=1,dy=1;//从这个棋子向右下延续五颗（连成斜线）
            for(int k=0;k<=5;++k)
                {
                if(k==5)return true;
                int tx=i+dx*k,ty=j+dy*k;
                if(tx<0||tx>=BOARD_SIZE+1||ty<0||ty>=BOARD_SIZE+1||chess[tx][ty]!=_side)break;
                }
            dx=0,dy=1;//从这颗棋子向下连续五颗（连成直线）
            for(int k=0;k<=5;++k)
                {
                if(k==5)return true;
                int tx=i+dx*k,ty=j+dy*k;
                if(tx<0||tx>=BOARD_SIZE+1||ty<0||ty>=BOARD_SIZE+1||chess[tx][ty]!=_side)break;
                }
            dx=-1,dy=1;//从这颗棋子向左下连续五颗（连成斜线)
            for(int k=0;k<=5;++k)
                {
                if(k==5)return true;
                int tx=i+dx*k,ty=j+dy*k;
                if(tx<0||tx>=BOARD_SIZE+1 ||ty<0||ty>=BOARD_SIZE+1||chess[tx][ty]!=_side)break;
                }
        }
    return false;

}

QPoint board::center(int row, int col){
    QPoint point;
    point.setX(row*GRID_SIZE + GRID_SIZE/2);
    point.setY(col*GRID_SIZE + GRID_SIZE/2);
    return point;
}

bool board::within(QPoint point){
    //点击的点在棋盘的范围上
    if(point.x()>=0 && point.x()<=BOARD_SIZE*GRID_SIZE + GRID_SIZE
            && point.y()>=0 && point.y()<=BOARD_SIZE * GRID_SIZE + GRID_SIZE)
        return true;

    return false;
}

int board::getRow(QPoint point){

       return point.x()/GRID_SIZE;
}

int board::getCol(QPoint point){

        return point.y()/GRID_SIZE;
}

void board::drawChess(QPainter *painter){
    QPixmap white,black;

    white.load(":/new/prefix1/picture/chess white.png");
    black.load(":/new/prefix1/picture/chess black.png");


    for(int i=0;i<BOARD_SIZE+1;i++){
        for(int j=0;j<BOARD_SIZE+1;j++){
            if(chess[i][j] == 1){

                painter->drawPixmap(center(i,j).x()-CHESS_R , center(i,j).y()-CHESS_R , CHESS_R*2 , CHESS_R*2,white);



            }
            else if(chess[i][j] == -1){
                painter->drawPixmap(center(i,j).x()-CHESS_R , center(i,j).y()-CHESS_R , CHESS_R*2 , CHESS_R*2 , black );
            }
        }
    }
}

void board::drawBoard(QPainter *painter){
    painter->setPen(QPen(Qt::black,3,Qt::SolidLine));//设置线条的宽度
    for(int i=0;i<BOARD_SIZE+1;i++){
        //画十六条竖线
        painter->drawLine(20+i*GRID_SIZE, 20, 20+i*GRID_SIZE , 20+GRID_SIZE*BOARD_SIZE);
        //画十六条横线
        painter->drawLine(20 , 20+i*GRID_SIZE , 20+GRID_SIZE*BOARD_SIZE, 20+i*GRID_SIZE);
    painter->setBrush(Qt::red);
    painter->drawEllipse(20+BOARD_SIZE/2*GRID_SIZE-5,20+BOARD_SIZE/2*GRID_SIZE-5,10,10);

}
}

void board::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if(win(1) || win(-1))//有一方赢了就弹出界面
    {

        QString text = win(1) ? "YOU WIN!!!" : "YOU LOST!!!";
        painter.setPen(QPen(Qt::red , 3));
        painter.drawText(rect(),Qt::AlignCenter, text);
        initialBoard();
        return;
    }

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background , QColor(255,222,173));
    this->setPalette(palette);
    drawBoard(&painter);

    drawChess(&painter);
}

void board::mouseReleaseEvent(QMouseEvent *event){
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
           //AISet();
            else {
                crntSide = 1;
                update();
            }

        }
    }

}

int board::getValue(int row, int col,int player){
    //离棋盘中心越近，分值越高
    int initialValue[BOARD_SIZE+1][BOARD_SIZE+1]=
    {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
     {0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
     {0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
     {0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
     {0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
     {0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
     {0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
     {0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
     {0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
     {0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
     {0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
     {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    int value= evaluate(row,col,crntSide,-1,0)+ evaluate(row,col,crntSide,1,0) + initialValue[row][col] *10;
    /*if(player == -1)//机器下棋
        return -value;
    else
        return value;*/
    return value;

}


int board::evaluate(int row , int col, int me,int player,int type) {
    // me:我的代号  plyer:当前计算的player的代号  type:测评整个棋局的价值（1），测评单个落子的价值（0）
        int value = 0;
        int numoftwo=0;
        for (int i = 1; i <= 8; i++) { // 8个方向
            // 活四 01111* *代表当前空位置  0代表其他空位置
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, -3) == player && getLine(row,col, i, -4) == player
                    && getLine(row,col, i, -5) == 0) {
                if(type == 0){
                    value += 300000;
                    if(me!=player){value-=500;}
                    continue;

                }
                if(type == 1){
                    if( player ==-1) value -=300000;//对电脑和人都是最有利的
                    if( player ==1) value +=300000;
                    continue;
                }
            }

            // 死四A 21111*
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, -3) == player && getLine(row,col, i, -4) == player
                    && (getLine(row,col, i, -5) ==  - player||getLine(row,col, i, -5) == -1)) {
                if(type ==0){
                    value += 250000;
                    if(me!=player){value-=500;}
                    continue;
                }
                if(type ==1){
                    if( player == -1) value -=250000;
                    if( player == 1) value +=250000;
                    continue;
                }
            }
            // 死四B 111*1
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, -3) == player && getLine(row,col, i, -1) == player) {
                if(type == 0){
                    value += 240000;
                    if(me!=player){value-=500;}
                    continue;
                }
                if(type == 1){
                    if( player == -1) value -=240000;
                    if( player == 1) value +=240000;
                    continue;
                }
            }
            // 死四C 11*11
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, 1) == player && getLine(row,col, i, 2) == player) {
                if(type == 0){
                    value += 230000;
                    if(me!=player){value-=500;}
                    continue;
                }
                if(type == 1){
                    if( player == -1) value -=230000;
                    if( player == 1) value +=230000;
                    continue;
                }

            }
            // 活三 近3位置 111*0
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, -3) == player) {
                if (getLine(row,col, i, 1) == 0) {
                    if(type == 1){
                        if( player == -1) value -=750;
                        if( player == 1) value +=750;
                    }
                    if(type == 0)
                    value += 750;
                    if(type ==1){
                        if( player == -1) value -=750;
                        if( player == 1) value +=750;
                    }
                    if (getLine(row,col, i, -4) == 0) {
                        if(type ==0){
                            value += 3150;
                            if(me!=player){value-=300;}
                        }
                        if(type ==1){
                            if( player == -1) value -=3150;
                            if( player == 1) value +=3150;
                        }
                    }
                }
                if ((getLine(row,col, i, 1) == - player||getLine(row,col, i, 1) == -1)
                        && getLine(row,col, i, -4) == 0) {
                    if(type ==0)
                    value += 500;
                    if(type ==1){
                        if( player == -1) value -=500;
                        if( player == 1) value +=500;
                    }
                }
                continue;
            }
            // 活三 远3位置 1110*
            if (getLine(row,col, i, -1) == 0 && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, -3) == player && getLine(row,col, i, -4) == player) {
                if(type == 0){
                    value += 350;
                    continue;
                }
                if(type ==1){
                    if( player == -1) value -=350;
                    if( player == 1) value +=350;
                    continue;
                }

            }
            // 死三 11*1
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, 1) == player) {
                if(type == 0)
                value += 600;
                if(type == 1){
                    if( player == -1) value -=600;
                    if( player == 1) value +=600;
                }
                if (getLine(row,col, i, -3) == 0 && getLine(row,col, i, 2) == 0) {
                    if(type == 0){
                        value += 3150;
                        continue;
                    }
                    if(type == 1){
                        if( player == -1) value -=3150;
                        if( player == 1) value +=3150;
                        continue;
                    }

                }
                if ((getLine(row,col, i, -3) ==  - player||getLine(row,col, i, -3) == -1)
                        && (getLine(row,col, i, 2) ==  - player||getLine(row,col, i, 2) == -1)) {
                    continue;
                } else {
                    if(type == 0){
                        value += 700;
                        continue;
                    }
                    if(type ==1){
                        if( player == -1) value -=700;
                        if( player == 1) value +=700;
                        continue;

                    }
                }
            }
            //活二的个数
            if (getLine(row,col, i, -1) == player && getLine(row,col, i, -2) == player
                    && getLine(row,col, i, -3) != -player&&getLine(row,col,i,1)!=-player) {
                numoftwo++;
            }
            //其余散棋
            int numOfplayer = 0; // 因为方向会算两次？
            for (int k = -4; k <= 0; k++) { // ++++* +++*+ ++*++ +*+++ *++++
                int temp = 0;
                for (int l = 0; l <= 4; l++) {
                    if (getLine(row,col, i, k + l) == player) {
                        temp++;
                    } else
                        if (getLine(row,col, i, k + l) ==  - player
                                || getLine(row,col, i, k + l) == -1) {
                        temp = 0;
                        break;
                    }
                }
                numOfplayer += temp;
            }
            if(type == 0)
            value += numOfplayer * 15;
            if(type == 1){
                if( player == -1) value -=numOfplayer * 15;
                if( player == 1) value +=numOfplayer * 15;
            }
            if (numOfplayer != 0) {
            }
        }
        if(numoftwo>=2){
           if(type == 0)
            value+=3000;

           if(type ==1){
               if( player == -1) value -=3000;
               if( player == 1) value +=3000;
           }

            if(me!=player){
                value-=100;
                }
            }
        return value;
    }





int board::getLine(int row,int col, int i, int j) { // i:方向 j:相对p的顺序值（以p为0） p:当前点
        int x =row, y =col;
        //1：右   2：右下   3：下   4：左下   5：左   6：左上   7：上   8：右上
        switch (i) {
            case 1 :
                x = x + j;
                break;
            case 2 :
                x = x + j;
                y = y + j;
                break;
            case 3 :
                y = y + j;
                break;
            case 4 :
                x = x - j;
                y = y + j;
                break;
            case 5 :
                x = x - j;
                break;
            case 6 :
                x = x - j;
                y = y - j;
                break;
            case 7 :
                y = y - j;
                break;
            case 8 :
                x = x + j;
                y = y - j;
        }
        if (x < 0 || y < 0 || x > BOARD_SIZE+1 || y > BOARD_SIZE+1) { // 越界处理
            return -1;
        }
        return chess[x][y];
    }



