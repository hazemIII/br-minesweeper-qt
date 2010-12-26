#include"IconFactory.h"
IconFactory* IconFactory::ins=0;
IconFactory::IconFactory(){

}
IconFactory* IconFactory::getInstance(){
    if(!ins)ins=new IconFactory();
    return ins;
}
QIcon IconFactory::getIcon(Cell &c){
    int s=c.getState(),v=c.getValue();
    return this->getIcon(s,v);
}
QIcon IconFactory::getIcon(int s, int v){
    if(s==Cell::UNKNOWN)
        return QIcon(":/images/img/UNKNOWN.png");
    else if(s==Cell::MARKED)
        return QIcon(":/images/img/MARKED.png");
    else if(s==Cell::KNOWN){
        if(v==Cell::MINE)
            return QIcon(":/images/img/MINE.png");
        else{
            return QIcon(std::string(":/images/img/"+str(v)+".png").c_str());
        }
    }
    std::cerr<<"Unknown state/value of cell"<<std::endl;
}
