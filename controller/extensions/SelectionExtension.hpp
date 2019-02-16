#pragma once

#include "../Extension.hpp"
#include "../../display/Colors.hpp"

class SelectionExtension : public Extension {

private:
    Container* left_window;
    Container* main_window;
    Point sel_position;
    GameMap* game_map = nullptr;

public:
    explicit SelectionExtension(SignalBus *_bus) : Extension(_bus) {

    }

    void initialize() override {
        subscribe(Stage::intro, SignalType::window_created, [this](Signal *signal) {
            auto win_signal = dynamic_cast<WindowCreatedSignal *>(signal);
            if (win_signal->get_code() == "left") {
                left_window = win_signal->get_window();
            } else if (win_signal->get_code() == "main") {
                main_window = win_signal->get_window();
            }
        });

        subscribe(SignalType::game_map_reload, [this] (Signal* signal) {
            game_map = dynamic_cast<GameMapReloadSignal*>(signal)->get_game_map();
            sel_position = game_map->get_pointer_position();
        });

        subscribe({Stage::main_game, Stage::main_game_selection}, SignalType::key_down, [this] (Signal* signal) {
            int key = dynamic_cast<KeyDownSignal*>(signal)->get_key();
            if (key == ';' || key == ':') {
                auto new_stage = get_stage() == Stage::main_game ? Stage::main_game_selection : Stage::main_game;
                send_signal(new StageChangeSignal(new_stage));
                sel_position = game_map->get_pointer_position();
            } else if (get_stage() == Stage::main_game_selection) {
                switch (key) {
                    case KEY_UP:
                        sel_position.y -= 1;
                        break;
                    case KEY_DOWN:
                        sel_position.y += 1;
                        break;
                    case KEY_LEFT:
                        sel_position.x -= 1;
                        break;
                    case KEY_RIGHT:
                        sel_position.x += 1;
                        break;
                    default:
                        break;
                }
            }
        });

        subscribe(Stage::main_game_selection, SignalType::render_prepare, [this] (Signal* signal) {
            if (sel_position == game_map->get_pointer_position()) {
                left_window->print_at({ 1, 1 }, "That's you.");
                Colors::color_on(main_window->raw(), Colors::YELLOW_BLACK);
                main_window->print_at(main_window->get_center(), "@");
                Colors::color_off(main_window->raw());
            } else {
                auto obj = game_map->object_at(sel_position);
                std::string skin = obj.skin == ' ' ? "+" : std::string(1, obj.skin);
                Colors::color_on(main_window->raw(), Colors::YELLOW_BLACK);
                main_window->print_at(main_window->get_center() + sel_position - game_map->get_pointer_position(), skin);
                Colors::color_off(main_window->raw());
                left_window->titled_text_at("[" + obj.name + "]", obj.description);
            }
        });
    }
};
