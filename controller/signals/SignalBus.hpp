#pragma once
#include <map>
#include <vector>
#include <functional>
#include "Signal.hpp"

class SignalBus {

public:
    void register_slot(SignalType signal_type, std::function<void(Signal *)> handler) {
        slots[signal_type].push_back(handler);
    }

    void send_signal(Signal *signal) {
        for (auto& func : slots[signal->type()]) {
            func(signal);
        }
        delete signal;
    }


private:
    std::map<SignalType, std::vector<std::function<void(Signal*)>>> slots;
};
