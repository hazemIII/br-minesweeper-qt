#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include"Player.h"
#include"MainWindow.h"

class HumanPlayer : public Player{
public:
    HumanPlayer(QString name, CompeteGameLogic * gl);
    virtual void makeMove(int i=-1,int j=-1);
};

#endif // HUMANPLAYER_H
