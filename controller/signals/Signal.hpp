#pragma once

enum class Stage {
    all,
    intro,
    esc_menu,
    main_game,
    main_game_selection,
    inventory
};

enum class SignalType {
    game_initialization,
    game_end,
    after_move,
    key_down,
    render_prepare,
    render_requested,
    render_do,
    window_created,
    stage_change,
    game_map_reload,
    player_created,
    character_render,
    player_sequence,
    enemy_sequence
};

struct Signal {
    virtual SignalType type() = 0;
    virtual ~Signal() = default;
};

