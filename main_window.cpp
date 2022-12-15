/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: main_window.cpp
Description:

Class is used to draw the main menu on screen, and to call the actual
game window.
*/

#include <QtWidgets>
#include "main_window.h"

Main_window::Main_window(QWidget* parent) :
    QMainWindow(parent)
{
    // create a new widget, which we set as central widget
    // we add GUI items to this widget
    main_widget = new QWidget();
    main_widget->setStyleSheet("background-color: rgb(80,80,80);");

    // create the main menu components and add it to layout
    main_layout = new QVBoxLayout();    
    create_main_menu();
    main_layout->addWidget(main_menu_grid);

    // add the created layout to screen
    main_widget->setLayout(main_layout);
    this->setCentralWidget(main_widget);

    // window title
    this->setWindowTitle(tr("Snake - Main menu"));

    // screen x, y size
    QRect screen_specs = main_widget->screen()->availableGeometry();
    // used later in game_board since it doesn't support screen->()..
    SCREEN_X = screen_specs.width();
    SCREEN_Y = screen_specs.height();

    // centers the menu to screen.
    // define window x,y size in QSize()
    this->setGeometry(
        QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        QSize(MENU_SIZE_X, MENU_SIZE_Y),
        main_widget->screen()->availableGeometry()
    ));
}

Main_window::~Main_window()
{
    QCoreApplication::quit();
}

void Main_window::new_game_window()
{
    this->hide();
    // if restarting game, delete old game window
    if (game_board != nullptr) {
        game_board->close();
        main_widget->setStyleSheet("background-color: rgb(80,80,80);");
        title_text->setText("Snake");
    }
    // toint requires a bool. since boxes use 0-9 ASCII filter values should
    // always be ok
    bool ok;

    // when starting the game, change start button to display resume instead
    game_push_button->setText("Resume game");

    // disconnect old start game connection
    disconnect(game_push_button, &QPushButton::clicked, 0, 0);

    // create a new resume game connection
    connect(game_push_button, &QPushButton::clicked,
            this, &Main_window::resume_game);

    // enable reset game button
    game_reset_button->setVisible(true);

    // avoid creating a too small window. could do this better if I had more
    // programming skill.
    int width_read_from_input_box = box_width->text().toInt(&ok, 10);
    int height_read_from_input_box = box_height->text().toInt(&ok, 10);
    int game_speed = box_gamespeed->text().toInt(&ok, 10);

    if (width_read_from_input_box < 20) {
        width_read_from_input_box = 20;
    }
    if (height_read_from_input_box < 20) {
        height_read_from_input_box = 20;
    }
    if (game_speed < 50) {
        game_speed = 100;
    }

    game_board = new Game_board(this,
                                width_read_from_input_box,
                                height_read_from_input_box,
                                box_seed->text().toInt(&ok, 10),
                                game_speed,
                                box_gfx_toggle->checkState());
    game_board->setWindowFlags(Qt::Window); //  | Qt::FramelessWindowHint
    game_board->setWindowTitle(tr("Snake v. 0.7"));

    game_board->setGeometry(
        QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        QSize(width_read_from_input_box*GAME_SQUARE_WIDTH,
              height_read_from_input_box*GAME_SQUARE_HEIGHT),
        QRect(QPoint(0,0),QPoint(SCREEN_X, SCREEN_Y))
    ));

    // disable resizing by setting window to a fixed size
    // 5 comes from making the window slightly larger so the game board
    // doesn't scroll around inside the window.
    game_board->setFixedSize(width_read_from_input_box*GAME_SQUARE_WIDTH+5,
                             height_read_from_input_box*GAME_SQUARE_HEIGHT+5);

    connect(game_board, &Game_board::game_won_signal,
            this, &Main_window::adjust_title_text_won);
    connect(game_board, &Game_board::game_lost_signal,
            this, &Main_window::adjust_title_text_lost);

    game_board->show();
}

void Main_window::resume_game()
{
    this->hide();
    game_board->start_timer();
    //emit unPauseGame();
}

void Main_window::adjust_title_text_won()
{
    //QPalette pal = QPalette();
    //pal.setColor(QPalette::Window, "#000000");
    main_widget->setStyleSheet("background-color: rgb(0,160,0);");
    this->title_text->setText("You won!");
    this->adjust_main_menu_after_gameover();
}

void Main_window::adjust_title_text_lost()
{
    main_widget->setStyleSheet("background-color: rgb(160,0,0);");
    this->title_text->setText("You lost :-(");
    this->adjust_main_menu_after_gameover();
}

void Main_window::adjust_main_menu_after_gameover()
{
    // disconnect old start game connection
    disconnect(game_push_button, &QPushButton::clicked, 0, 0);
    connect(game_push_button, &QPushButton::clicked,
            this, &Main_window::new_game_window);
    game_push_button->setText("Start a new game");
    this->game_reset_button->hide();
}

