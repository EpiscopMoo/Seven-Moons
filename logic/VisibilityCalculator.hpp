#pragma once

#include <set>
#include <vector>
#include "Point.hpp"
#include "GameMap.hpp"
#include "Player.hpp"

class VisibilityCalculator {

public:
    explicit VisibilityCalculator(GameMap* _game_map) : game_map(_game_map) {
        auto dim = game_map->get_dimensions();
        for (auto i = 0; i < dim.y; i++) {
            int dim_x = game_map->get_map()[i].size();
            for (int j = 0; j < dim_x; j++) {
                auto& object = game_map->object_at({j, i});
                if (object.visibility == Visibility::ALWAYS) {
                    discovered.insert({j, i});
                }
            }
        }
    }

    std::vector<std::string> get_visible_map(const Player& player) {
        const auto& levelmap = game_map->get_map();
        auto player_position = player.get_position();
        if (is_player_coord_correct(player_position, levelmap)) {
            auto map_size = game_map->get_dimensions();
            std::vector<std::string> visible_map(map_size.y, empty_row(map_size.x));
            int fov = player.get_base_stats().fov;
            for (int i = -fov; i <= fov; i++) {
                int vis_width = fov - abs(i);
                for (int j = -vis_width; j <= vis_width; j++) {
                    int vis_x = player_position.x + i;
                    int vis_y = player_position.y + j;
                    Point visible_point = { vis_x, vis_y };
                    make_visible(visible_point, visible_map);
                }
            }
            for (auto obj_pt : discovered) {
                visible_map[obj_pt.y][obj_pt.x] = game_map->object_at(obj_pt).skin;
            }
            return visible_map;
        }
        return std::vector<std::string>();
    }

    static bool is_visible(const Point& observer, const Point& target, int fov) {
        int diff_x = abs(observer.x - target.x);
        int diff_y = abs(observer.y - target.y);
        return diff_x + diff_y <= fov;
    }
private:
    std::set<Point> discovered;
    GameMap* game_map;

    bool is_player_coord_correct(const Point& player_position, const std::vector<std::string>& levelmap) {
        if (player_position.y < 0 or player_position.y >= levelmap.size()) {
            return false;
        }
        auto player_row = levelmap[player_position.y];
        if (player_position.x < 0 or player_position.x >= player_row.size()) {
            return false;
        }
        return true;
    }

    std::string empty_row(int len) {
        std::string row = "";
        for (int i = 0; i< len; i++) {
            row += " ";
        }
        return row;
    }

    void make_visible(const Point& visible_point, std::vector<std::string>& visible_map) {
        const auto& real_map = game_map->get_map();
        if (visible_point.y < 0 or visible_point.y >= real_map.size()) {
            return;
        }
        auto& row = real_map[visible_point.y];
        if (visible_point.x < 0 or visible_point.x >= row.size()) {
            return;
        }
        auto& object = game_map->object_at(visible_point);
        char skin = object.skin == ' ' ? '.' : object.skin;
        int x = visible_point.x;
        int y = visible_point.y;
        switch (object.visibility) {
            case Visibility::DISCOVER_ONCE:
                discovered.insert(visible_point);
            case Visibility::ALWAYS:
            case Visibility::DEFAULT:
                visible_map[y][x] = skin;
                break;
            case Visibility::HIDDEN:
            default:
                visible_map[y][x] = '.';
                break;
        }
    }
};
