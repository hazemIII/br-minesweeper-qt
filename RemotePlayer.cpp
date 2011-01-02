#include"RemotePlayer.h"
#include"CompeteGameLogic.h"
#include"MainWindow.h"
#include<QStringList>
#include"LocalPlayer.h"

void RemotePlayer::makeMove(int i, int j){
    HumanPlayer::makeMove(i,j);
}
void RemotePlayer::socketHostFound(){
    printErr("host found");
}
bool RemotePlayer::isReady(){return readyToPlay;}

void RemotePlayer::socketConnected(){
    printErr("connection esdablished");
    state=OK;
}
void RemotePlayer::socketError(){
    printErr("error occurs");
    state=FAIL;
}
RemotePlayer::~RemotePlayer(){
    printErr("Player deleted\n");
    socket->close();
    delete socket;
}
int RemotePlayer::getState(){return state;}
RemotePlayer::RemotePlayer(QString name, CompeteGameLogic *gl,MainWindow* win,QString addr,quint16 port)
    :HumanPlayer(name,gl){
    readyToPlay=false;
    socket=new QTcpSocket();

    connect(socket,SIGNAL(hostFound()),this,SLOT(socketHostFound()));
    connect(socket,SIGNAL(connected()),this,SLOT(socketConnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReadyRead()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError()));

    connect(this,SIGNAL(newGameFromServer(QString)),gl,SLOT(handleGameFromServer(QString)));

    connect(this,SIGNAL(needUpdageGUI(bool)),win,SLOT(updateGUISlot(bool)));

    //construct its opponent automatically
    oppo=new LocalPlayer("You",gl,win,this);
    state=CONNECTING;
    socket->connectToHost(addr,port);
}
void RemotePlayer::send(QString s){
    if(state!=OK){
        printErr("Cannot send message: socket is not connected to server\n");
        return ;
    }
    std::cerr<<"[send] "<<qPrintable(s)<<std::endl;
    if(!s.endsWith("\n"))s+="\n";
    socket->write(s.toAscii());
}
void RemotePlayer::socketReadyRead(){
    while(socket->canReadLine()){
        QString s=socket->readLine().trimmed().toUpper();
        std::cerr<<"[receive] "<<qPrintable(s)<<std::endl;
        if(s=="READY"){
            readyToPlay=true;
            //by now, both sides should have already construct board
            emit this->needUpdageGUI(true);
        }else if(s.startsWith("PLAYER")){
            emit this->newGameFromServer(s);
            //should handled by game logic
            emit this->needUpdageGUI(true);
        }else if(s.startsWith("DIG")){
            s=s.mid(3).trimmed();
            QStringList ss=s.split(" ");
            int i=ss.at(0).toInt();
            int j=ss.at(1).toInt();
            this->makeMove(i,j);
            emit this->needUpdageGUI();
        }else if(s=="BYE"){
            socket->close();
        }
    }
}
Player* RemotePlayer::getOpponent(){
    return dynamic_cast<Player*>(oppo);
}
