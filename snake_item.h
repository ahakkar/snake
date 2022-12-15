/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: snake_item.h
Description:

Class is used to draw and move snake tiles.
QGraphicsItem *parent   parent class
QString letter          letter to draw
bool graphics_mode      gfx on/off
QColor tile_color       drawn tile color

*/

#ifndef SNAKE_ITEM_H
#define SNAKE_ITEM_H

#include "constants.h"
#include "qgraphicsscene.h"
#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsWidget>

class Snake_item : public QGraphicsItem, public QGraphicsScene
{
public:
    // can use dynamic_cast to access this Square_item's properties later
    // in update_item_at_scene method in Game_board
    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    Snake_item(QGraphicsScene *parent,
               int y,
               int x,
               QString letter = "E",
               bool graphics_mode = false,
               QColor tile_color = DEFAULT_TILE_COLOR,
               qreal speed = 1);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    void set_properties(int y, int x, QString letter, QColor tile_color);

    void set_angle(qreal angle);

    qreal angle();

protected:
    // moves the item in screen
    void advance(int step) override;

private:
    QGraphicsScene *parent;
    int y;
    int x;
    qreal angle_ = DEFAULT_ANGLE;
    qreal speed;
    QColor tile_color_;
    QPixmap missing;

    QString letter_ = "E";
    bool graphics_mode_;
};

#endif // SNAKE_ITEM_H
