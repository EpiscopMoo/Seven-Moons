#pragma once

#include <set>
#include <vector>
#include <queue>
#include "GameMap.hpp"

class PathCalculator {

public:
    PathCalculator() : game_map(nullptr) {}

    explicit PathCalculator(GameMap *_game_map) : game_map(_game_map) {}

    void set_game_map(GameMap* _game_map) {
        game_map = _game_map;
    }

    std::vector<Point> plot_path(const Point &start, const Point &goal) {
        std::set<Point> closed;

        auto comparator = [=](std::vector<Point> v1, std::vector<Point> v2) -> bool {
            auto a = v1.back();
            auto b = v2.back();
            float adist = (a.x - goal.x)*(a.x - goal.x) + (a.y - goal.y)*(a.y - goal.y);
            float bdist = (b.x - goal.x)*(b.x - goal.x) + (b.y - goal.y)*(b.y - goal.y);
            return adist > bdist;
        };

        std::priority_queue<std::vector<Point>, std::vector<std::vector<Point>>, decltype(comparator)> open(comparator);
        std::vector<Point> initPath = { start };
        open.push(initPath);

        while (!open.empty())
        {
            auto p = open.top();
            open.pop();
            auto x = p.back();
            if (closed.count(x))
            {
                continue;
            }
            if (x == goal)
            {
                return p;
            }
            closed.insert(x);

            for (auto y : succ(x))
            {
                auto pcopy = p;
                pcopy.push_back(y);
                open.push(pcopy);
            }
        }
        return std::vector<Point>();
    }
private:
    GameMap* game_map;

    std::vector<Point> succ(const Point& p) {
        int x = p.x;
        int y = p.y;
        std::vector<Point> neighs;
        std::vector<Point> result;
        neighs.push_back({x + 1, y});
        neighs.push_back({x, y + 1});
        neighs.push_back({x - 1, y});
        neighs.push_back({x, y - 1});
        for (auto& neigh : neighs) {
            if (game_map->is_valid(neigh)) {
                auto& game_object = game_map->object_at(neigh);
                auto character = game_map->character_at(neigh);
                bool pathable = game_object.pathable;
                bool obstructed = character != nullptr;
                if (pathable and not obstructed) {
                    result.push_back(neigh);
                }
            }
        }
        return result;
    }
};
