#ifndef PLAYER_H
#define PLAYER_H

#include"GameLogic.h"

class CompeteGameLogic;         //forward declaration

//  abstract player class
class Player {
public:
    Player(QString name, CompeteGameLogic * gl);
    virtual void makeMove(int i=-1,int j=-1)=0;   //for human player, dig (i,j); for AI player, i and j are ignored
    int getScore();
    void clearScore();
    QString getName();
    void increaseScore();
protected:
    QString name;
    int score;
    CompeteGameLogic* gl;   //player is only needed in compete mode
};

#endif // PLAYER_H



