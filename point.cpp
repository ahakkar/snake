/*
COMP.CS.110 Programming 2: Autumn 2022
Project4: Snake
Antti Hakkarainen K79735 antti.i.hakkarainen@tuni.fi
File: point.cpp
Description:

Class is used to store the location of snake parts. Class provided by school.
*/

#include "point.h"
#include "constants.h"

#include <QDebug>

Point::Point() : x_(0), y_(0) { }

Point::Point(int x, int y) : x_(x), y_(y) { }

Point::~Point() { }

bool Point::operator==(const Point &rhs) const {
    return x_ == rhs.x_ and y_ == rhs.y_;
}

bool Point::operator!=(const Point &rhs) const {
    return x_ != rhs.x_ or y_ != rhs.y_;
}

int Point::pos_x() {
    return x_;
}

int Point::pos_y() {
    return y_;
}

void Point::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Point::move(const char &dir) {
    switch(dir)
    {
        case UP: --y_; break;
        case LEFT: --x_; break;
        case DOWN: ++y_; break;
        case RIGHT: ++x_; break;
        default: qInfo() << "Internal error: impossible direction";
    }
}

bool Point::isInside(int left_top_x, int left_top_y,
                     int right_bottom_x, int right_bottom_y) const
{
    return (x_ >= left_top_x) and (y_ >= left_top_y) and
           (x_ <= right_bottom_x) and (y_ <= right_bottom_y);
}
