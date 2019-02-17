#pragma once

#include "Signal.hpp"
#include "../../display/CWindow.hpp"
#include "../../logic/GameMap.hpp"
#include "../../logic/Character.hpp"
#include "../../logic/Player.hpp"

struct GameInitializationSignal : public Signal {

    SignalType type() override {
        return SignalType ::game_initialization;
    }
};

struct GameEndSignal : public Signal {

    SignalType type() override {
        return SignalType ::game_end;
    }
};

struct KeyDownSignal : public Signal {

    explicit KeyDownSignal(int _sym) : key(_sym) {}

    int get_key() { return key; }

    SignalType type() override {
        return SignalType ::key_down;
    }

private:
    int key;
};

struct RenderPrepareSignal : public Signal {

    SignalType type() override {
        return SignalType ::render_prepare;
    }
};

struct RenderDoSignal : public Signal {

    SignalType type() override {
        return SignalType ::render_do;
    }
};

struct WindowCreatedSignal : public Signal {

    explicit WindowCreatedSignal(Container* _win, const std::string& _code) : window(_win), code(_code) {}
    Container* get_window() { return window; }
    const std::string& get_code() {
        return code;
    }

    SignalType type() override {
        return SignalType::window_created;
    }

private:
    Container* window;
    std::string code;
};

struct RenderRequestedSignal : public Signal {

    explicit RenderRequestedSignal(Container* _win) : window(_win) {}
    Container* get_window() { return window; }

    SignalType type() override {
        return SignalType ::render_requested;
    }

private:
    Container* window;
};

struct StageChangeSignal : public Signal {
    explicit StageChangeSignal(Stage _stage) : stage(_stage) {}
    Stage get_stage() {
        return stage;
    }
    SignalType  type() override {
        return SignalType ::stage_change;
    }

private:
    Stage stage;
};

struct GameMapReloadSignal : public Signal {

    explicit GameMapReloadSignal(GameMap* _game_map) : game_map(_game_map) {}
    GameMap* get_game_map() {
        return game_map;
    }

    SignalType type() override {
        return SignalType::game_map_reload;
    }

private:
    GameMap* game_map;
};

struct CharacterRenderSignal : public Signal {

    explicit CharacterRenderSignal(P_Character _character) : character(_character) {}
    P_Character get_character() {
        return character;
    }

    SignalType type() override {
        return SignalType ::character_render;
    }

private:
    P_Character character;
};

struct PlayerSequenceSignal : public Signal {

    SignalType type() override {
        return SignalType ::player_sequence;
    }
};

struct EnemySequenceSignal : public Signal {

    SignalType type() override {
        return SignalType ::enemy_sequence;
    }
};