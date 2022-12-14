/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: square_item.cpp
Description:

Class is used to draw the game tiles.
*/

#include "square_item.h"
#include <QDebug>

Square_item::Square_item(QGraphicsScene *parent, int y, int x, QString letter,
                         bool graphics_mode,
                         QColor tile_color) :
    //QGraphicsScene(parent),
    missing(QPixmap(QLatin1String(":/img/missing.png")))
{
    this->parent = parent;
    this->x = x;
    this->y = y;

    letter_ = letter;
    graphics_mode_ = graphics_mode;
    tile_color_ = tile_color;
}

QRectF Square_item::boundingRect() const
{    
    return QRectF(0, 0, GAME_SQUARE_WIDTH, GAME_SQUARE_HEIGHT);
}

void Square_item::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRect rect(0, 0, GAME_SQUARE_WIDTH, GAME_SQUARE_HEIGHT);

    // painter seems to overlay earlier painted items with new items..
    //painter->eraseRect(rect);

    if (letter_ == EMPTY) {
        return;
    }
    else {
        // paint a gfx tile if gfx are enabled
        if (graphics_mode_)
        {
            QPointF pos = QPoint(0, 0);
            QPixmap colorized(GAME_SQUARE_WIDTH, GAME_SQUARE_HEIGHT);
            QPixmap tile = QPixmap(QString::fromStdString(GFX_TILES.at(letter_)));

            auto iter = GFX_TILES.find(letter_);
            if (iter != GFX_TILES.end())
            {
                colorized.fill(tile_color_);
                colorized.setMask(tile.createMaskFromColor(Qt::transparent));
                painter->drawPixmap(pos, colorized);

            }
            // didn't find letter?
            else {
                painter->drawPixmap(pos, missing);
            }        
        }
        // otherwise just paint the provided letter
        else {
            painter->setPen(tile_color_);
            painter->drawText(rect, Qt::AlignCenter, letter_);
        }
    }
}

void Square_item::set_properties(int y, int x, QString letter, QColor tile_color)
{
    this->y = y;
    this->x = x;
    this->letter_ = letter;
    this->tile_color_ = tile_color;
}
