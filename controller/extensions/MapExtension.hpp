#pragma once
#include <vector>
#include <string>
#include <set>

#include "../Extension.hpp"
#include "../../display/CWindow.hpp"
#include "../signals/SimpleSignals.hpp"
#include "../../logic/GameMap.hpp"
#include "../../logic/Character.hpp"
#include "../../logic/VisibilityCalculator.hpp"

class MapExtension : public Extension {

private:
    GameMap map;
    VisibilityCalculator visibility;
    Container* main_window = nullptr;
    Player* player = nullptr;
    std::set<Character*> characters;

    Point compute_position() {
        return main_window->get_center() - map.get_pointer_position();
    }

public:
    explicit MapExtension(SignalBus *_bus) : Extension(_bus), map(MapAttributes::prologue1()), visibility(&map) { }

    void initialize() override {
        subscribe(Stage::intro, SignalType::window_created, [this] (Signal* signal) {
            auto win_signal = dynamic_cast<WindowCreatedSignal*>(signal);
            if (win_signal->get_code() == "main") {
                main_window = win_signal->get_window();
                main_window->set_title(map.get_title());
                main_window->set_hint("[;] - look mode, [arrows] - move");
                send_signal(new GameMapReloadSignal(&map));
            }
        });

        subscribe({Stage::main_game, Stage::main_game_selection}, SignalType::character_render, [this] (Signal* signal) {
            characters.insert(dynamic_cast<CharacterRenderSignal*>(signal)->get_character());
        });

        subscribe({Stage::main_game, Stage::main_game_selection}, SignalType::render_prepare, [this] (Signal* signal) {
            if (main_window) {
                main_window->content_at(compute_position(), visibility.get_visible_map(*player));
                for (auto character : characters) {
                    auto position = character->get_position() + compute_position();
                    auto skin = character->get_skin();
                    main_window->print_at(position, skin);
                }
                characters.clear();
            }
        });

        subscribe(SignalType::player_created, [this] (Signal* signal) {
            auto player_signal = dynamic_cast<PlayerCreatedSignal*>(signal);
            player = player_signal->get_player();
        });
    }
};


