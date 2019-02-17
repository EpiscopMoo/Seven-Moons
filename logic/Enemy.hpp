#pragma once

#include "Character.hpp"
#include "json.hpp"

class Enemy;
using P_Enemy = std::shared_ptr<Enemy>;

class Enemy : public Character {

    using json = nlohmann::json;

public:
    Enemy(const Point& orig, char sym) : Character(orig, sym) {
    }

    Enemy(const json& character_config) : Character(Point(), ' ') {
        std::string name = character_config["name"];
        std::string descr = character_config["descr"];
        std::string skin = character_config["display"];
        int x = character_config["x"];
        int y = character_config["y"];
        const auto &stats_config = character_config["stats"];
        GenericStats stats = GenericStats::from_json(stats_config);

        set_position({x, y});
        set_name(name);
        set_description(descr);
        set_skin(skin[0]);
        set_stats(stats);
    }
};