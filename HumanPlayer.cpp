#include"HumanPlayer.h"
#include"CompeteGameLogic.h"
void HumanPlayer::makeMove(int i, int j){
    if(this->gl->getCurrentPlayer()!=this){
        printErr("not your turn yet\n");
        return;
    }
    try{
        this->gl->dig(i,j);
        if(gl->getCell(i,j).getValue()!=Cell::MINE)
            this->gl->switchTurn();
    }catch(std::exception e){
        printErr("exception when human player is trying to make a move..");
    }
}
HumanPlayer::HumanPlayer(QString name, CompeteGameLogic *gl):Player(name,gl){
    //trivial constructor
}
