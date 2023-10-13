//
// Created by Rocky Chen on 2023/10/2.
//

#pragma once

class Point {
public:
    Point():x(0), y(0){};

    Point(double x, double y): x(x), y(y){};

    Point operator+(const Point &rhs) const {
        return {rhs.x + this->x, rhs.y + this->y};
    }

    Point operator-(const Point &rhs) const {
        return {this->x - rhs.x , this->y - rhs.y};
    }

    Point operator*(const double rhs) const{
        return {this->x * rhs, this->y * rhs};
    }

    Point operator/(const double rhs) const{
        return {this->x / rhs, this->y / rhs};
    }

private:
    double x, y;


};

