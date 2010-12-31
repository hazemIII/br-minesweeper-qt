#include"CompeteGameLogic.h"
#include"AIPlayer.h"

CompeteGameLogic::CompeteGameLogic(){
    this->p1=0;
    this->p2=0;
    this->turn=p1;
}
void CompeteGameLogic::setPlayer(int idx, Player *p){
    if(isAIPlayer(p))dynamic_cast<AIPlayer*>(p)->start();
    if(idx==1)
        p1=p;
    else if(idx==2)
        p2=p;
    else throw std::logic_error("unknown player index: "+str(idx));
}
void CompeteGameLogic::switchTurn(){
    if(turn==p1)
        turn=p2;
    else
        turn=p1;
}
void CompeteGameLogic::dig(int i, int j){
    //  any unsuccessful dig will throw exception, which is handled by player
    if(state!=GameLogic::RUN)
        throw std::logic_error("Game is not running");
    if(!board->validCoordinate(i,j))
        throw std::invalid_argument("Invalid arguments");
    Cell& c=board->getCell(i,j);
    if(c.getState()!=Cell::UNKNOWN)
        throw std::logic_error("Can only dig UNKNOWN cells\n");
    else{
        if(c.getValue()==0)
            this->floodFillDig(i,j);
        else{
            c.setState(Cell::KNOWN);
            if(c.getValue()==Cell::MINE)
                this->turn->increaseScore();
        }
    }
    if(this->checkWin()){
        this->setState(GameLogic::WIN);
        this->revealAll();
        if(isAIPlayer(p1))dynamic_cast<AIPlayer*>(p1)->stop();
        if(isAIPlayer(p2))dynamic_cast<AIPlayer*>(p2)->stop();
        emit this->winSignal();
    }
}
void CompeteGameLogic::mark(int , int ){
    throw std::logic_error("mark operation is not allowed in compete mode");
}
void CompeteGameLogic::unmark(int ,int ){
    throw std::logic_error("unmark operation is not allowed in compete mode");
}
void CompeteGameLogic::explore(int ,int ){
    throw std::logic_error("explore operation is not allowed in compete mode");
}
bool CompeteGameLogic::checkWin(){
    return p1->getScore()+p2->getScore()==this->getNum();
}
bool CompeteGameLogic::checkLose(){
    throw std::logic_error("check lose operation is not allowed in compete mode");
}
Player* CompeteGameLogic::getPlayer(int idx){
    if(idx==1)
        return p1;
    else if(idx==2)
        return p2;
    else
        throw std::logic_error("unknown player index: "+str(idx));
}
Player* CompeteGameLogic::getCurrentPlayer(){
    return turn;
}
CompeteGameLogic::~CompeteGameLogic(){
    delete p1;
    delete p2;
}
void CompeteGameLogic::newGame(int row, int col, int num){
    if(!p1 || !p2)throw std::logic_error("some player is not set yet");
    turn=p1;
    GameLogic::newGame(row,col,num);
}
void CompeteGameLogic::newGame(int row, int col, const Board::LocationList &lst){
    if(!p1 || !p2)throw std::logic_error("some player is not set yet");
    turn=p1;
    GameLogic::newGame(row,col,lst);
}
bool CompeteGameLogic::isAIPlayer(Player *p){
    if(!p)return false;
    return dynamic_cast<AIPlayer*>(p)!=0;
}
