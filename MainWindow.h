#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QtGui>
#include"NormalGameLogic.h"
#include"MsButton.h"
#include<vector>

class MainWindow: public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=0);
    void updateGUI(bool rebuildBoard=false);
    void newGame(int row,int col,int num);
    void dig(int i,int j);
    void mark(int i,int j);
    void unmark(int i,int j);
    void explore(int i,int j);
    void toggle(int i,int j);
    void sunkNeighbourWidgets(int i,int j);
    void raiseNeighbourWidgets(int i,int j);

    void createBoard(int row,int col);
    void createGameLogic();
    void initializeWidgets();
    void createMenuBar();
    void createActions();
    void checkWinLose();
private:
    std::vector<std::vector<MsButton*> > buttons;
    GameLogic *gl;
    QWidget *central;
    QFrame *frame;
    QAction *newGameAction;
    QAction *quitAction;
    QMenu* gameMenu;
public slots:
    void newGameSlot();
};

#endif // MAINWINDOW_H
