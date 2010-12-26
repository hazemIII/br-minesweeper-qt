#include"Cell.h"
#include<sstream>
Cell::Cell():value(0),state(UNKNOWN){}
bool Cell::validState(int state){
    return state==MARKED || state==KNOWN || state==UNKNOWN;
}
bool Cell::validValue(int value){
    return (value>=0 && value<=8) || value==MINE;
}
int Cell::getState(){
    return this->state;
}
int Cell::getValue(){
    return this->value;
}
void Cell::setState(int new_state){
    if(this->validState(new_state))
        this->state=new_state;
    else
        throw std::invalid_argument("invalid state value: "+str(new_state));
}
void Cell::setValue(int new_value){
    if(this->validValue(new_value))
        this->value=new_value;
    else
        throw std::invalid_argument("invalid");
}
std::string Cell::toString(){
    if(this->state == UNKNOWN)
        return "[ ]";
    else if(this->state == KNOWN){
        if(this->value == MINE)
            return "|*|";
        else if(this->value == 0)
            return "| |";
        else{
            std::stringstream str;
            str<<"|"<<this->value<<"|";
            return str.str();
        }
    }else if(this->state == MARKED)
        return "|M|";
    else
        throw std::invalid_argument(
                "unkonwn state or value "
                "(should never see this if setValue setState works correctly)");
}
