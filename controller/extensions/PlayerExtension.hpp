#pragma once

#include "../Extension.hpp"
#include "../../logic/Player.hpp"
#include "../../logic/GameMap.hpp"

class PlayerExtension : public Extension {

private:
    P_Player player = nullptr;
    GameMap* game_map = nullptr;
    CWindow* stats_window = nullptr;

public:
    explicit PlayerExtension(SignalBus *_bus) : Extension(_bus) {

    }

    void initialize() override {
        subscribe(SignalType::game_map_reload, [this] (Signal* signal) {
            game_map = dynamic_cast<GameMapReloadSignal*>(signal)->get_game_map();
            player = game_map->get_player();
        });

        subscribe(Stage::intro, SignalType::window_created, [this] (Signal* signal) {
            auto win_signal = dynamic_cast<WindowCreatedSignal*>(signal);
            if (win_signal->get_code() == "middle") {
                stats_window = dynamic_cast<CWindow*>(win_signal->get_window());
            }
        });

        subscribe(Stage::main_game, SignalType::key_down, [this] (Signal* signal) {
            int key = dynamic_cast<KeyDownSignal*>(signal)->get_key();
            switch (key) {
                case 'q':
                    send_signal(new GameEndSignal());
                    break;

                case 'k':
                case KEY_UP:
                    if (game_map->is_pathable(player->get_position() + Point({0, -1}))) {
                        player->up();
                    }
                    break;

                case 'j':
                case KEY_DOWN:
                    if (game_map->is_pathable(player->get_position() + Point({0, 1}))) {
                        player->down();
                    }
                    break;

                case 'h':
                case KEY_LEFT:
                    if (game_map->is_pathable(player->get_position() + Point({-1, 0}))) {
                        player->left();
                    }
                    break;

                case 'l':
                case KEY_RIGHT:
                    if (game_map->is_pathable(player->get_position() + Point({1, 0}))) {
                        player->right();
                    }
                    break;

                default:
                    break;
            }
            game_map->update_pointer_position(player->get_position());
        });

        subscribe({Stage::main_game, Stage::main_game_selection}, SignalType::player_sequence, [this] (Signal*) {
            send_signal(new CharacterRenderSignal(player));
            stats_window->content_at({1,1}, player->get_base_stats().to_strings());
        });
    }
};


