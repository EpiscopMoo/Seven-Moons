#pragma once
#include <string>
#include <vector>
#include "json.hpp"

enum class Visibility {
    DEFAULT,
    DISCOVER_ONCE,
    ALWAYS,
    HIDDEN
};

struct MapObject {

    using json = nlohmann::json;

    char skin;
    std::string name;
    std::string description;
    bool pathable;
    bool destructible;
    bool transparent;
    Visibility visibility;

    MapObject(json data) {
        std::string display = data["display"];
        skin = display[0];
        name = data["name"];
        description = data["descr"];
        pathable = data["pathable"];
        destructible = data["destructible"];
        transparent = data["transparent"];
        std::string vis = data["visibility"];
        visibility = vis == "default" ? Visibility::DEFAULT :
                     vis == "discover_once" ? Visibility::DISCOVER_ONCE :
                     vis == "always" ? Visibility::ALWAYS :
                     Visibility::HIDDEN;
    }

};


