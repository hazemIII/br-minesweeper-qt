#include"Cell.h"
#include"Board.h"
#include"util.h"
#include"GameLogic.h"
#include"NormalGameLogic.h"
using namespace std;
void doCheckCondition(bool res,string msg,const string& file, int line){
    cout<<msg<<": ";
    if(res)cout<<"PASS"<<endl;
    else {
        cout<<"FAIL"<<endl;
        cout<<"\tError at: "<<file<<", line"<<line<<endl;
    }
}

#define checkCondition(res,msg) doCheckCondition(res,msg,__FILE__,__LINE__)

void cellTest(){
    cout<<"****************************************************"<<endl;
    cout<<"Cell Test Starts....."<<endl;
    Cell c;
    if(c.getState()!=Cell::UNKNOWN || c.getValue()!=0){
        cout<<"initializatin error"<<endl;
        exit(-1);
    }
    try{
        c.setState(Cell::KNOWN);
        checkCondition(c.getState()==Cell::KNOWN,"get and set state");

        c.setValue(Cell::MINE);
        checkCondition(c.getValue()==Cell::MINE,"get and set value");

        checkCondition(c.validState(Cell::KNOWN),"valid state test");
        checkCondition(c.validState(Cell::UNKNOWN),"valid state test");
        checkCondition(c.validState(Cell::MARKED),"valid state test");
        checkCondition(!c.validState(Cell::MINE),"valid state test");
    }catch(exception e){
        cout<<"unexpected exception encountered when setting values:"<<endl;
        cout<<e.what()<<endl;
        exit(-1);
    }
}

bool randomConstructedBoard(Board& bd,int row,int col,int num){
    //  check mine number and value for each cell

    if(bd.getRow()!=row || bd.getCol()!=col)return false;
    int ct=0;
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            if(bd.getCell(i,j).getValue()==Cell::MINE){
                ct++;
            }else{
                Board::LocationList lst=bd.getNeighbours(i,j);
                int neighbour_mine_num=0;
                for(size_t k=0;k<lst.size();k++)
                    if(bd.getCell(lst[k].first,lst[k].second).getValue()==Cell::MINE)
                        neighbour_mine_num++;
                if(neighbour_mine_num!=bd.getCell(i,j).getValue())
                    return false;
            }
    return ct==num;
}
bool listConstructedBoard(Board &bd,int row,int col,Board::LocationList& lst){
    if(!randomConstructedBoard(bd,row,col,lst.size()))
        return false;
    for(size_t i=0;i<lst.size();i++)
        if(bd.getCell(lst[i].first,lst[i].second).getValue()!=Cell::MINE)
            return false;
    return true;
}
bool checkNeighbourLst(Board &bd,const Board::LocationList& lst,int i,int j){
    int location_type=0;  // 0:inner, 1:border, 2:corner
    if(i==0 || i==bd.getRow()-1)location_type++;
    if(j==0 || j==bd.getCol()-1)location_type++;

    switch(location_type){
    case 0:
        if (lst.size()!=8)
            return false;
        break;
    case 1:
        if (lst.size()!=5)
            return false;
        break;
    case 2:
        if (lst.size()!=3)
            return false;
        break;
    }
    set<Board::Location> s;
    for(size_t k=0;k<lst.size();k++){
        if(s.count(lst[k])>0)
            return false;
        if(max(abs(lst[k].first-i),abs(lst[k].second-j))!=1)
            return false;
        s.insert(lst[k]);
    }
    return true;
}

void boardTest(){
    cout<<"****************************************************"<<endl;
    cout<<"Board Test Starts....."<<endl;
    Board *bd=new Board(10,10,20);

    Board::LocationList lst;
    int loc[4][2]={
        {0,0},
        {1,1},
        {2,2},
        {3,3},
    };
    lst.clear();
    for(int i=0;i<4;i++)
        lst.push_back(Board::Location(loc[i][0],loc[i][1]));

    checkCondition(checkNeighbourLst(*bd,bd->getNeighbours(0,0),0,0),"neighbours(corner)");
    checkCondition(checkNeighbourLst(*bd,bd->getNeighbours(0,5),0,5),"neighbours(border1)");
    checkCondition(checkNeighbourLst(*bd,bd->getNeighbours(5,0),5,0),"neighbours(border2)");
    checkCondition(checkNeighbourLst(*bd,bd->getNeighbours(5,5),5,5),"neighbours(inner)");
    checkCondition(randomConstructedBoard(*bd,10,10,20),"board random construction");
    delete bd;

    bd=new Board(4,4,lst);
    checkCondition(listConstructedBoard(*bd,4,4,lst),"board construction from list");
    checkCondition(bd->validCoordinate(3,3),"valid coordinate 1");
    checkCondition(!bd->validCoordinate(-1,5),"valid coordinate 2");
    checkCondition(!bd->validCoordinate(0,10),"valid coordinate 2");
    delete bd;
}
bool allRevealed(GameLogic& gl){
    for(int i=0;i<gl.getRow();i++)
        for(int j=0;j<gl.getCol();j++)
            if(gl.getCell(i,j).getState()!=Cell::KNOWN)
                return false;
    return true;
}
void normalGameLogicTest(){
    cout<<"****************************************************"<<endl;
    cout<<"GameLogic Test Starts....."<<endl;
    NormalGameLogic gl;
    checkCondition(gl.getState()==GameLogic::STOP,"get state");
    gl.newGame(10,10,20);
    checkCondition(gl.getState()==GameLogic::RUN,"getState after newGame");
    checkCondition(!gl.checkWin(),"checkWin 1");
    checkCondition(!gl.checkLose(),"checkLose 1");

    Board::LocationList lst;
    int loc[4][2]={
        {0,0},
        {1,1},
        {2,2},
        {3,3},
    };
    lst.clear();
    for(int i=0;i<4;i++)
        lst.push_back(Board::Location(loc[i][0],loc[i][1]));
    gl.newGame(4,4,lst);
    gl.dig(0,0);
    checkCondition(!gl.checkWin(),"checkWin 2");
    checkCondition(gl.checkLose(),"checkLose 2");
    checkCondition(allRevealed(gl),"all revealed");
    gl.newGame(4,4,lst);
    gl.dig(3,0);
    gl.dig(0,3);
    for(size_t i=0;i<lst.size();i++)
        gl.mark(lst[i].first,lst[i].second);
    gl.explore(1,2);
    gl.explore(2,1);
    checkCondition(gl.checkWin(),"checkWin 3");
    checkCondition(!gl.checkLose(),"checkLose 3");
}

#if MODE==TEST_MODE

int main(){
    cellTest();
    boardTest();
    normalGameLogicTest();
    return 0;
}

#endif
