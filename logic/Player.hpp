#pragma once
#include <string>

#include "Character.hpp"

class Player : public Character {

public:
    Player() : Character({ 0, 0 }, "@") {
        base_stats.set_space_and_update(8, 5, 8, 6, 1, 14);
    }
    Player(Point orig, const std::string& sym) : Character(orig, sym) {
        base_stats.set_space_and_update(8, 5, 8, 6, 1, 14);
    }
    const PlayerStats& get_base_stats() const {
        return base_stats;
    }

private:
    PlayerStats base_stats;
    GenericStats additional_stats;
};


