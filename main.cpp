/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: main.cpp
Description:

Runs the Qt app
*/

#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // double the window scaling with this
    //qputenv("QT_SCALE_FACTOR", "2.0");
    QApplication app(argc, argv);
    //app.setAttribute(Qt::AA_EnableHighDpiScaling);
    Main_window menu;
    menu.show();

    return app.exec();
}
