#include"GameLogic.h"
#include"util.h"
GameLogic::GameLogic():board(0),state(STOP){}

Cell& GameLogic::getCell(int i, int j){
    if(!board) throw std::runtime_error("Board has not been constructed yet");
    return board->getCell(i,j);
}
int GameLogic::getState(){
    return state;
}

void GameLogic::newGame(int row, int col, const Board::LocationList &lst){
    if(row < Board::MIN_ROW_NUM || col < Board::MIN_COLUMN_NUM
       || row > Board::MAX_ROW_NUM|| col > Board::MAX_COLUMN_NUM)
        throw std::invalid_argument("invalid size of board");
    if(num <0 || num >row*col)
        throw std::invalid_argument("invalid number of mines");
    if(board) delete board;
    this->num=lst.size();
    board=new Board(row,col,lst);
    setState(RUN);
    //emit this->boardChangedSignal();
}
void GameLogic::newGame(int row, int col, int num){
    if(row < Board::MIN_ROW_NUM || col < Board::MIN_COLUMN_NUM
       || row > Board::MAX_ROW_NUM|| col > Board::MAX_COLUMN_NUM)
        throw std::invalid_argument("invalid size of board");
    if(num <0 || num >row*col)
        throw std::invalid_argument("invalid number of mines");
    if(board) delete board;
    this->num=num;
    board=new Board(row,col,num);
    setState(RUN);
    //emit this->boardChangedSignal();
}
int GameLogic::getNum(){
    return num;
}
bool GameLogic::validState(int v){
    return v==GameLogic::RUN || v==GameLogic::STOP ||
            v==GameLogic::WIN || v==GameLogic::LOSE;
}
void GameLogic::setState(int new_state){
    if(this->validState(new_state))
        state=new_state;
    else
        throw std::invalid_argument("unknown state for GameLogic: "+str(new_state));
}
std::string GameLogic::cheat(){
    if(this->getState()!=RUN)
        throw std::logic_error("Game is not running");
    else{
        std::stringstream res;
        for(int i=0;i<board->getRow();i++){
            for(int j=0;j<board->getCol();j++)
                res<<std::setw(3)<<board->getCell(i,j).getValue();
            res<<std::endl;
        }
        return res.str();
    }
}
std::string GameLogic::toString(){
    if(this->getState()==RUN)
        return board->toString();
    else
        return "";
}
void GameLogic::floodFillDig(int i, int j){
    if(state!=GameLogic::RUN)
        throw std::logic_error("Game is not running");
    else if(!board->validCoordinate(i,j))
        throw std::invalid_argument("Invalid arguments");

    Board::LocationList lst=board->getNeighbours(i,j);
    board->getCell(i,j).setState(Cell::KNOWN);
    for(size_t i=0;i<lst.size();i++){
        Board::Location& p=lst[i];
        Cell& c=board->getCell(p.first,p.second);
        if(c.getState()!=Cell::UNKNOWN)continue;
        if(c.getValue()==0)
            floodFillDig(p.first,p.second);
        else
            dig(p.first,p.second);
    }
}
void GameLogic::revealAll(){
    for(int i=0;i<board->getRow();i++)
        for(int j=0;j<board->getCol();j++)
            this->getCell(i,j).setState(Cell::KNOWN);
    //emit this->boardChangedSignal();
}
int GameLogic::getRow(){
    return board->getRow();
}
int GameLogic::getCol(){
    return board->getCol();
}
Board::LocationList GameLogic::getNeighbours(int i, int j){
    return this->board->getNeighbours(i,j);
}
int GameLogic::getMarkedNum(){
    //  count one by one...
    //  maybe not efficient,
    //  but I don't want to bring trouble to later maintainence
    //  because keeping track of a counting variable in multiple functions is difficult
    if(getState()!=GameLogic::RUN)
        return -1;
    int res=0;
    for(int i=0;i<this->getRow();i++)
        for(int j=0;j<this->getCol();j++)
            if(getCell(i,j).getState()==Cell::MARKED)
                res++;
    return res;
}
