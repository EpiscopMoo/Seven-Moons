#pragma once
#include <vector>
#include <string>

struct GenericStats {

    int hp;
    int max_hp;
    int ep; //energy points spent on PSY-abilities
    int max_ep;
    int charge; //tech energy points spent on technical abilities and tools
    int max_charge;
    float barrier; //tech barrier
    float max_barrier;
    int speed; //aka action points
    float evasion_chance;
    int base_melee_damage;
    int fov; //view radius
    int base_reaction; //reaction towards this stat holder from other npcs
    int carrying_weight;

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
        return info_strs;
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
        base_melee_damage = strength;
        fov = 4 + comprehension;
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

