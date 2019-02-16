#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "json.hpp"
#include "MapAttributes.hpp"
#include "Point.hpp"
#include "MapObject.hpp"

/**
 * Parses the given json map config and stores information about loaded map. The game level itself is represented via 2d char array.
 * The map position relative to user viewport IS NOT controlled here - see {@link MapExtension}. To help moving the map around this class
 * stores the 'cursor position', though, which is basically a center of game window most of the time and is also the position of the player.
 **/
class GameMap {

    using json = nlohmann::json;

public:
    explicit GameMap(json map_config) {
        name = map_config["name"];
        std::string filename = map_config["file"];
        pointer_position.x = map_config["player_x"];
        pointer_position.y = map_config["player_y"];
        for (const auto& obj_data : map_config["objects"]) {
            MapObject object(obj_data);
            objects_table.insert({object.skin, object});
        }
        read_file(MapAttributes::resource_path() + filename);
    }

    const std::vector<std::string>& get_map() {
        return level_map;
    }

    const std::string& get_title() {
        return name;
    }

    const Point& get_pointer_position() const {
        return pointer_position;
    }

    void update_pointer_position(const Point& p) {
        pointer_position = p;
    }

    bool is_pathable(const Point& p) {
        if (p.y >= level_map.size() || std::min(p.x, p.y) < 0) {
            return false;
        }
        std::string row = level_map[p.y];
        if (p.x >= row.size()) {
            return false;
        }
        char key = row[p.x];
        return objects_table.at(key).pathable;

    }

    const MapObject& object_at(const Point& p) {
        return objects_table.at(level_map[p.y][p.x]);
    }

    const Point& get_dimensions() {
        return dimensions;
    }

private:

    std::string name;
    std::vector<std::string> level_map;
    Point pointer_position = {0, 0}; //x,y of the currently moving entity: player, selection cursor, etc
    std::map<char, MapObject> objects_table;
    Point dimensions;

    void read_file(const std::string& file_n_path) {
        std::fstream file(file_n_path, std::ios::in);
        if (!file.is_open()) {
            level_map.push_back("failed to load map with path " + file_n_path);
            return;
        }
        std::string line;
        level_map.clear();
        int current_max_width = 0;
        while (std::getline(file, line)) {
            level_map.push_back(line);
            current_max_width = std::max(current_max_width, (int) line.size());
        }
        file.close();
        dimensions = { current_max_width, (int) level_map.size() };
    }
};

