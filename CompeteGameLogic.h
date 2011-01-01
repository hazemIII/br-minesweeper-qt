#ifndef COMPETEGAMELOGIC_H
#define COMPETEGAMELOGIC_H

#include"GameLogic.h"
#include"util.h"
#include"Player.h"


class CompeteGameLogic:public GameLogic{
Q_OBJECT
public:
    CompeteGameLogic();
    ~CompeteGameLogic();
    void switchTurn();
    void setPlayer(int idx,Player* p);
    void clearPlayer(int idx);
    Player* getPlayer(int idx);
    Player* getCurrentPlayer();
    Player* getNextPlayer();
    void newGame(int row, int col, const Board::LocationList &lst);     //override to initialize players
    void newGame(int row, int col, int num);                            //override to initialize players
    bool isAIPlayer(Player *p);
    bool isRemotePlayer(Player *p);
    bool isHumanPlayer(Player *p);
    bool isLocalPlayer(Player *p);
    bool isExactAIPlayer(Player *p);
    bool isExactRemotePlayer(Player *p);
    bool isExactHumanPlayer(Player *p);
    bool isExactLocalPlayer(Player *p);
    bool isQObject(Player* p);

    virtual void dig(int i,int j);
    virtual void mark(int i,int j);
    virtual void unmark(int i,int j);
    virtual void explore(int i,int j);
    virtual bool checkWin();
    virtual bool checkLose();

private:
    Player *p1,*p2,*turn;

private slots:
    void handleGameFromServer(QString s);
};


#endif // COMPETEGAMELOGIC_H
