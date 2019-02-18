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

    virtual std::vector<std::string> to_strings() const {
        std::vector<std::string> info_strs;
        info_strs.push_back(resource_bar(hp, max_hp, "HP"));
        if (max_ep > 0) {
            info_strs.push_back(resource_bar(ep, max_ep, "EP"));
        }
        if (max_charge > 0) {
            info_strs.push_back(resource_bar(charge, max_charge, "CH"));
        }
        if (max_barrier > 0) {
            info_strs.push_back(resource_bar(barrier, max_barrier, "BR"));
        }
        info_strs.push_back("Speed:   " + std::to_string(speed));
        info_strs.push_back("Damage:  " + std::to_string(base_damage));
        info_strs.push_back("Evasion: " + std::to_string((int) (evasion_chance * 100)) + "%");
        info_strs.push_back("View:    " + std::to_string(fov) + " cells");
        if (carrying_weight > 0) {
            info_strs.push_back("Carrying weight: " + std::to_string(carrying_weight));
        }
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

    template<typename T>
    std::string resource_bar(T current, T max, const std::string& label) const {
        auto blocks = static_cast<int>((float) current / max * 10.0f);
        std::string bar = label + ": [";
        for (int i=0; i<10; i++) {
            bar += (i < blocks) ? "=" : " ";
        }
        bar += "] " + std::to_string((int) current) + "/" + std::to_string((int) max);
        return bar;
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
        fov = 10 + comprehension;
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

    std::vector<std::string> to_strings() const override {
        auto stats_strings = GenericStats::to_strings();
        stats_strings.push_back("S.P.A.C.E. = " +
            std::to_string(strength) + " " +
            std::to_string(personality) + " " +
            std::to_string(agility) + " " +
            std::to_string(comprehension) + " " +
            std::to_string(energy)
        );
        return stats_strings;
    }
};

