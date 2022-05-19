QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    easygame.cpp \
    game.cpp \
    gameover.cpp \
    hardgame.cpp \
    main.cpp \
    mineblock.cpp \
    newgamechoice.cpp \
    normalgame.cpp \
    score.cpp \
    startscene.cpp \
    win.cpp

HEADERS += \
    easygame.h \
    game.h \
    gameover.h \
    hardgame.h \
    mineblock.h \
    newgamechoice.h \
    normalgame.h \
    score.h \
    startscene.h \
    win.h

FORMS += \
    easygame.ui \
    gameover.ui \
    hardgame.ui \
    newgamechoice.ui \
    normalgame.ui \
    score.ui \
    startscene.ui \
    win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rec.qrc
