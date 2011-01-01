#include"CompeteGameLogic.h"
#include"AIPlayer.h"
#include"RemotePlayer.h"
#include"LocalPlayer.h"

CompeteGameLogic::CompeteGameLogic(){
    this->p1=0;
    this->p2=0;
    this->turn=0;
}
void CompeteGameLogic::setPlayer(int idx, Player *p){
    //AI player is not stopped by default. need to start on set
    if(isAIPlayer(p))
        dynamic_cast<AIPlayer*>(p)->start();
    if(idx==1){
        if(p1)clearPlayer(1);
        p1=p;
    }else if(idx==2){
        if(p2)clearPlayer(2);
        p2=p;
    }else throw std::logic_error("unknown player index: "+str(idx));
}
bool CompeteGameLogic::isQObject(Player *p){
    return dynamic_cast<QObject*>(p)!=0;
}
void CompeteGameLogic::clearPlayer(int idx){
    if(idx==1){
        if(!p1)return;
        if(isQObject(p1))
            dynamic_cast<QObject*>(p1)->deleteLater();
        else
            delete p1;
    }else if(idx==2){
        if(!p2)return;
        if(isQObject(p2))
            dynamic_cast<QObject*>(p2)->deleteLater();
        else
            delete p2;
    }else throw std::logic_error("unknown player index: "+str(idx));
}
void CompeteGameLogic::switchTurn(){
    if(turn==p1)
        turn=p2;
    else
        turn=p1;
}
void CompeteGameLogic::dig(int i, int j){
    //  any unsuccessful dig will throw exception, which is handled by player
    if(state!=GameLogic::RUN){
        throw std::logic_error("Game Not Running");
        return;
    }
    if(!board->validCoordinate(i,j)){
        throw std::logic_error("Invalid arguments");
        return;
    }
    Cell& c=board->getCell(i,j);
    if(c.getState()!=Cell::UNKNOWN){
        throw std::logic_error("Can only dig UNKNOWN cells");
        return;
    }else{
        //  successfull dig
        if(c.getValue()==0)
            this->floodFillDig(i,j);
        else{
            c.setState(Cell::KNOWN);
            if(c.getValue()==Cell::MINE)
                this->turn->increaseScore();
        }
    }
    if(this->checkWin()){
        //handle all logical winnning issues here

        this->setState(GameLogic::WIN);
        this->revealAll();
        if(isAIPlayer(p1))dynamic_cast<AIPlayer*>(p1)->stop();
        if(isAIPlayer(p2))dynamic_cast<AIPlayer*>(p2)->stop();
        if(isRemotePlayer(p1))
            dynamic_cast<RemotePlayer*>(p1)->send(QString("DONE"));
        if(isRemotePlayer(p2))
            dynamic_cast<RemotePlayer*>(p2)->send(QString("DONE"));
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
Player* CompeteGameLogic::getNextPlayer(){
    return turn==p1 ? p2 : p1;
}
CompeteGameLogic::~CompeteGameLogic(){
    delete p1;
    delete p2;
}
void CompeteGameLogic::newGame(int row, int col, int num){
    //remote player will never call this function since board layout
    //is determined by server
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
bool CompeteGameLogic::isRemotePlayer(Player *p){
    if(!p)return false;
    return dynamic_cast<RemotePlayer*>(p)!=0;
}
bool CompeteGameLogic::isHumanPlayer(Player *p){
    if(!p)return false;
    return dynamic_cast<HumanPlayer*>(p)!=0;
}
bool CompeteGameLogic::isLocalPlayer(Player *p){
    if(!p)return false;
    return dynamic_cast<LocalPlayer*>(p)!=0;
}
bool CompeteGameLogic::isExactAIPlayer(Player *p){
    return isAIPlayer(p);
}
bool CompeteGameLogic::isExactHumanPlayer(Player *p){
    return isHumanPlayer(p) && !isLocalPlayer(p) && !isRemotePlayer(p);
}
bool CompeteGameLogic::isExactLocalPlayer(Player *p){
    return isLocalPlayer(p);
}
bool CompeteGameLogic::isExactRemotePlayer(Player *p){
    return isRemotePlayer(p);
}
void CompeteGameLogic::handleGameFromServer(QString s){
    RemotePlayer *rp=dynamic_cast<RemotePlayer*>(sender());
    LocalPlayer *lp=dynamic_cast<LocalPlayer*>(rp->getOpponent());
    if(s[6]=='1'){
        setPlayer(1,lp);
        setPlayer(2,rp);
    }else if(s[6]=='2'){
        setPlayer(1,rp);
        setPlayer(2,lp);
    }else throw std::logic_error("unknonwn player index. WTF?");
    QStringList ss=s.trimmed().split(" ");
    int row=ss.at(1).toInt();
    int col=ss.at(2).toInt();
    Board::LocationList lst;
    for(int i=4;i<ss.count();i++){
        QStringList loc=ss.at(i).split(",");
        lst.push_back(std::make_pair(loc.at(0).toInt(),loc.at(1).toInt()));
    }
    newGame(row,col,lst);
    printErr("game from server constructed");
}
