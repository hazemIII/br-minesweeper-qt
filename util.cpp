#include"util.h"
void printErr(const std::string & msg){
    std::cerr<<msg<<std::endl;
}
int randInt(int a, int b){
    if(a > b){
        printErr("invalid randInt range");
        exit(-1);
    }
    return rand() % (b-a) + a;
}
std::string str(int n){
    std::stringstream ss;
    ss<<n;
    return ss.str();
}
QString qstr(int n){
    return QString(str(n).c_str());
}
