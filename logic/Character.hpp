#pragma once

#include "Point.hpp"
#include "GenericStats.hpp"

class Character {

public:
    Character(const Point& orig, const std::string& sym) : position(orig), skin(sym) {
    }

    const Point &get_position() const {
        return position;
    }

    const std::string& get_skin() const {
        return skin;
    }

    void set_position(const Point &position) {
        this->position = position;
    }

    void set_skin(char skin) {
        this->skin = skin;
    }

    const Point& up(int steps=1) {
        position.y -= steps;
        return position;
    }
    const Point& down(int steps=1) {
        position.y += steps;
        return position;
    }
    const Point& left(int steps=1) {
        position.x -= steps;
        return position;
    }
    const Point& right(int steps=1) {
        position.x += steps;
        return position;
    }
    const GenericStats& stats() {
        return effective_stats;
    }

protected:
    GenericStats effective_stats;
    Point position;
    std::string skin;
};


