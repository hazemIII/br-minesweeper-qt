#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H


#include"HumanPlayer.h"
#include<QTcpSocket>

//  remote player has the same behavior as human
class MainWindow;
class LocalPlayer;
class RemotePlayer :public QObject, public HumanPlayer{
    Q_OBJECT
private:
    QTcpSocket* socket;
    bool readyToPlay;
    int state;
    LocalPlayer* oppo;
public:
    enum{
        CONNECTING,
        OK,
        FAIL,
    };
    RemotePlayer(QString name, CompeteGameLogic * gl,MainWindow* win,QString addr,quint16 port);
    ~RemotePlayer();
    void send(QString s);
    Player* getOpponent();
    void makeMove(int i, int j);
    bool isReady();
    int getState();
signals:
    void newGameFromServer(QString s);
    void needUpdageGUI(bool flag=false);
private slots:

    void socketHostFound();
    void socketConnected();
    void socketReadyRead();
    void socketError();
};

#endif // REMOTEPLAYER_H
