/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: game_board.h
Description:

Class is used to run the game logic.

QMainWindow* parent     main menu
int width               game area witdh in tiles
int height              game are height in tiles
int seed_value          seed
int game_speed          game speed in ms
*/

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <random>
#include <string>
#include <deque>

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>

#include "point.h"
#include "constants.h"
#include "snake_item.h"
#include "block_item.h"

QT_BEGIN_NAMESPACE
class QWidget;
class QDebug;
class QLabel;
QT_END_NAMESPACE

class Game_board : public QMainWindow
{
    Q_OBJECT

public:
    // Default constructor.
    Game_board(QMainWindow* parent,
               int width,
               int height,
               int seed_value,
               int game_speed,
               bool gfx_toggle);

    ~Game_board();

public slots:
    void start_timer();

private slots:
    void stop_timer();

    // decides how snake is drawn to screen
    void snake_handler();
    void anim_snake_handler();

signals:
    // communicate pause, game won/lost to Main_window
    void pauseGame();
    void game_won_signal();
    void game_lost_signal();

private:
    // parent & renderer classes
    QMainWindow* parent;

    // tile or text mode graphics
    bool graphics_mode_;

    // render game tiles to these
    QGraphicsScene* scene;
    QGraphicsView* view;

    int game_speed;

    // game timer
    QTimer* timer_;
    // animation timer
    QTimer* anim_timer;

    // direction snake is going. default is right (d)
    char dir_ = 'd';
    bool dir_changed = false;

    // Generates random numbers used to move the food item to random locations.
    std::default_random_engine rng_;

    // Points currently occupied by the snake, head being the last one.
    std::deque<Point> snake_;

    // List of graphical snake objects, so we can access them later
    QList<Snake_item*> gfx_snake_items;

    Block_item *gfx_food_item = nullptr;

    // The food item"s position in the gameboard.
    Point food_;

    // previous tail's and head's point;
    Point prev_tail_;

    bool is_game_paused = false;

    // Tells if the snake is alive and able to move.
    bool dead_ = false;

    // Specifies the width and height of the gameboard.
    int width_ = DEFAULT_WIDTH;
    int height_ = DEFAULT_HEIGHT;

    void keyPressEvent(QKeyEvent* event) override;

    //void start_music();

    // create empty game board with walls
    void populate_scene();

    // add a new item to scene (wall or empty)
    void add_block_item_to_scene(int y, int x, QString letter,
                           QColor tile_color = QColor(0,0,0));

    // add a new snake item to scene (wall or empty)
    void add_snake_item_to_scene(int y,
                                 int x,
                                 QString letter,
                                 bool graphics_mode,
                                 QColor tile_color = DEFAULT_TILE_COLOR,
                                 qreal snake_speed = 1);

    // update graphicsscene at specified position, like when drawing
    // food or snake parts
    void update_item_at_scene(int y, int x, QString letter,
                              QColor tile_color = QColor(0,0,0));

    void update_snake_item(
        int position,
        QString letter,
        QColor tile_color = QColor(0,0,0),
        qreal angle = DEFAULT_ANGLE);

    void new_food();

    // Checks if the game is over.
    // Returns false until the game has been either lost or won.
    bool game_over() const;

    // Checks if the game has been lost.
    // Returns true if the snake is dead.
    bool game_lost() const;

    // Checks if the game has been won.
    // Returns true if the snake has filled the field.
    bool game_won() const;

    // Returns true if the given point is a part of the snake.
    bool is_snake_point(const Point& point) const;

    // Returns the point of the snake"s head.
    const Point& head() const;

    // Returns the point of the snake"s tail.
    const Point& tail() const;

    // Moves the snake to the given direction, if possible.
    // Moving is not possible, if game is over, or if the snake would move
    // against a wall.
    // If moving is possible, calls the private method moveSnakeAndFood.
    // Returns true, if moving was possible.
    bool move_snake(const char& direction);

    // Relocates food to a random, snakeless location.
    // Hides the food if the snake has completely filled the gameboard.
    void move_food();

    // Moves the snake unless the new head would be the body of the snake.
    // If the new head is the neck of the snake, nothing happens.
    // If the new head is other body part of the snake, the snake dies.
    // Otherwise the snake moves, whereupon the method returns true.
    // If, in addition, the food got eaten a new one is placed somewhere,
    // and the snake grows a bit.
    bool move_snake_and_food(const Point& new_head);

};

#endif // GAME_BOARD_H
