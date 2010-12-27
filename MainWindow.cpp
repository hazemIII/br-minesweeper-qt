#include"MainWindow.h"
#include"IconFactory.h"
#include"NewGameDialog.h"
void MainWindow::newGameSlot(){
    NewGameDialog d(this->gl->getRow(),this->gl->getCol(),this->gl->getNum());
    if(d.exec()){
        int row=d.rowText->text().toInt();
        int col=d.columnText->text().toInt();
        int num=d.mineText->text().toInt();
        try{
            this->newGame(row,col,num);
        }catch(std::exception e){
            QMessageBox::warning(this,tr("Invalid input"),
                                 tr(("<h4>Invalid input encountered</h4>"
                                     "<ul>"
                                     "<li>row within ["+str(Board::MIN_ROW_NUM)+","+str(Board::MAX_ROW_NUM)+"]</li>"
                                     "<li>column within ["+str(Board::MIN_COLUMN_NUM)+","+str(Board::MAX_COLUMN_NUM)+"]</li>"
                                     "<li>mine number within [0,row*column]</li>"
                                     "</ul>").c_str()),
                                 QMessageBox::Ok);
        }
    }
}
void MainWindow::createGameLogic(){
    this->gl=new NormalGameLogic();
}
void MainWindow::initializeWidgets(){
    this->central=new QWidget(this);
    this->setCentralWidget(this->central);
    this->frame=0;
}
void MainWindow::createMenuBar(){
    this->gameMenu=this->menuBar()->addMenu(tr("&Game"));
    this->gameMenu->addAction(this->newGameAction);
    this->gameMenu->addAction(this->quitAction);

    this->helpMenu=this->menuBar()->addMenu(tr("&Help"));
    this->helpMenu->addAction(this->aboutAction);
}
void MainWindow::createActions(){
    this->newGameAction=new QAction(tr("&New Game"),this);
    this->newGameAction->setStatusTip(tr("start a new game"));
    this->newGameAction->setShortcut(tr("Ctrl+n"));
    //this->newGameAction->setIcon(QIcon(":/images/img/new.png"));  //doesn't work?
    connect(this->newGameAction,SIGNAL(triggered()),this,SLOT(newGameSlot()));

    this->quitAction=new QAction(tr("&Quit"),this);
    this->quitAction->setStatusTip(tr("quit QMineSweeper"));
    this->quitAction->setShortcut(tr("Ctrl+q"));
    //this->quitAction->setIcon(QIcon(":/images/img/quit.png"));    //doesn't work?
    connect(this->quitAction,SIGNAL(triggered()),this,SLOT(close()));

    this->aboutAction=new QAction(tr("&About"),this);
    this->aboutAction->setShortcut(tr("Ctrl+h"));
    connect(this->aboutAction,SIGNAL(triggered()),this,SLOT(aboutSlot()));
}
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent){
    this->move(300,200);
    this->setWindowIcon(QIcon(":/images/img/logo.png"));
    createGameLogic();
    initializeWidgets();
    createBoard(Board::MAX_ROW_NUM,Board::MAX_COLUMN_NUM);
    createActions();
    createMenuBar();
    createStatusBar();
    this->newGame(10,10,10);    //start a new game by default
}
void MainWindow::createBoard(int row, int col){
    this->frame=new QFrame(this->central);
    this->frame->setGeometry(QRect(0,0,20*col,20*row));
    buttons.clear();
    buttons.resize(row);
    for(int i=0;i<row;i++)
        buttons[i].resize(col);
    boardCopy.clear();
    boardCopy.resize(row);;
    for(int i=0;i<row;i++)
        boardCopy[i].resize(col);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            MsButton *b=new MsButton(this->frame,i,j);
            b->setGeometry(QRect(j*20,i*20,21,21));
            b->setIcon(IconFactory::getInstance()->getIcon(Cell::UNKNOWN,0)); //initialize icon
            buttons[i][j]=b;
        }
    }
}
void MainWindow::updateGUI(bool rebuildBoard){
    int row=this->gl->getRow(),col=this->gl->getCol();
    if(rebuildBoard){
        this->setFixedSize(col*20,row*20+menuBar()->sizeHint().height()
                           +statusBar()->sizeHint().height());
    }
    for(int i =0;i<row;i++)
        for(int j=0;j<col;j++){
        MsButton* b=buttons[i][j];
        Cell& c=gl->getCell(i,j);
        if(boardCopy[i][j]!=c){
            b->setIcon(IconFactory::getInstance()->getIcon(c));
            boardCopy[i][j]=c;
        }
    }
    updateStatusBar();
}
void MainWindow::newGame(int row, int col,int num){
    /**initialize static variables**/
    MsButton::state=0;
    MsButton::gui=this;
    /******************************/
    this->gl->newGame(row,col,num);
    this->updateGUI(true);
}
void MainWindow::checkWinLose(){
    if(this->gl->checkWin()){
        QMessageBox::information(this,"You Win!",
                                 tr("<h3>Congratulations! You win!</h3>"));
    }else if(this->gl->checkLose()){
        QMessageBox::information(this,"You Lose",
                                 tr("<h3>Sorry, You lose.</h3>"
                                    "<p>better luck next time</p>"));
    }
}
void MainWindow::dig(int i, int j){
    this->gl->dig(i,j);
    this->updateGUI();
    this->checkWinLose();
}
void MainWindow::mark(int i, int j){
    this->gl->mark(i,j);
    this->updateGUI();
    this->checkWinLose();
}
void MainWindow::unmark(int i, int j){
    this->gl->unmark(i,j);
    this->updateGUI();
}
void MainWindow::toggle(int i, int j){
    int s=this->gl->getCell(i,j).getState();
    if(s==Cell::MARKED)
        this->unmark(i,j);
    else if(s==Cell::UNKNOWN)
        this->mark(i,j);
}
void MainWindow::explore(int i, int j){
    this->gl->explore(i,j);
    this->updateGUI();
    this->checkWinLose();
}
void MainWindow::raiseNeighbourWidgets(int i, int j){
    Board::LocationList lst=this->gl->getNeighbours(i,j);
    for(size_t k=0;k<lst.size();k++){
        MsButton* b=this->buttons[lst[k].first][lst[k].second];
        if(this->gl->getCell(lst[k].first,lst[k].second).getState()==Cell::UNKNOWN){
            b->setIcon(IconFactory::getInstance()->getIcon(Cell::UNKNOWN,0));
        }
    }
    //this->updateGUI();
}
void MainWindow::sinkWidgetsIfUnknown(int i, int j){
    if(gl->getCell(i,j).getState()==Cell::UNKNOWN)
        buttons[i][j]->setIcon(IconFactory::getInstance()->getIcon(Cell::KNOWN,0));
}
void MainWindow::raiseWidgetsIfUnknown(int i, int j){
    if(gl->getCell(i,j).getState()==Cell::UNKNOWN)
        buttons[i][j]->setIcon(IconFactory::getInstance()->getIcon(Cell::UNKNOWN,0));
}
void MainWindow::sinkNeighbourWidgets(int i, int j){
    Board::LocationList lst=this->gl->getNeighbours(i,j);
    for(size_t k=0;k<lst.size();k++){
        MsButton* b=this->buttons[lst[k].first][lst[k].second];
        if(this->gl->getCell(lst[k].first,lst[k].second).getState()==Cell::UNKNOWN)
            b->setIcon(IconFactory::getInstance()->getIcon(Cell::KNOWN,0));
    }
    //this->updateGUI();    //should not update here, or else sunken fails immediately
}
void MainWindow::aboutSlot(){
    QMessageBox::about(this,tr("About"),tr("<h2>QMineSweeper</h2>"
                                           "<p>This is a mine sweeper game implemented in QT</p>"
                                           "<p>This is part of br-minesweeper project.</p>"));
}
void MainWindow::createStatusBar(){
    mineNumLabel=new QLabel(this);
    this->statusBar()->addWidget(mineNumLabel);
}
void MainWindow::updateStatusBar(){
    int num=gl->getNum(),marked=gl->getMarkedNum();
    if(marked==-1)
        mineNumLabel->setText(tr("Game stopped"));
    else{
        int remaining=num-marked;
        mineNumLabel->setText(tr(std::string("Remaining Mines: "+
                                             str(remaining)).c_str()));
    }
}
