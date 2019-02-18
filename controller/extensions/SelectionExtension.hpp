#pragma once

#include "../Extension.hpp"
#include "../../display/Colors.hpp"

class SelectionExtension : public Extension {

private:
    Container* main_window;
    Container* left_window;
    Container* right_window;
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
            } else if (win_signal->get_code() == "right") {
                right_window = win_signal->get_window();
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

                auto orig = game_map->get_player()->get_position();
                int fov = game_map->get_player()->get_base_stats().fov;
                Point dest;
                switch (key) {
                    case 'k':
                    case KEY_UP:
                        dest = sel_position - Point({0, 1});
                        if (VisibilityCalculator::is_visible(orig, dest, fov) and game_map->is_valid(dest)) {
                            sel_position.y -= 1;
                        }
                        break;
                    case 'j':
                    case KEY_DOWN:
                        dest = sel_position + Point({0, 1});
                        if (VisibilityCalculator::is_visible(orig, dest, fov) and game_map->is_valid(dest)) {
                            sel_position.y += 1;
                        }
                        break;
                    case 'h':
                    case KEY_LEFT:
                        dest = sel_position - Point({1, 0});
                        if (VisibilityCalculator::is_visible(orig, dest, fov) and game_map->is_valid(dest)) {
                            sel_position.x -= 1;
                        }
                        break;
                    case 'l':
                    case KEY_RIGHT:
                        dest = sel_position + Point({1, 0});
                        if (VisibilityCalculator::is_visible(orig, dest, fov) and game_map->is_valid(dest)) {
                            sel_position.x += 1;
                        }
                        break;
                    default:
                        break;
                }
            }
        });

        subscribe(Stage::main_game_selection, SignalType::render_prepare, [this] (Signal* signal) {
            P_Player player = game_map->get_player();
            P_Character selected_character = game_map->character_at(sel_position);
            Point sel_pos_relative_to_window = main_window->get_center() + sel_position - game_map->get_pointer_position();

            if (selected_character != nullptr) {
                left_window->titled_text(selected_character->get_name(), selected_character->get_description());
                Colors::color_on(main_window->raw(), Colors::YELLOW_BLACK);
                main_window->print_at(sel_pos_relative_to_window, selected_character->get_skin());
                Colors::color_off(main_window->raw());

                if (selected_character != player) {
                    Colors::color_on(right_window->raw(), Colors::RED_BLACK);
                    right_window->content_at({1, 1}, selected_character->stats().to_strings());
                    Colors::color_off(right_window->raw());
                }
            } else {
                auto obj = game_map->object_at(sel_position);
                std::string skin = obj.skin == ' ' ? "+" : std::string(1, obj.skin);
                Colors::color_on(main_window->raw(), Colors::YELLOW_BLACK);
                main_window->print_at(sel_pos_relative_to_window, skin);
                Colors::color_off(main_window->raw());
                left_window->titled_text(obj.name, obj.description);
            }
        });
    }
};
