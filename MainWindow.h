#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QtGui>
#include"GameLogic.h"
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
    void sinkNeighbourWidgets(int i,int j);
    void sinkWidgetsIfUnknown(int i,int j);
    void raiseNeighbourWidgets(int i,int j);
    void raiseWidgetsIfUnknown(int i,int j);

    void createStatusBar();
    void createBoard(int row,int col);
    void createNormalGameLogic();
    void createCompeteGameLogic();
    void initializeWidgets();
    void createMenuBar();
    void createActions();
    void updateStatusBar();

    bool isCompeteMode();
    bool isNormalMode();
private:
    std::vector<std::vector<MsButton*> > buttons;
    std::vector<std::vector<Cell> > boardCopy;
    GameLogic *gl;
    QWidget *central;
    QFrame *frame;
    QAction *newGameAction;
    QAction *quitAction;
    QAction *aboutAction;
    QMenu* gameMenu;
    QMenu* helpMenu;
    QLabel* mineNumLabel;
public slots:
    void newGameSlot();
    void aboutSlot();
    void winSlot();
    void loseSlot();
};

#endif // MAINWINDOW_H
