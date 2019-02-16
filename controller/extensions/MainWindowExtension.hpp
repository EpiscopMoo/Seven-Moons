#pragma once
#include <ncurses.h>

#include "../Extension.hpp"
#include "../../display/Container.hpp"
#include "../signals/SimpleSignals.hpp"
#include "../../display/WindowTree.hpp"

class MainWindowExtension : public Extension {
    using json =  nlohmann::json;
    WindowTree* windows = nullptr;

public:
    explicit MainWindowExtension(SignalBus *_bus) : Extension(_bus) {}

    void initialize() override {
        subscribe(Stage::intro, SignalType::game_initialization, [this] (Signal* signal) {
            json layout;
            layout["x"] = 0;
            layout["y"] = 0;
            layout["w"] = COLS;
            layout["h"] = LINES;
            layout["containers"] = {{
                    {"proportions", {0.7f, 0.3f}},
                    {"split", "v"},
                    {"window", ""},
                    {"containers", {
                           {{"window", CWindow::type_name()}, {"code", "main"}},
                           {
                               {"proportions", {0.4f, 0.3f, 0.3f}},
                               {"split", "h"},
                               {"window", ""},
                               {"containers", {
                                      {{"window", CWindow::type_name()}, {"code", "left"}},
                                      {{"window", CWindow::type_name()}, {"code", "middle"}},
                                      {{"window", CWindow::type_name()}, {"code", "right"}}
                                  }
                               }
                           }
                        }
                    }
            }};
            windows = new WindowTree(layout);
            CWindow* main_window = windows->get_window<CWindow>("main");
            CWindow* middle_window = windows->get_window<CWindow>("middle");
            CWindow* left_window = windows->get_window<CWindow>("left");
            send_signal(new WindowCreatedSignal(main_window, "main"));
            send_signal(new WindowCreatedSignal(left_window, "left"));
            send_signal(new WindowCreatedSignal(middle_window, "middle"));
        });

        subscribe({Stage::main_game, Stage::main_game_selection}, SignalType::render_prepare, [this] (Signal* signal) {
            windows->for_each([this](Container* win) {
                win->print_border();
                send_signal(new RenderRequestedSignal(win));
            });
        });
    }

    ~MainWindowExtension() override {
        delete windows;
    }
};


