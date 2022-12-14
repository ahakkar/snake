/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: square_item.h
Description:

Class is used to draw the game tiles.
QGraphicsItem *parent   parent class
QString letter          letter to draw
bool graphics_mode      gfx on/off
QColor tile_color       drawn tile color

*/

#ifndef SQUARE_ITEM_H
#define SQUARE_ITEM_H

#include "constants.h"
#include "qgraphicsscene.h"
#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsWidget>

class Square_item : public QGraphicsItem, public QGraphicsScene
{
public:
    // can use dynamic_cast to access this Square_item's properties later
    // in update_item_at_scene method in Game_board
    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    Square_item(QGraphicsScene *parent, int y, int x, QString letter = "E",
                bool graphics_mode = false,
                QColor tile_color = DEFAULT_TILE_COLOR);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    void set_properties(int y, int x, QString letter, QColor tile_color);

private:
    QGraphicsScene *parent;
    int y;
    int x;
    QColor tile_color_;
    QPixmap missing;

    QString letter_ = "E";
    bool graphics_mode_;
};

#endif // SQUARE_ITEM_H
