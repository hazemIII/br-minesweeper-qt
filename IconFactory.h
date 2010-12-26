#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include<QIcon>
#include"Cell.h"

//singleton pattern, so each icon is also unique
class IconFactory{    
private:
    static IconFactory* ins;
    IconFactory();     //  in order to initialize icons...
public:
    static IconFactory* getInstance();
    QIcon getIcon(Cell& c);
};

#endif // ICONFACTORY_H
