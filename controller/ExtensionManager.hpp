#pragma once
#include <vector>

#include "../display/Display.hpp"
#include "Extension.hpp"
#include "signals/SimpleSignals.hpp"
#include "extensions/MapExtension.hpp"
#include "extensions/MainWindowExtension.hpp"
#include "extensions/TermRefreshExtension.hpp"
#include "extensions/IntroExtension.hpp"
#include "extensions/PlayerExtension.hpp"
#include "extensions/SelectionExtension.hpp"
#include "extensions/EnemiesExtension.hpp"

class ExtensionManager {

public:
    ExtensionManager() {
        extensions.push_back(new MapExtension(&bus));
        extensions.push_back(new MainWindowExtension(&bus));
        extensions.push_back(new TermRefreshExtension(&bus));
        extensions.push_back(new IntroExtension(&bus));
        extensions.push_back(new PlayerExtension(&bus));
        extensions.push_back(new SelectionExtension(&bus));
        extensions.push_back(new EnemiesExtension(&bus));
    }

    ~ExtensionManager() {
        for (auto extension : extensions) {
            delete extension;
        }
        delete window;
    }

    void do_game() {
        Display::instance().init();
        Display::instance().update();
        initialize_extensions();

        while (!exit_game_flag) {
            process_render();
            process_input(getch());
            process_player_sequence();
            process_enemy_sequence();
        }
    }

private:

    bool exit_game_flag = false;
    std::vector<Extension*> extensions;
    SignalBus bus;
    CWindow* window = nullptr;

    void initialize_extensions() {
        for (auto ext : extensions) {
            ext->initialize();
        }
        bus.register_slot(SignalType::game_end, [this] (Signal*) {
            exit_game_flag = true;
        });
        bus.send_signal(new GameInitializationSignal());
    }

    void process_input(int sym) {
        bus.send_signal(new KeyDownSignal(sym));
    }

    void process_render() {
        bus.send_signal(new RenderPrepareSignal());
        bus.send_signal(new RenderDoSignal());
    }

    void process_player_sequence() {
        bus.send_signal(new PlayerSequenceSignal());
    }

    void process_enemy_sequence() {
        bus.send_signal(new EnemySequenceSignal());
    }
};