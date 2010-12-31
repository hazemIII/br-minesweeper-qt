#ifndef AIPLAYER_H
#define AIPLAYER_H

#include"Player.h"
#include<QThread>

class AIPlayer;     //forward declaration

class AIThread: public QThread{
    Q_OBJECT
public:
    AIThread(AIPlayer* p);
    ~AIThread();
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
    AIPlayer* p;
};
class MainWindow;   //forward declaration
class AIPlayer : public Player{
private:
    AIThread* thread;
    MainWindow *win;
public:
    AIPlayer(QString name, CompeteGameLogic * gl,MainWindow* win); //main window to connect signal
    ~AIPlayer();
    void makeMove(int i=-1,int j=-1);
};

#endif // AIPLAYER_H
