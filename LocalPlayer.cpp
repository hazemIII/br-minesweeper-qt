#include"LocalPlayer.h"

LocalPlayer::LocalPlayer(QString name, CompeteGameLogic *gl, MainWindow *win, RemotePlayer *oppo)
    :HumanPlayer(name,gl){
    this->oppo=oppo;
    connect(this,SIGNAL(needUpdateGUI(bool)),win,SLOT(updateGUISlot(bool)));
}
void LocalPlayer::makeMove(int i, int j){
    if(!oppo->isReady()){
        printErr("Your remote player is not ready yet");
        return;
    }
    oppo->send(QString("DIG %1 %2").arg(i).arg(j));
    HumanPlayer::makeMove(i,j);
    emit this->needUpdateGUI();
}
