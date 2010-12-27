#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include"Board.h"
#include"util.h"
#include<QObject>

class GameLogic : public QObject{
    Q_OBJECT
protected:
    Board *board;
    int state;
    int num;        //mine number in the board

    void floodFillDig(int i,int j);
    void revealAll();
    void setState(int new_state);   //  only allow in class call
    bool validState(int state);
public:
    enum{
        RUN=0,
        STOP=1,
        WIN=2,
        LOSE=3,
    };

    GameLogic();
    void newGame(int row,int col,int num);
    void newGame(int row,int col,const Board::LocationList &lst);
    int getRow() ;
    int getCol() ;
    int getNum() ;
    int getMarkedNum() ;
    int getState();
    Cell& getCell(int i,int j);
    std::string cheat();
    std::string toString();
    Board::LocationList getNeighbours(int i,int j);
    /******* rule dependent part ************/
    virtual void dig(int i,int j)=0;
    virtual void mark(int i,int j)=0;
    virtual void unmark(int i,int j)=0;
    virtual void explore(int i,int j)=0;
    virtual bool checkWin()=0;
    virtual bool checkLose()=0;
    /******* rule dependent part ************/
signals:
    void winSignal();
    void loseSignal();
    //void boardChangedSignal();
};

#endif // GAMELOGIC_H
