#pragma once

#include "Point.hpp"
#include "GenericStats.hpp"

class Character {

public:
    Character(const Point& orig, char sym) : position(orig), skin(sym) {
    }

    const Point &get_position() const {
        return position;
    }

    char get_skin() const {
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
    const std::string& get_description() {
        return description;
    }
    const std::string& get_name() {
        return name;
    }
    void set_name(const std::string& _name) {
        name = _name;
    }
    void set_description(const std::string& _descr) {
        description = _descr;
    }
    void set_stats(const GenericStats& _stats) {
        effective_stats = _stats;
    }

protected:
    std::string name;
    std::string description;
    GenericStats effective_stats;
    Point position;
    char skin;
};


