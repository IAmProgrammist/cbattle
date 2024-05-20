QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dump.cpp \
    fieldview.cpp \
    fieldviewedit.cpp \
    initgame.cpp \
    main.cpp \
    movableobjectship.cpp

HEADERS += \
    dump.h \
    fieldview.h \
    fieldviewedit.h \
    initgame.h \
    movableobjectadapter.hpp \
    movableobjectship.h \
    mytcpserver.h

FORMS += \
    game.ui \
    initgame.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
