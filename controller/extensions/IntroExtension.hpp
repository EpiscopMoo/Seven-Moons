#pragma once
#include <ncurses.h>

#include "../Extension.hpp"
#include "../../display/MenuWindow.hpp"

class IntroExtension : public Extension {

    MenuWindow* menu = nullptr;
    enum MenuItem {
        NEW_GAME = 0,
        OPTIONS = 1,
        ABOUT = 2,
        EXIT = 3
    };

    void process_menu_choice(int item) {
        if (item == EXIT) {
            send_signal(new GameEndSignal);
        } else {
            send_signal(new StageChangeSignal(Stage::main_game));
        }
    }

public:
    explicit IntroExtension(SignalBus *_bus) : Extension(_bus) {

    }

    void initialize() override {
        subscribe(Stage::intro, SignalType::game_initialization, [this] (Signal*) {
            int w = COLS;
            int h = LINES;
            int x = w/2 - 7;
            int y = h/2 - 3;
            menu = new MenuWindow({x, y}, 16, 8);
            menu->add_menu_item("New Game");
            menu->add_menu_item("Options");
            menu->add_menu_item("About");
            menu->add_menu_item("Exit");
            menu->set_title("Seven Moons");
            menu->set_on_enter_press([this] (int i, std::string&) { process_menu_choice(i); });
        });

        subscribe(Stage::intro, SignalType::render_prepare, [this] (Signal* s) {
            menu->print_border();
            menu->print_menu_items();
            send_signal(new RenderRequestedSignal(menu));
        });

        subscribe(Stage::intro, SignalType::key_down, [this] (Signal* signal) {
            int key = dynamic_cast<KeyDownSignal*>(signal)->get_key();
            menu->feed_input(key);
        });
    }

    ~IntroExtension() {
        delete menu;
    }
};


