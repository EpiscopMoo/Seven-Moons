#pragma once

#include <utility>
#include <vector>
#include <map>
#include <functional>
#include <cassert>
#include "../logic/json.hpp"
#include "Container.hpp"
#include "CWindow.hpp"

class WindowTree {
    using json =  nlohmann::json;

    std::map<std::string, Container*> windows;
    enum class Split {
        H, V
    };

public:

    WindowTree(json& layout) {
        Point orig = { layout["x"], layout["y"] };
        int w = layout["w"];
        int h = layout["h"];
        process_container(orig, w, h, layout["containers"][0]);

    }

    void process_container(Point orig, int w, int h, json& layout) {
        if (layout["window"] == WinType::CWINDOW) {
            windows[layout["code"]] = new CWindow(orig, w, h);
        } else {
            std::vector<float> proportions = layout["proportions"];
            Split split = (layout["split"] == "v") ? Split::V : Split::H;
            int cont_idx = 0;
            for (auto& container : layout["containers"]) {
                int cur_w = (split == Split::H) ? w * proportions[cont_idx] : w;
                int cur_h = (split == Split::V) ? h * proportions[cont_idx] : h;

                //horizontal layout border fix:
                int fixed_w = std::min(cur_w + 1, w - orig.x);

                process_container(orig, fixed_w, cur_h, container);
                if (split == Split::H) {
                    orig.x += cur_w;
                } else {
                    orig.y += cur_h;
                }
                cont_idx++;
            }
        }
    }

    ~WindowTree() {
        for (auto& win : windows) {
            delete win.second;
        }
    }

    void for_each(std::function<void(Container*)> handler) {
        for (auto& win : windows) {
            handler(win.second);
        }
    }

    Container* get_window(const std::string& code) {
        return windows.at(code);
    }

    Container* get_window(const char* code) {
        return windows.at(code);
    }

    template<typename T> T* get_window(const char* code) {
        return dynamic_cast<T*>(get_window(code));
    }
};