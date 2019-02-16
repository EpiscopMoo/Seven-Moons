#pragma once
#include <functional>
#include <algorithm>
#include <vector>
#include "signals/SignalBus.hpp"
#include "signals/SimpleSignals.hpp"

class Extension {

    SignalBus* bus = nullptr;
    Stage stage = Stage::intro;

protected:
    void subscribe(const std::vector<Stage>& stages, SignalType signal_type, std::function<void(Signal*)> f) {
        bus->register_slot(signal_type, [this, stages, f] (Signal* signal) {
            if (std::find(stages.begin(), stages.end(), stage) != stages.end()) {
                f(signal);
            }
        });
    }

    void subscribe(Stage _stage, SignalType signal_type, std::function<void(Signal*)> f) {
        bus->register_slot(signal_type, [this, _stage, f] (Signal* signal) {
            if (_stage == this->stage) {
                f(signal);
            }
        });
    }

    void subscribe(SignalType signal_type, std::function<void(Signal*)> f) {
        bus->register_slot(signal_type, f);
    }

    void send_signal(Signal* s) {
        bus->send_signal(s);
    }

    Stage get_stage() {
        return stage;
    }

public:
    virtual void initialize() = 0;
    virtual ~Extension() = default;

    explicit Extension(SignalBus* _bus) {
        bus = _bus;
        bus->register_slot(SignalType::stage_change, [this] (Signal* s) {
            stage = dynamic_cast<StageChangeSignal*>(s)->get_stage();
        });
    }

    Extension() = delete;

};
