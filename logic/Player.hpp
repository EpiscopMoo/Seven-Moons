#pragma once
#include <string>

#include "Character.hpp"

class Player;
using P_Player = std::shared_ptr<Player>;

class Player : public Character {

public:
    Player(Point orig, char sym) : Character(orig, sym) {
        base_stats.set_space_and_update(8, 5, 8, 6, 1, 14);
        name = "Neal Porgo";
        description = "That's you.";
    }
    const PlayerStats& get_base_stats() const {
        return base_stats;
    }

private:
    PlayerStats base_stats;
    GenericStats additional_stats;
};


