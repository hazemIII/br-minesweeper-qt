#include"Board.h"
#include"util.h"

Board::Board(int row, int col, int num){
    this->row=row;
    this->col=col;
    board=new Cell*[row];
    for(int i=0;i<row;i++)
        board[i]=new Cell[col];
    this->randomlyFillMines(num);
    this->setupValues();
}
Board::Board(int row, int col, const LocationList &lst){
    this->row=row;
    this->col=col;
    board=new Cell*[row];
    for(int i=0;i<row;i++)
        board[i]=new Cell[col];
    this->fillMineByLocationList(lst);
    this->setupValues();
}
/**
    set up values for each cell to be consistent with mine allignment
*/
void Board::setupValues(){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(this->getCell(i,j).getValue()!=Cell::MINE)continue;
            LocationList lst=this->getNeighbours(i,j);
            for(size_t k=0;k<lst.size();k++){
                Location &p=lst[k];
                Cell& c=board[p.first][p.second];
                if(c.getValue()!=Cell::MINE)
                    c.setValue(c.getValue()+1);
            }
        }
    }
}
/**
  randomly fill in <num> mines into board
*/
void Board::randomlyFillMines(int num){
    srand(time(NULL));
    int i,j;
    while(num--){
        do{
            i=randInt(0,row-1);
            j=randInt(0,col-1);
        }while(board[i][j].getValue()==Cell::MINE);
        board[i][j].setValue(Cell::MINE);
    }
}
/**
    fill in mines according to location list
*/
void Board::fillMineByLocationList(const LocationList &lst){
    for(size_t i=0;i<lst.size();i++){
        const Location &p=lst[i];
        board[p.first][p.second].setValue(Cell::MINE);
    }
}
Board::~Board(){
    for(int i=0;i<row;i++)
        delete[] board[i];
    delete[] board;
}
Cell& Board::getCell(int i, int j){
    if(this->validCoordinate(i,j))
        return board[i][j];
    else{
        printErr("try to get cell from invalid coordinate");
        exit(-1);
    }
}
int Board::getCol(){
    return col;
}
int Board::getRow(){
    return row;
}
bool Board::validCoordinate(int i, int j){
    return i>=0 && i<row && j>=0 && j<col;
}
std::string Board::toString(){
    std::stringstream res;
    res<<"\n";
    res<<"  ";
    for(int i=0;i<col;i++)
        res<<std::setw(3)<<std::right<<i;
    res<<std::setw(0)<<"\n";
    for(int i=0;i<row;i++){
        res<<std::setw(3)<<std::left<<i<<std::setw(0);
        for(int j=0;j<col;j++)
            res<<board[i][j].toString();
        res<<"\n";
    }
    return res.str();
}
Board::LocationList Board::getNeighbours(int i, int j){
    Board::LocationList res;
    for(int di=-1;di<=1;di++)
        for(int dj=-1;dj<=1;dj++){
        if(di==0 && dj==0)
            continue;   //  not neighbour
        if(!this->validCoordinate(i+di,j+dj))
            continue;   //  not valid
        res.push_back(std::make_pair(i+di,j+dj));
    }
    return res;
}
