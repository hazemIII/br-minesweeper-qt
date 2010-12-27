#include"NormalGameLogic.h"

void NormalGameLogic::dig(int i, int j){
    //  need to check win & lose after calling this function
    if(state!=GameLogic::RUN)
        throw std::logic_error("Game is not running");
    else if(!board->validCoordinate(i,j))
        throw std::invalid_argument("Invalid arguments");

    Cell& c=board->getCell(i,j);
    if(c.getState()!=Cell::UNKNOWN)
        printErr("Can only dig UNKNOWN cells\n");
    else{
        if(c.getValue()==0)
            this->floodFillDig(i,j);
        else
            c.setState(Cell::KNOWN);
    }
    //emit this->boardChangedSignal();
    if(this->checkWin()){
        this->setState(GameLogic::WIN);
        emit this->winSignal();
    }else if(this->checkLose()){
        this->revealAll();
        this->setState(GameLogic::LOSE);
        emit this->loseSignal();
    }
}
void NormalGameLogic::mark(int i, int j){
    //  need to check win after calling this function
    if(state!=GameLogic::RUN)
        throw std::logic_error("Game is not running");
    else if(!board->validCoordinate(i,j))
        throw std::invalid_argument("Invalid arguments");

    Cell& c=board->getCell(i,j);
    if(c.getState()!=Cell::UNKNOWN)
        printErr("Can only mark UNKNOWN cells\n");
    else
        c.setState(Cell::MARKED);
    //emit this->boardChangedSignal();
    if(this->checkWin()){
        this->setState(GameLogic::WIN);
        emit this->winSignal();
    }
}
void NormalGameLogic::unmark(int i, int j){
    if(state!=GameLogic::RUN)
        throw std::logic_error("Game is not running");
    else if(!board->validCoordinate(i,j))
        throw std::invalid_argument("Invalid arguments");

    Cell& c=board->getCell(i,j);
    if(c.getState()!=Cell::MARKED)
        printErr("Can only unmark MARKED cells\n");
    else
        c.setState(Cell::UNKNOWN);
    //emit this->boardChangedSignal();
}
void NormalGameLogic::explore(int i, int j){
    if(state!=GameLogic::RUN)
        throw std::logic_error("Game is not running");
    else if(!board->validCoordinate(i,j))
        throw std::invalid_argument("Invalid arguments");

    Cell& c=board->getCell(i,j);
    if(c.getState()!=Cell::KNOWN)
        printErr("Can only explore KNOWN cells\n");
    else{
        if(this->markedNeighboursNumberOK(i,j))
            this->digAllUnknownNeighbours(i,j);
        else
            printErr("Marked neighbour number is not correct\n");
    }
    //emit this->boardChangedSignal();
}
bool NormalGameLogic::markedNeighboursNumberOK(int i, int j){
    Board::LocationList lst=board->getNeighbours(i,j);
    int ct=0;
    for(size_t k=0;k<lst.size();k++)
        if(this->getCell(lst[k].first,lst[k].second).getState()==Cell::MARKED)
            ct++;
    return this->getCell(i,j).getValue()==ct;
}
void NormalGameLogic::digAllUnknownNeighbours(int i, int j){
    Board::LocationList lst=board->getNeighbours(i,j);
    for(size_t k=0;k<lst.size();k++)
        if(this->getCell(lst[k].first,lst[k].second).getState()==Cell::UNKNOWN)
            this->dig(lst[k].first,lst[k].second);
}
bool NormalGameLogic::checkWin(){
    //  all mine are MARKED, the rest are KNOWN
    if(!board)return false;
    for(int i=0;i<board->getRow();i++){
        for(int j=0;j<board->getCol();j++){
            Cell &c=board->getCell(i,j);
            if(c.getValue()==Cell::MINE){
                if(c.getState()!=Cell::MARKED)
                    return false;
            }else{
                if(c.getState()!=Cell::KNOWN)
                    return false;
            }
        }
    }
    return true;
}
bool NormalGameLogic::checkLose(){
    //  some MINE is KNOWN
    if(!board)return false;
    for(int i=0;i<board->getRow();i++){
        for(int j=0;j<board->getCol();j++){
            Cell &c=board->getCell(i,j);
            if(c.getValue()==Cell::MINE
               && c.getState()==Cell::KNOWN)
                return true;
        }
    }
    return false;
}
