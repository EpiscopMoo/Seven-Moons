#pragma once

#include "../Extension.hpp"
#include "../../logic/PathCalculator.hpp"

class EnemiesExtension : public Extension {

private:
    P_Player player = nullptr;
    GameMap* game_map = nullptr;
    PathCalculator paths;

public:
    explicit EnemiesExtension(SignalBus *_bus) : Extension(_bus) {

    }

    void initialize() override {
        subscribe(SignalType::game_map_reload, [this] (Signal* signal) {
            game_map = dynamic_cast<GameMapReloadSignal*>(signal)->get_game_map();
            player = game_map->get_player();
            paths.set_game_map(game_map);
        });

        subscribe(SignalType::enemy_sequence, [this] (Signal* signal) {
            if (player != nullptr and game_map != nullptr) {
                for (auto& enemy : game_map->get_enemies()) {
                    if (VisibilityCalculator::is_visible(enemy->get_position(),
                            player->get_position(),
                            enemy->stats().fov)) {
                        auto path = paths.plot_path(enemy->get_position(), player->get_position());
                        if (path.size() > 1) {
                            enemy->set_position(path[1]);
                        }
                    }
                    if (VisibilityCalculator::is_visible(player->get_position(),
                                                         enemy->get_position(),
                                                         player->get_base_stats().fov)) {
                        send_signal(new CharacterRenderSignal(enemy));
                    }
                }
            }
        });
    }
};