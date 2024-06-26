QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/game/abstractgamebuilder.cpp \
    src/game/client/botclient.cpp \
    src/game/client/client.cpp \
    src/game/client/connection.cpp \
    src/game/client/connectionstrategy.cpp \
    src/game/client/localconnectionstrategy.cpp \
    src/game/client/tcpconnectionstrategy.cpp \
    src/game/server/conneciton.cpp \
    src/game/server/localconnection.cpp \
    src/game/server/server.cpp \
    src/game/gamebuilder.cpp \
    src/game/server/tcpconnection.cpp \
    src/models/field.cpp \
    src/models/game.cpp \
    src/models/ship.cpp \
    src/utils/moveableobjectship.cpp \
    src/widgets/fieldstyle.cpp \
    src/widgets/fieldwidget.cpp \
    src/widgets/fieldwidgetedit.cpp \
    src/widgets/fieldwidgetplayenemy.cpp \
    src/widgets/gamewindow.cpp \
    src/widgets/initgame.cpp \
    src/main.cpp

HEADERS += \
    include/game/abstractgamebuilder.h \
    include/game/client/botclient.h \
    include/game/client/client.h \
    include/game/client/connection.h \
    include/game/client/connectionstrategy.h \
    include/game/client/localconnectionstrategy.h \
    include/game/client/tcpconnectionstrategy.h \
    include/game/server/connection.h \
    include/game/server/localconnection.h \
    include/game/server/server.h \
    include/game/gamebuilder.h \
    include/game/server/tcpconnection.h \
    include/models/field.h \
    include/models/game.h \
    include/models/ship.h \
    include/utils/moveableobjectadapter.hpp \
    include/utils/moveableobjectship.h \
    include/widgets/fieldstyle.h \
    include/widgets/fieldwidget.h \
    include/widgets/fieldwidgetedit.h \
    include/widgets/fieldwidgetplayenemy.h \
    include/widgets/gamewindow.h \
    include/widgets/initgame.h

FORMS += \
    src/ui/game.ui \
    src/ui/initgame.ui \

INCLUDEPATH += include

RC_ICONS += src/assets/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    model.qmodel
