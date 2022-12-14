/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: game_board.cpp
Description:

Class is used to run the game logic and render snake to screen.

Methods regarding internal snake and food creation and movement were provided
by the course. I implemented only the input and drawing methods.
*/

#include "game_board.h"
#include "square_item.h"

Game_board::Game_board(QMainWindow *parent,
                       int width,
                       int height,
                       int seed_value,
                       int game_speed,
                       bool graphics_mode):
    QMainWindow(parent, Qt::Window)
{
    graphics_mode_ = graphics_mode;
    width_ = width;
    height_ = height;
    rng_.seed(seed_value);


    // Create a new scene so we can render graphics to it
    scene = new QGraphicsScene(this);
    this->populate_scene();

    // Add scene to view, so we can see the scene
    view = new QGraphicsView(scene);
    view->setInteractive(false);
    view->setAlignment(Qt::AlignTop);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setCentralWidget(view);

    // create snake    
    const Point head((width_ - 1) / 2, (height_ - 1) / 2);
    snake_.push_back(head);

    // put food somewhere
    move_food();

    // start the game timer
    timer_ = new QTimer(this);
    timer_->start(game_speed);
    connect(timer_, &QTimer::timeout,
            this, &Game_board::snake_handler);

    // hide the main menu when game starts
    parentWidget()->hide();

    // connect pause signal to method
    connect(this, &Game_board::pauseGame, this, &Game_board::stop_timer);
}

Game_board::~Game_board()
{

}

void Game_board::stop_timer()
{
    timer_->stop();
    parentWidget()->show();
}

void Game_board::start_timer()
{
    timer_->start();
    parentWidget()->hide();
}


void Game_board::snake_handler() {
    //qInfo() << scene->items().size();
    // handle death
    if (dead_) {
        timer_->stop();
        emit game_lost_signal();
        parentWidget()->show();
        this->close();
        return;
    }

    // clear board after tail
    if (prev_tail_.pos_x() != 0 && prev_tail_.pos_y() != 0) {
        this->update_item_at_scene(prev_tail_.pos_y(),
                          prev_tail_.pos_x(),
                          EMPTY
                          );
    }

    // render snake
    for (int i = 0; i < (int)snake_.size(); i++) {
        QString bodypart;
        if (i == 0 and (int)snake_.size() > 1) {
            bodypart = TAIL;
        }
        else if (i == (int)snake_.size()-1) {
            bodypart = HEAD;
        }
        else {
            bodypart = BODY;
        }

        this->update_item_at_scene(snake_.at(i).pos_y(),
                          snake_.at(i).pos_x(),
                          bodypart,
                          snake_colors.at(i%11)
                         );
    }

    prev_tail_ = tail();

    move_snake(dir_);
    dir_changed = false;
}

void Game_board::keyPressEvent(QKeyEvent* event) {
    switch (event->key())
    {
    // show game menu
    case Qt::Key_Escape: {        
        emit pauseGame(); // emit signal so game can be paused
        break;
    }
    case Qt::Key_W: {
        if (dir_ == DOWN or dir_changed) { break; } // to avoid suicides
        dir_ = UP;
        dir_changed = true; // to avoid snake getting stuck in itself
        break;
    }
    case Qt::Key_S: {
        if (dir_ == UP or dir_changed) { break; }
        dir_ = DOWN;
        dir_changed = true;
        break;
    }
    case Qt::Key_A: {
        if (dir_ == RIGHT or dir_changed) { break; }
        dir_ = LEFT;
        dir_changed = true;
        break;
    }
    case Qt::Key_D: {
        if (dir_ == LEFT or dir_changed) { break; }
        dir_ = RIGHT;
        dir_changed = true;
        break;
    }
    default: { break; }
    }
}

void Game_board::populate_scene()
{
    // draw walls around the game area
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            QString letter = EMPTY;

            if (x == 0 and y == height_-1) {
                letter = CORNER_SW;
            }
            else if (x == 0 and y == 0) {
                letter = CORNER_NW;
            }
            else if (x == width_-1 and y == height_-1) {
                letter = CORNER_SE;
            }
            else if (x == width_-1 and y == 0) {
                letter = CORNER_NE;
            }
            else if ((x > 0 and x < width_-1 and y == 0) or
                     (x > 0 and x < width_-1 and y == height_-1))
            {
                letter = HOR_WALL;
            }
            else if (x == 0 or x == width_-1) {
                letter = VER_WALL;
            }

            this->add_item_to_scene(y, x, letter, DEFAULT_TILE_COLOR);

        }
    }
}

