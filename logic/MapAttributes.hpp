#pragma once
#include <string>
#include "json.hpp"

class MapAttributes {

    using json = nlohmann::json;

public:

    static std::string resource_path() {
        return "../res/maps/";
    }

    static json prologue1() {
        json config;
        config["name"] = "Scarrex plateau near Cold-City, Deadball colony";
        config["file"] = "prologue1.txt";
        config["player_x"] = 58;
        config["player_y"] = 48;
        config["objects"] = {
            {
                { "display", " " },
                { "name", "You see nothing of interest here." },
                { "descr", "" },
                { "pathable", true },
                { "destructible", false },
                { "transparent", true },
                { "visibility", "default" }
            },
            {
                 { "display", "x" },
                 { "name", "Logus" },
                 { "descr", "A branchy tree covered with thorns, practically impassable. It doesn't combust and it's not edible; "
                            "can't be used as a building material or decoration. It all makes logus absolutely futile unless you "
                            "consider lethality a proper quality for a plant." },
                 { "pathable", false },
                 { "destructible", false },
                 { "transparent", false },
                 { "visibility", "discover_once" }
            },
            {
                 { "display", "*" },
                 { "name", "Redstone" },
                 { "descr", "A stone, ubiquitous for this planet. Typically it has a somewhat reddish colour to it, hence the name. "
                            "If you look closely, you'll see that it has a phallic shape which is good hint about the planet's general attitude towards colonists." },
                 { "pathable", false },
                 { "destructible", false },
                 { "transparent", false },
                 { "visibility", "discover_once" }
            }
        };
        config["enemies"] = {
            {
                { "x", 73},
                { "y", 39},
                { "name", "Farhgo" },
                { "display", "F" },
                { "descr", "Farhgos are vicious beasts dedicated to killing everything that moves. Small size and quick reflexes make them a perfect target practice." },
                { "stats", {
                    { "max_hp", 10 },
                    { "base_damage", 2 },
                    { "speed", 2 },
                    { "fov", 12 }
                }}
            },
            {
                { "x", 48},
                { "y", 25},
                { "name", "Farhgo" },
                { "display", "F" },
                { "descr", "Farhgos are vicious beasts dedicated to killing everything that moves. Small size and quick reflexes make them a perfect target practice." },
                { "stats", {
                    { "max_hp", 10 },
                    { "base_damage", 2 },
                    { "speed", 2 },
                    { "fov", 12 }
               }}
            }
        };
        return config;
    }

};


