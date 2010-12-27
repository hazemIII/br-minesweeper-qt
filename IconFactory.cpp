#include"IconFactory.h"
IconFactory* IconFactory::ins=0;
IconFactory::IconFactory(){
    UNKNOWN=new QIcon(":/images/img/UNKNOWN.png");
    MARKED=new QIcon(":/images/img/MARKED.png");
    MINE=new QIcon(":/images/img/MINE.png");
    for(int i=0;i<9;i++)
        NUM[i] = new QIcon(std::string(":/images/img/"+str(i)+".png").c_str());
}
IconFactory* IconFactory::getInstance(){
    if(!ins)ins=new IconFactory();
    return ins;
}
const QIcon& IconFactory::getIcon(Cell &c) const{
    int s=c.getState(),v=c.getValue();
    return this->getIcon(s,v);
}
const QIcon& IconFactory::getIcon(int s, int v) const{
    if(s==Cell::UNKNOWN)
        return *UNKNOWN;
    else if(s==Cell::MARKED)
        return *MARKED;
    else if(s==Cell::KNOWN){
        if(v==Cell::MINE)
            return *MINE;
        else
            return *NUM[v];
    }
    std::cerr<<"Unknown state/value of cell"<<std::endl;
    return *UNKNOWN;        //to silent warnings
}
