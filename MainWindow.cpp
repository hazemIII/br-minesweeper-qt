#include"MainWindow.h"
#include"IconFactory.h"
#include"HumanPlayer.h"
#include"AIPlayer.h"
#include"NewGameDialog.h"
#include"CompeteGameLogic.h"
#include"NormalGameLogic.h"
#include"RemotePlayer.h"

void MainWindow::newGameSlot(){
    NewGameDialog d(this->gl->getRow(),this->gl->getCol(),this->gl->getNum());
    if(d.exec()){
        int row=d.rowText->text().toInt();
        int col=d.columnText->text().toInt();
        int num=d.mineText->text().toInt();
        try{
            if(d.normalMode->isChecked()){
                if(!this->isNormalMode())this->createNormalGameLogic();
                this->newGame(row,col,num);
            }else if(d.competeMode->isChecked()){
                if(!this->isCompeteMode())this->createCompeteGameLogic();
                CompeteGameLogic * gl_cpt=dynamic_cast<CompeteGameLogic*>(gl);
                Player *p1,*p2;
                if(d.p1=="Human")
                    p1=new HumanPlayer("Player1",gl_cpt);
                else if(d.p1=="AI")
                    p1=new AIPlayer("Player1",gl_cpt,this);
                else
                    throw std::logic_error(std::string("Unknown player: ")+qPrintable(d.p1));

                if(d.p2=="Human")
                    p2=new HumanPlayer("Player2",gl_cpt);
                else if(d.p2=="AI")
                    p2=new AIPlayer("Player2",gl_cpt,this);
                else
                    throw std::logic_error(std::string("Unknown player: ")+qPrintable(d.p2));
                gl_cpt->setPlayer(1,p1);
                gl_cpt->setPlayer(2,p2);
                this->newGame(row,col,num);
            }else if(d.netMode->isChecked()){
                if(!this->isCompeteMode())this->createCompeteGameLogic();
                CompeteGameLogic* gl_cpt=dynamic_cast<CompeteGameLogic*>(gl);
                RemotePlayer* p=new RemotePlayer("Remote Player",gl_cpt,
                                                 this,d.serverAddress->text(),d.portNumber->text().toUShort());
                while(p->getState()==RemotePlayer::CONNECTING)
                    QApplication::processEvents();//busy loop, connecting to server
                if(p->getState()==RemotePlayer::FAIL){
                    QMessageBox::warning(this,tr("Error"),tr("<p>Cannot connect to server.</p>"
                                                             "<p>Start human-human compete mode by default.</p>"));
                    gl_cpt->setPlayer(1,new HumanPlayer("Player1",gl_cpt));
                    gl_cpt->setPlayer(2,new HumanPlayer("Player2",gl_cpt));
                    this->newGame(row,col,num);
                }else if(p->getState()==RemotePlayer::OK){
                    //connect successfully
                    p->send(QString("NEW %1 %2 %3").arg(row).arg(col).arg(num));
                    //should receive game from server soon..
                }else{
                    throw std::logic_error("unknown state of remote player. WTF?");
                }
            }else{
                throw std::logic_error("unknown mode? WTF?");
            }
        }catch(std::exception ){
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
void MainWindow::createCompeteGameLogic(){
    if(gl)delete gl;
    gl=new CompeteGameLogic();

    connect(this->gl,SIGNAL(winSignal()),this,SLOT(winSlot()));
    connect(this->gl,SIGNAL(loseSignal()),this,SLOT(loseSlot()));
}
void MainWindow::createNormalGameLogic(){
    if(gl)delete gl;
    this->gl=new NormalGameLogic();

    connect(this->gl,SIGNAL(winSignal()),this,SLOT(winSlot()));
    connect(this->gl,SIGNAL(loseSignal()),this,SLOT(loseSlot()));
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
    gl=0;
    createNormalGameLogic();
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
    boardCopy.resize(row);
    for(int i=0;i<row;i++){
        buttons[i].resize(col);
        boardCopy[i].resize(col);
    }
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
void MainWindow::winSlot(){
    this->updateGUI();
    if(this->isNormalMode()){
        QMessageBox::information(this,"You Win!",
                                 tr("<h3>Congratulations! You win!</h3>"));
    }else if(this->isCompeteMode()){
        CompeteGameLogic* gl_cpt=dynamic_cast<CompeteGameLogic*>(gl);
        Player* p1=gl_cpt->getPlayer(1),*p2=gl_cpt->getPlayer(2);
        Player* winner=0;
        if(p1->getScore() > p2->getScore())
            winner=p1;
        else if(p1->getScore() < p2->getScore())
            winner=p2;
        QString title,content;
        if(!winner)
            title="Draw!";
        else
            title=winner->getName()+" wins!";
        content="<h3>"+title+"</h3>"+
                QString("<p>Final Score: %1 - %2</p>").arg(p1->getScore()).arg(p2->getScore());
        QMessageBox::information(this,title,content);
    }else{
        throw std::logic_error("Unknown game mode");
    }
}
void MainWindow::loseSlot(){
    this->updateGUI();
    if(this->isNormalMode()){
        QMessageBox::information(this,"You Lose",
                                 tr("<h3>Sorry, You lose.</h3>"
                                    "<p>better luck next time</p>"));
    }else if(this->isCompeteMode()){
        throw std::logic_error("compete mode has no lose slot");
    }else{
        throw std::logic_error("Unknown game mode");
    }
}
void MainWindow::dig(int i, int j){
    if(this->isNormalMode()){
        this->gl->dig(i,j);
    }else if(this->isCompeteMode()){
        //in compete mode, only (exact)humanPlayer or (exact)localPlayer can call this function.
        //all other kinds of players handle it directly themselves
        CompeteGameLogic* gl_cpt=dynamic_cast<CompeteGameLogic*>(gl);
        Player* p=gl_cpt->getCurrentPlayer();
        if(gl_cpt->isExactHumanPlayer(p) || gl_cpt->isExactLocalPlayer(p))
            p->makeMove(i,j);
        else
            printErr("You are not current player.");
    }else{
        throw std::logic_error("Unknown game mode");
    }
    this->updateGUI();
}
void MainWindow::mark(int i, int j){
    if(this->isNormalMode()){
        this->gl->mark(i,j);
    }else if(this->isCompeteMode()){
        //  do nothing, mark is not supported in compete mode
    }else{
        throw std::logic_error("Unknown game mode");
    }
    this->updateGUI();
}
void MainWindow::unmark(int i, int j){
    if(this->isNormalMode()){
        this->gl->unmark(i,j);
    }else if(this->isCompeteMode()){
        //  do nothing, unmark is not supported in compete mode
    }else{
        throw std::logic_error("Unknown game mode");
    }
    this->updateGUI();
}
void MainWindow::toggle(int i, int j){
    if(this->isNormalMode()){
        int s=this->gl->getCell(i,j).getState();
        if(s==Cell::MARKED)
            this->unmark(i,j);
        else if(s==Cell::UNKNOWN)
            this->mark(i,j);
    }else if(this->isCompeteMode()){
        //  do nothing, toggle is not supported in compete mode
    }else{
        throw std::logic_error("Unknown game mode");
    }
}
void MainWindow::explore(int i, int j){
    if(this->isNormalMode()){
        this->gl->explore(i,j);
    }else if(this->isCompeteMode()){
        //  do nothing, unmark is not supported in compete mode
    }else{
        throw std::logic_error("Unknown game mode");
    }
    this->updateGUI();
}
void MainWindow::raiseNeighbourWidgets(int i, int j){
    Board::LocationList lst=this->gl->getNeighbours(i,j);
    for(size_t k=0;k<lst.size();k++){
        MsButton* b=this->buttons[lst[k].first][lst[k].second];
        if(this->gl->getCell(lst[k].first,lst[k].second).getState()==Cell::UNKNOWN){
            b->setIcon(IconFactory::getInstance()->getIcon(Cell::UNKNOWN,0));
        }
    }
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
    if(gl->getState()!=GameLogic::RUN)
        mineNumLabel->setText(tr("Game stopped"));
    else{
        if(this->isNormalMode()){
            int num=gl->getNum(),marked=gl->getMarkedNum();
            int remaining=num-marked;
            mineNumLabel->setText(tr(std::string("Remaining Mines: "+
                                                 str(remaining)).c_str()));
        }else if(this->isCompeteMode()){
            CompeteGameLogic* gl_cpt=dynamic_cast<CompeteGameLogic*>(gl);
            QString content=QString("%1's turn  Score: %2-%3").arg(gl_cpt->getCurrentPlayer()->getName())
                            .arg(gl_cpt->getPlayer(1)->getScore()).arg(gl_cpt->getPlayer(2)->getScore());
            mineNumLabel->setText(content);
        }
    }
}
bool MainWindow::isNormalMode(){
    if(!gl)return false;
    return dynamic_cast<NormalGameLogic*>(gl)!=0;
}
bool MainWindow::isCompeteMode(){
    if(!gl)return false;
    return dynamic_cast<CompeteGameLogic*>(gl)!=0;
}
void MainWindow::updateGUISlot(bool flag){
    updateGUI(flag);
}
