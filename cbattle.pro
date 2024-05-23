QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/models/field.cpp \
    src/models/game.cpp \
    src/models/ship.cpp \
    src/utils/moveableobjectship.cpp \
    src/widgets/fieldwidget.cpp \
    src/widgets/fieldwidgetedit.cpp \
    src/widgets/initgame.cpp

HEADERS += \
    include/models/field.h \
    include/models/game.h \
    include/models/ship.h \
    include/utils/moveableobjectadapter.hpp \
    include/utils/moveableobjectship.h \
    include/widgets/fieldwidget.h \
    include/widgets/fieldwidgetedit.h \
    include/widgets/initgame.h \
    mytcpserver.h

FORMS += \
    src/ui/game.ui \
    src/ui/initgame.ui \

INCLUDEPATH += include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