void Game_board::add_item_to_scene(int y, int x,
                                   QString letter,
                                   QColor tile_color)
{
    Square_item *item = new Square_item(scene,
                                        y*GAME_SQUARE_HEIGHT,
                                        x*GAME_SQUARE_WIDTH,
                                        letter,
                                        graphics_mode_,
                                        tile_color);

    item->setPos(QPointF(x*GAME_SQUARE_WIDTH, y*GAME_SQUARE_HEIGHT));
    scene->addItem(item);
}

void Game_board::update_item_at_scene(int y, int x,
                                      QString letter,
                                      QColor tile_color)
{
    // look for an item at point
    auto *item = scene->itemAt(QPointF(x*GAME_SQUARE_WIDTH,
                                       y*GAME_SQUARE_HEIGHT),
                                       QTransform());

    // change item's properties and redraw item's portion of the scene
    if (item != nullptr) {
        Square_item *as_item = dynamic_cast<Square_item*>(item);
        as_item->set_properties(y, x, letter, tile_color);
        scene->update(x*GAME_SQUARE_WIDTH,
                      y*GAME_SQUARE_HEIGHT,
                      GAME_SQUARE_WIDTH,
                      GAME_SQUARE_HEIGHT);
        return;
    }
    qInfo() << "itemAt returned nullptr! :-(";
}

void Game_board::new_food() {
    move_food();
    this->update_item_at_scene(food_.pos_y(), food_.pos_x(), FOOD);
}

bool Game_board::game_over() const
{
    return game_lost() or game_won();
}

bool Game_board::game_lost() const
{    
    return dead_;
}

bool Game_board::game_won() const
{
    return static_cast<int>(snake_.size()) >= width_ + height_;
}

bool Game_board::move_snake(const char& direction)
{
    // If the snake can't / doesn't need to move, do nothing
    if (game_over()) {
        if (game_won()) {
            emit game_won_signal();
            parentWidget()->show();
            this->close();
        }
        return false;
    }

    // Figuring out the destination coordinates
    Point new_head = head();
    new_head.move(direction);

    // Checking if the snake died due to running against a wall
    if(not new_head.isInside(1, 1, width_ - 2, height_ - 2))
    {
        dead_ = true;
        if (game_lost()) {
            emit game_lost_signal();
            parentWidget()->show();
            this->close();
        }
        return false;
    }

    // Actually moving the snake
    return move_snake_and_food(new_head);
}

void Game_board::move_food()
{
    // Moving food out of sight when it's no longer needed
    if (game_won()) {
        food_.setPosition(-1, -1);
        return;
    }

    // Keeping to try random points until an empty square is found
    std::uniform_int_distribution<int> width_dist(1, width_ - 2);
    std::uniform_int_distribution<int> height_dist(1, height_ - 2);
    width_dist(rng_);
    height_dist(rng_);

    while (true) {
        food_.setPosition(width_dist(rng_), height_dist(rng_));
        if (not is_snake_point(food_)) {
            // Snakeless point found, stop moving the food around and render it
            update_item_at_scene(food_.pos_y(), food_.pos_x(),
                        FOOD, DEFAULT_TILE_COLOR);
            return;
        }
    }
}

bool Game_board::move_snake_and_food(const Point& new_head)
{
    // There shouldn't be any problems if the snake is only a head or
    // if it doesn't yet occupy the point it's moving into.
    if (snake_.size() > 1 and is_snake_point(new_head))
    {
        const Point& neck = snake_.at(snake_.size() - 2);
        if (new_head == neck)
        {
            // If the destination point is the point before the head,
            // don't move but don't die either
            return false;

        }
        else if (new_head != tail())
        {
            // If the destination point is the snake's body point, other than
            // "neck" or tail, the snake dies
            dead_ = true;
            return false;
        }
    }

    // Moving the snake
    snake_.push_back(new_head);    

    // New food must be placed somewhere once one gets eaten.
    // Also, the snake should stretch a little.
    if (new_head == food_) {
        move_food();
    }
    // Otherwise the point is of the old tail becomes empty.
    else {
        snake_.pop_front();
    }
    return true;
}

bool Game_board::is_snake_point(const Point& point) const
{
    // Checking if any of the Points stored in snake_ match the given point
    for(const Point& part : snake_) {
        if (part == point) { return true; }
    }
    return false;
}

const Point& Game_board::head() const
{
    // This should never happen: snake_ contains at least one element (head)
    if(snake_.size() == 0)
    {
        qInfo() << "Internal error: empty snake";
    }
    // The snake's head is the last one in the deque
    return snake_.back();
}

const Point& Game_board::tail() const
{
    // This should never happen: snake_ contains at least one element (head)
    if(snake_.size() == 0)
    {
        qInfo() << "Internal error: empty snake";
    }
    // The snake's tail is the first one in the deque
    return snake_.front();
}
