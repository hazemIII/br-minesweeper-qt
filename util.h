#ifndef UTIL_H
#define UTIL_H

//  necessary header files from clib and stl
//  all header file must include this file
#include<string>
#include<cstdlib>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<set>
#include<stdexcept>
#include<algorithm>
#include<QString>
#include<time.h>

#define TEST_MODE 0
#define TEXTUI_MODE 1
#define GUI_MODE 2

#define MODE GUI_MODE

void printErr(const std::string & msg);    //  print message to stderr
int randInt(int a,int b);       //  return random integer from [a,b]
std::string str(int n);              //return string form of the ingeger
QString qstr(int n);            //same as str(n), return QString
#endif // UTIL_H
