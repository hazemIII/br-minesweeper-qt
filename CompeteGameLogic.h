#ifndef COMPETEGAMELOGIC_H
#define COMPETEGAMELOGIC_H

#include"GameLogic.h"
#include"util.h"
#include"Player.h"


class CompeteGameLogic:public GameLogic{

public:
    CompeteGameLogic();
    ~CompeteGameLogic();
    void switchTurn();
    void setPlayer(int idx,Player* p);
    Player* getPlayer(int idx);
    Player* getCurrentPlayer();
    void newGame(int row, int col, const Board::LocationList &lst);     //override to initialize players
    void newGame(int row, int col, int num);                            //override to initialize players
    bool isAIPlayer(Player *p);

    virtual void dig(int i,int j);
    virtual void mark(int i,int j);
    virtual void unmark(int i,int j);
    virtual void explore(int i,int j);
    virtual bool checkWin();
    virtual bool checkLose();

private:
    Player *p1,*p2,*turn;
};


#endif // COMPETEGAMELOGIC_H
