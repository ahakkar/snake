/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: constants.h
Description:

Header contains constants used in the game, in one place.
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QWidget>

// # Main_window class

// main menu size
inline static constexpr int MENU_SIZE_X = 640;
inline static constexpr int MENU_SIZE_Y = 480;

// one square's size
inline const int GAME_SQUARE_WIDTH = 32;
inline const int GAME_SQUARE_HEIGHT = 32;

// default gamespeed in ms
inline const QString DEFAULT_GAME_SPEED = QString::number(100);

// # Game_board class

inline const int GFX_FPS = 10;

// snake rainbow colors
inline const QColor snake_00 = QColor(255, 0, 0);
inline const QColor snake_01 = QColor(255, 128, 0);
inline const QColor snake_02 = QColor(255, 255, 0);
inline const QColor snake_03 = QColor(128, 255, 0);
inline const QColor snake_04 = QColor(0, 255, 0);
inline const QColor snake_05 = QColor(0, 255, 128);
inline const QColor snake_06 = QColor(0, 255, 255);
inline const QColor snake_07 = QColor(0, 128, 255);
inline const QColor snake_08 = QColor(0, 0, 255);
inline const QColor snake_09 = QColor(128, 0, 255);
inline const QColor snake_10 = QColor(255, 0, 255);
inline const QColor snake_11 = QColor(255, 0, 128);

// snake colors
inline const std::vector<QColor> SNAKE_COLORS =
    {snake_00, snake_01, snake_02, snake_03, snake_04, snake_05,
     snake_06, snake_07, snake_08, snake_09, snake_10, snake_11};

inline const QColor DEFAULT_TILE_COLOR = QColor(255, 255, 255);;

// Constants for printing the gameboard
inline const QString HEAD = "@";
inline const QString BODY = "o";
inline const QString TAIL = "X";
inline const QString FOOD = "*";
inline const QString DEAD = "X";

// walls and corners
inline const QString HOR_WALL = "═";
inline const QString VER_WALL = "║";
inline const QString CORNER_WALL = "╬";
inline const QString CORNER_NW = "╔";
inline const QString CORNER_NE = "╗";
inline const QString CORNER_SW = "╚";
inline const QString CORNER_SE = "╝";

inline const QString EMPTY = " ";

// default game board size
inline constexpr int DEFAULT_WIDTH = 40;
inline constexpr int DEFAULT_HEIGHT = 30;
inline constexpr int DEFAULT_SEED = 1;

// # Point class #

// Constants for directions
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';

// # *_item class #

// right
inline const qreal DEFAULT_ANGLE = 270;

// map of used gfx tile locations
inline const std::map<QString, std::string> GFX_TILES = {
    {HEAD, ":/img/head.png"},
    {BODY, ":/img/body.png"},
    {TAIL, ":/img/tail.png"},
    {FOOD, ":/img/food.png"},
    {HOR_WALL, ":/img/hor_wall.png"},
    {VER_WALL, ":/img/ver_wall.png"},
    {CORNER_NW, ":/img/nw_wall.png"},
    {CORNER_NE, ":/img/ne_wall.png"},
    {CORNER_SW, ":/img/sw_wall.png"},
    {CORNER_SE, ":/img/se_wall.png"},
};

// not used
inline const std::vector<QString> SNAKE_PARTS = {HEAD, BODY, TAIL};

#endif // CONSTANTS_H
