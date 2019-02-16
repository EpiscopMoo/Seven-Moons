#pragma once
#include <functional>
#include "CWindow.hpp"
#include "Colors.hpp"

class MenuWindow : public CWindow {
public:
    MenuWindow() = delete;
    MenuWindow(Point xy, int _w, int _h) : CWindow(xy, _w, _h) {}

    static std::string type_name() {
        return "menu";
    }

    void add_menu_item(const std::string& item) {
        options.push_back(item);
    }

    void add_menu_item(const char* item) {
        add_menu_item(std::string(item));
    }

    void set_menu_items(const std::vector<std::string>& items) {
        options.clear();
        options = items;
    }

    //When selected item changes, do given action:
    void set_on_selection_move(std::function<void(int, std::string&)> handler) {
        on_selection_handler = handler;
    }

    void set_on_enter_press(std::function<void(int, std::string&)> handler) {
        on_enter_press = handler;
    }

    void feed_input(int key) {
        if (key == KEY_DOWN && selection < options.size() - 1) {
            selection++;
            if (on_selection_handler) on_selection_handler(selection, options[selection]);
        } else if (key == KEY_UP && selection > 0) {
            selection--;
            if (on_selection_handler) on_selection_handler(selection, options[selection]);
        } else if (key == KEY_ENTER || key == ' ') {
            on_enter_press(selection, options[selection]);
        }
    }

    void print_menu_items() {
        for (int i = 0; i < options.size(); i++) {
            if (selection == i) {
                Colors::color_on(window, Colors::BLACK_WHITE);
            } else {
                Colors::color_on(window, Colors::WHITE_BLACK);
            }
            print_at({1, i + 1}, options[i]);
            Colors::color_off(window);
        }
    }

private:
    std::vector<std::string> options;
    std::function<void(int, std::string&)> on_selection_handler = nullptr;
    std::function<void(int, std::string&)> on_enter_press = nullptr;

    int selection = 0;
};


