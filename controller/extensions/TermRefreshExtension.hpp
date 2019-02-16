#pragma once
#include <set>

#include "../Extension.hpp"
#include "../../display/CWindow.hpp"
#include "../signals/SimpleSignals.hpp"

class TermRefreshExtension : public Extension {

    std::set<Container*> updating_windows;

public:
    explicit TermRefreshExtension(SignalBus *_bus) : Extension(_bus) {}

    void initialize() override {

        subscribe(SignalType::render_requested, [this] (Signal* signal) {
            updating_windows.insert(dynamic_cast<RenderRequestedSignal*>(signal)->get_window());
        });

        subscribe(SignalType::render_do, [this] (Signal*) {
            refresh();
            for (auto win : updating_windows) {
                win->update();
            }
            updating_windows.clear();
        });
    }

};