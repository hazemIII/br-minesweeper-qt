#ifndef NORMALGAMELOGIC_H
#define NORMALGAMELOGIC_H

#include"GameLogic.h"
#include"util.h"

class NormalGameLogic:public GameLogic{
public:
    virtual void dig(int i,int j);
    virtual void mark(int i,int j);
    virtual void unmark(int i,int j);
    virtual void explore(int i,int j);
    virtual bool checkWin();
    virtual bool checkLose();

private:
    bool markedNeighboursNumberOK(int i,int j);
    void digAllUnknownNeighbours(int i,int j);
};

#endif // NORMALGAMELOGIC_H
