#pragma once
#include <vector>
#include <string>

struct GenericStats {

    using json = nlohmann::json;

    int hp = 0;
    int max_hp = 0;
    int ep = 0; //energy points spent on PSY-abilities
    int max_ep = 0;
    int charge = 0; //tech energy points spent on technical abilities and tools
    int max_charge = 0;
    float barrier = 0; //tech barrier
    float max_barrier = 0;
    int speed = 0; //aka action points
    float evasion_chance = 0;
    int base_damage = 0;
    int fov = 0; //view radius
    int base_reaction = 0; //reaction towards this stat holder from other NPCs
    int carrying_weight = 0;

    std::vector<std::string> descr() {
        std::vector<std::string> info_strs;
        info_strs.push_back("Health:  " + std::to_string(hp) + "/" + std::to_string(max_hp));
        if (max_ep > 0) {
            info_strs.push_back("Energy:  " + std::to_string(ep) + "/" + std::to_string(max_ep));
        }
        if (max_charge > 0) {
            info_strs.push_back("Charge:  " + std::to_string(charge) + "/" + std::to_string(max_charge));
        }
        if (max_barrier > 0) {
            info_strs.push_back("Barrier: " + std::to_string(barrier) + "/" + std::to_string(max_barrier));
        }
        info_strs.push_back("Speed:   " + std::to_string(speed));
        info_strs.push_back("Damage: " + std::to_string(base_damage));
        return info_strs;
    }

    static GenericStats from_json(const json& stats_config) {
        GenericStats stats;
        if (defined(stats_config, "hp")) {
            stats.hp = stats_config["hp"];
        }
        if (defined(stats_config, "max_hp")) {
            stats.max_hp = stats_config["max_hp"];
        }
        if (defined(stats_config, "ep")) {
            stats.ep = stats_config["ep"];
        }
        if (defined(stats_config, "max_ep")) {
            stats.max_ep = stats_config["max_ep"];
        }
        if (defined(stats_config, "charge")) {
            stats.charge = stats_config["charge"];
        }
        if (defined(stats_config, "max_charge")) {
            stats.max_charge = stats_config["max_charge"];
        }
        if (defined(stats_config, "barrier")) {
            stats.barrier = stats_config["barrier"];
        }
        if (defined(stats_config, "max_barrier")) {
            stats.max_barrier = stats_config["max_barrier"];
        }
        if (defined(stats_config, "speed")) {
            stats.speed = stats_config["speed"];
        }
        if (defined(stats_config, "evasion_chance")) {
            stats.evasion_chance = stats_config["evasion_chance"];
        }
        if (defined(stats_config, "base_damage")) {
            stats.base_damage = stats_config["base_damage"];
        }
        if (defined(stats_config, "fov")) {
            stats.fov = stats_config["fov"];
        }
        if (defined(stats_config, "base_reaction")) {
            stats.base_reaction = stats_config["base_reaction"];
        }
        if (defined(stats_config, "carrying_weight")) {
            stats.carrying_weight = stats_config["carrying_weight"];
        }
        return stats;
    }

private:
    static bool defined(const json& stats_config, const std::string& field) {
        return stats_config.find(field) != stats_config.end();
    }
};

struct PlayerStats : public GenericStats {
    int strength;
    int personality;
    int agility;
    int comprehension;
    int energy;

    void update_secondary() {
        max_ep = energy * 2;
        speed = 2 + agility;
        evasion_chance = agility * 5.0f / 100.0f;
        base_damage = strength;
        fov = 8 + comprehension;
        base_reaction = personality*10 + 50;
        carrying_weight = 50 + strength*20;

        ep = max_ep;
        hp = max_hp;
    }

    void set_space_and_update(int s, int p, int a, int c, int e, int mhp) {
        strength = s;
        personality = p;
        agility = a;
        comprehension = c;
        energy = e;
        max_hp = mhp;
        update_secondary();
    }

    std::vector<std::string> to_strings() const {
        auto blocks = static_cast<int>((float) hp / max_hp * 10.0f);
        std::string hp_bar = "HP: [";
        for (int i=0; i<10; i++) {
            hp_bar += (i < blocks) ? "=" : " ";
        }
        hp_bar += "] " + std::to_string(hp) + "/" + std::to_string(max_hp);

        blocks = static_cast<int>((float) ep / max_ep * 10.0f);
        std::string ep_bar = "EP: [";
        for (int i=0; i<10; i++) {
            ep_bar += (i < blocks) ? "=" : " ";
        }
        ep_bar += "] " + std::to_string(ep) + "/" + std::to_string(max_ep);
        return {
            hp_bar,
            ep_bar,
            "Strength:      " + std::to_string(strength),
            "Personality:   " + std::to_string(personality),
            "Agility:       " + std::to_string(agility),
            "Comprehension: " + std::to_string(comprehension),
            "Energy:        " + std::to_string(energy)
        };
    }
};

