/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: main_window.h
Description:

Class is used to draw the main menu on screen, and to call the actual
game window.
*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "game_board.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
class QGroupBox;
class QMenu;
class QMenuBar;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QMainWindow;
class QVBoxLayout;
class QGuiApplication;
class QDebug;
QT_END_NAMESPACE

/*
 *  snake game
 */

class Main_window : public QMainWindow
{
    Q_OBJECT

public:
    Main_window(QWidget *parent = nullptr);
    ~Main_window();

private slots:
    // creates a new game window
    void new_game_window();

    // when pressing resume game, hides the menu again
    void resume_game();

    // self-explanatory methods
    void adjust_title_text_won();
    void adjust_title_text_lost();
    void adjust_main_menu_after_gameover();

private:
    // contains the main menu
    QWidget *main_widget;

    // contains the game board tiles. when restarting, delete this and create
    // a new one
    Game_board* game_board = nullptr;

    // contains main menu layout
    QVBoxLayout *main_layout;

    // contains main menu button layout
    QGroupBox *main_menu_grid;

    // some main menu elements which need to be accessed elsewhere
    QLabel* title_text;
    QLineEdit* box_width;
    QLineEdit* box_height;
    QLineEdit* box_seed;
    QLineEdit* box_gamespeed;
    QCheckBox* box_gfx_toggle;
    QPushButton* game_reset_button;
    QPushButton* game_push_button;

    // creates main menu buttons
    void create_main_menu();

    // seed
    int SEED_VALUE = 1;

    // user can dynamically adjust the grid size
    // preferrably to odd size
    int GAME_SQUARES_X = 40;
    int GAME_SQUARES_Y = 30;


    // game window's total size
    int GAME_WINDOW_SIZE_X = GAME_SQUARES_X * GAME_SQUARE_WIDTH;
    int GAME_WINDOW_SIZE_Y = GAME_SQUARES_Y * GAME_SQUARE_HEIGHT;

    int SCREEN_X = 0;
    int SCREEN_Y = 0;

};
#endif // MAIN_WINDOW_H
