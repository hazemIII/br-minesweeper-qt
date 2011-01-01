HEADERS += GameLogic.h \
    Cell.h \
    Board.h \
    util.h \
    NormalGameLogic.h \
    MainWindow.h \
    MsButton.h \
    IconFactory.h \
    NewGameDialog.h \
    ui_NewGameDialog.h \
    CompeteGameLogic.h \
    HumanPlayer.h \
    Player.h \
    AIPlayer.h \
    RemotePlayer.h \
    LocalPlayer.h
SOURCES += Cell.cpp \
    Board.cpp \
    util.cpp \
    GameLogic.cpp \
    NormalGameLogic.cpp \
    test.cpp \
    TextUI.cpp \
    MainWindow.cpp \
    MsButton.cpp \
    IconFactory.cpp \
    main.cpp \
    NewGameDialog.cpp \
    Player.cpp \
    HumanPlayer.cpp \
    CompeteGameLogic.cpp \
    AIPlayer.cpp \
    RemotePlayer.cpp \
    LocalPlayer.cpp
RESOURCES += resource.qrc
FORMS += *.ui
QT += network
