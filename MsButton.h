#ifndef MSBUTTON_H
#define MSBUTTON_H

#include"GameLogic.h"
#include<QtGui>

class MainWindow;   //forward declaration

class MsButton : public QPushButton{
    Q_OBJECT
/*
    before starting new game, state must b 0, gui must be initialized
*/
private:
    int i,j;    //  location

public:         //  in order to initialize...
    MsButton(QWidget *parent,int _i,int _j);

    static int state;
    static MainWindow* gui;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};
#endif // MSBUTTON_H
