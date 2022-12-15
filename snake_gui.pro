QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CFLAGS_WARN_ON = -Wall -Wextra

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block_item.cpp \
    game_board.cpp \
    main.cpp \
    main_window.cpp \
    point.cpp \
    snake_item.cpp

HEADERS += \
    block_item.h \
    constants.h \
    game_board.h \
    main_window.h \
    point.h \
    snake_item.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    snake.qrc

DISTFILES += \
    README.md \
    instructions.txt