void Main_window::create_main_menu()
{    
    // init layout
    main_menu_grid = new QGroupBox();
    QGridLayout *layout = new QGridLayout;

    /*addWidget params: row y, col x. row span y, col span x */

    // Game title
    title_text = new QLabel(tr("Snake"));
    title_text->setAlignment(Qt::AlignCenter);
    title_text->setStyleSheet(
        "font-size: 80px;"
        "color: black;"
        "font-family: 'New Century Schoolbook'");    
    layout->addWidget(title_text, 0, 0);

    // info msg about game area size. doesn't check if area is too small
    QLabel* info_msg =
        new QLabel(tr("Please input Width and Height values >=20"));
    info_msg->setAlignment(Qt::AlignHCenter);
    layout->addWidget(info_msg, 1, 0);

    // width input
    QLabel* text_width = new QLabel(tr("Width:"));
    text_width->setAlignment(Qt::AlignLeft);
    layout->addWidget(text_width, 2, 0);
    box_width = new QLineEdit();
    box_width->setStyleSheet(
        "background-color: white;"
        "max-width: 30px;"
        "color: black;"
        "margin-left: 200px;");
    box_width->setText(QString::number(GAME_SQUARES_X));
    box_width->setInputMask("99");
    box_width->setAlignment(Qt::AlignHCenter);
    layout->addWidget(box_width, 2, 0);

    // height input
    QLabel* text_height = new QLabel(tr("Height:"));
    text_height->setAlignment(Qt::AlignLeft);
    layout->addWidget(text_height, 3, 0);
    box_height = new QLineEdit();
    box_height->setStyleSheet(
        "background-color: white;"
        "max-width: 30px;"
        "color: black;"
        "margin-left: 200px;");
    box_height->setText(QString::number(GAME_SQUARES_Y));
    box_height->setInputMask("99");
    box_height->setAlignment(Qt::AlignHCenter);
    layout->addWidget(box_height, 3, 0);

    // seed input
    QLabel* text_seed = new QLabel(tr("Seed:"));
    text_seed->setAlignment(Qt::AlignLeft);
    layout->addWidget(text_seed, 4, 0);
    box_seed = new QLineEdit();
    box_seed->setStyleSheet(
        "background-color: white;"
        "max-width: 60px;"
        "color: black;"
        "margin-left: 200px;");
    box_seed->setText(QString::number(SEED_VALUE));
    box_seed->setInputMask("999999");
    box_seed->setAlignment(Qt::AlignHCenter);
    layout->addWidget(box_seed, 4, 0);

    // game speed in ms
    QLabel* text_gamespeed = new QLabel(tr("Game speed in ms:"));
    text_gamespeed->setAlignment(Qt::AlignLeft);
    layout->addWidget(text_gamespeed, 5, 0);
    box_gamespeed = new QLineEdit();
    box_gamespeed->setStyleSheet(
        "background-color: white;"
        "max-width: 80px;"
        "color: black;"
        "margin-left: 200px;");
    box_gamespeed->setText(DEFAULT_GAME_SPEED);
    box_gamespeed->setInputMask("9999");
    box_gamespeed->setAlignment(Qt::AlignHCenter);
    layout->addWidget(box_gamespeed, 5, 0);

    // gfx on/off
    QLabel* text_gfx = new QLabel(tr("GFX on/off:"));
    text_gfx->setAlignment(Qt::AlignLeft);
    layout->addWidget(text_gfx, 6, 0);
    box_gfx_toggle = new QCheckBox();
    box_gfx_toggle->setChecked(true);
    box_gfx_toggle->setStyleSheet(
        "margin-left: 200px;");
    layout->addWidget(box_gfx_toggle, 6, 0);


    // start new game button
    game_push_button = new QPushButton(tr("Start a new game"));
    game_push_button->setStyleSheet(
        "background-color: green;"
        "max-width: 400px;"
        "height: 100px;"
        "font-size: 40px;"
        "color: black;"
        "font-family: 'New Century Schoolbook'");    
    layout->addWidget(game_push_button, 7, 0);

    connect(game_push_button, &QPushButton::clicked,
            this, &Main_window::new_game_window);

    // reset game button. does the same as new game button..
    game_reset_button = new QPushButton(tr("Reset game"));
    game_reset_button->setStyleSheet(
        "background-color: yellow;"
        "max-width: 400px;"
        "height: 100px;"
        "font-size: 40px;"
        "color: black;"
        "font-family: 'New Century Schoolbook'");
    game_reset_button->setVisible(false);
    layout->addWidget(game_reset_button, 8, 0);

    connect(game_reset_button, &QPushButton::clicked,
            this, &Main_window::new_game_window);

    // close game button
    QPushButton* close_push_button = new QPushButton(tr("Close"));
    close_push_button->setStyleSheet(
        "background-color: red;"
        "max-width: 400px;"
        "height: 100px;"
        "color: black;"
        "font-size: 40px;"
        "font-family: 'New Century Schoolbook'");
    layout->addWidget(close_push_button, 9, 0);

    connect(close_push_button, &QPushButton::clicked,
            this, &Main_window::close);

    // create layout
    main_menu_grid->setLayout(layout);

}
