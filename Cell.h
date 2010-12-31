#ifndef CELL_H
#define CELL_H


#include"util.h"
#include<QObject>

class Cell {
private:
    int value;                  //  value of the cell, can be 0-8, or -1(mine)
    int state;                  //  state value, can be MARKED,KNOWN or UNKNOWN
public:
    Cell();
    enum{                       //  for value
        MINE=-1,    // not 0 - 9
    };
    enum{                       //  for state
        MARKED=1,
        UNKNOWN=2,
        KNOWN=3,
    };
    bool operator==(const Cell& c)const;
    bool operator!=(const Cell& c)const;
    bool validState(int state);
    bool validValue(int value);
    int getValue();
    void setValue(int new_value);
    int getState();
    void setState(int new_state);
    std::string toString();
};
#endif // CELL_H
