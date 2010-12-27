#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include<QIcon>
#include"Cell.h"

//singleton pattern, so each icon is also unique
class IconFactory{    
private:
    static IconFactory* ins;
    IconFactory();     //  in order to initialize icons...
    QIcon *UNKNOWN,*MARKED,*MINE,*NUM[9];   //keep one copy only, no need to read data each time.
public:
    static IconFactory* getInstance();
    const QIcon& getIcon(Cell& c) const;
    const QIcon& getIcon(int state,int value) const;
};

#endif // ICONFACTORY_H
