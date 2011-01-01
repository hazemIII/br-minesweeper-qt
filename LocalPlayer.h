#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include"RemotePlayer.h"
class MainWindow;
class LocalPlayer :public QObject, public HumanPlayer{
    Q_OBJECT
private:
    RemotePlayer* oppo;
public:
    LocalPlayer(QString name, CompeteGameLogic * gl,MainWindow* win,RemotePlayer* oppo);
    void makeMove(int i, int j);
signals:
    void needUpdateGUI(bool flag=false);
};


#endif // LOCALPLAYER_H
