#pragma once

struct Point {
    int x, y;
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
    bool operator!=(const Point& p) const {
        return !(*this == p);
    }
    bool operator<(const Point& p) const {
        if (x < p.x) {
            return true;
        } else if (x > p.x) {
            return false;
        } else {
            return y < p.y;
        }
    }
    Point operator+(const Point& p) const {
        return {x + p.x, y + p.y};
    }
    Point operator-(const Point& p) const {
        return {x - p.x, y - p.y};
    }
    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
};


