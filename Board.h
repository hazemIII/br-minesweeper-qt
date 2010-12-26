#ifndef BOARD_H
#define BOARD_H

#include"Cell.h"
#include"util.h"

class Board{
public:
    typedef std::pair<int,int> Location;
    typedef std::vector<Location> LocationList;
    const static int MAX_ROW_NUM=30;
    const static int MAX_COLUMN_NUM=30;
    const static int MIN_ROW_NUM=3;
    const static int MIN_COLUMN_NUM=3;
private:
    int row,col;    //  size of the board
    Cell** board;
    void randomlyFillMines(int num);
    void fillMineByLocationList(const LocationList& lst);
    void setupValues();
public:

    Board(int row,int col,int num);
    Board(int row,int col, const LocationList& lst);
    ~Board();
    int getRow() ;
    int getCol() ;
    Cell& getCell(int i,int j);
    std::string toString();
    bool validCoordinate(int i,int j);
    LocationList getNeighbours(int i,int j);
};
#endif // BOARD_H
