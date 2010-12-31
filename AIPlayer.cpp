#include"AIPlayer.h"
#include"CompeteGameLogic.h"
#include"MainWindow.h"

AIThread::AIThread(AIPlayer* p){
    this->stopped=false;
    this->p=p;
}
AIThread::~AIThread(){
    stop();
}
void AIThread::stop(){
    this->stopped=true;
}
void AIThread::run(){
    while(!stopped)
        p->makeMove();
}

AIPlayer::AIPlayer(QString name, CompeteGameLogic * gl,MainWindow* win)
    :Player(name,gl){
    thread=new AIThread(this);
    thread->start();
    this->win=win;
}
AIPlayer::~AIPlayer(){
    delete thread;
}
void AIPlayer::makeMove(int , int ){
    if(this->gl->getCurrentPlayer()!=this){
        return;
    }
    try{
        for(int i=0;i<gl->getRow();i++)
            for(int j=0;j<gl->getCol();j++)
                if(gl->getCell(i,j).getState()==Cell::UNKNOWN){
                    this->gl->dig(i,j);
                    if(gl->getCell(i,j).getValue()!=Cell::MINE)
                        this->gl->switchTurn();
                    win->updateGUI();
                    return;
                }
    }catch(std::exception e){
        printErr("exception when human player is trying to make a move..");
    }
}
