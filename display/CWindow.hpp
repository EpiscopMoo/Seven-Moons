#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <ncurses.h>
#include <iterator>
#include <sstream>
#include "../logic/Point.hpp"
#include "Container.hpp"

class CWindow : public Container {

public:
    virtual void content_at(Point p, const std::vector<std::string>& strings) {
        size_t x = (size_t) std::max(0, p.x);
        size_t y = (size_t) std::max(0, p.y);
        size_t offset_x = -std::min(0, p.x);
        size_t offset_y = -std::min(0, p.y);
        size_t max_len = w - 1 - x;
        size_t max_h = h - 1 - y;
        if (max_len < 1 || max_h < 1 || x > w - 2 || y > h - 2) {
            return;
        }
        for (size_t i = offset_y; i < std::min(strings.size(), offset_y + max_h); i++) {
            const auto& str = strings[i];
            std::string to_print = str.substr(std::min(offset_x, strlen(str)), max_len);
            if (!to_print.empty()) {
                print_at({(int) x, (int) (y + i - offset_y)}, to_print);
            }
        }
    }

    virtual void text_at(const std::string& text) {
        text_at({1, 1}, text);
    }

    virtual void titled_text_at(const std::string& title, const std::string& text) {
        print_at({1, 1}, title);
        text_at({1, 3}, text);
    }

    virtual void print_at(Point p, const std::string& str) {
        print_at(p, str.c_str());
    }

    virtual void print_at(Point p, const char* str_raw) {
        mvwaddstr(window, p.y + 1, p.x + 1, str_raw);
    }

    virtual void print_border(chtype hor, chtype vert, chtype corner) {
        wborder(window, vert, vert, hor, hor, corner, corner, corner, corner);
        if (!title.empty()) {
            int title_x = std::max(0, (int) ((w - 2)/2 - (strlen(title) + 2)/2) );
            print_at({title_x, -1}, " " + title + " ");
        }
        if (!hint.empty()) {
            int hint_x = std::max(0, (int) ((w - strlen(hint) - 2)/2) );
            print_at({hint_x, h - 2}, " " + hint + " ");
        }
    }

    virtual void print_border() {
        print_border('-', '|', '+');
    }

    virtual void update() {
        wrefresh(window);
        werase(window);
    }

    static std::string type_name() {
        return "cwindow";
    }

    virtual WINDOW* raw() override {
        return window;
    }

    virtual ~CWindow() {
        if (window) delwin(window);
    }

    CWindow() = delete;
    CWindow(Point xy, int _w, int _h) {
        gx = xy.x;
        gy = xy.y;
        w = _w;
        h = _h;
        window = newwin(h, w, gy, gx);
    }

protected:
    WINDOW* window = nullptr;

private:
    size_t strlen(const std::string& str) {
        return str.length();
    }

    virtual void text_at(Point p, const std::string& text) {
        int x = p.x, y = p.y;
        int effective_h = h - 2 - y;
        int effective_w = w - 3 - x;
        if (effective_h < 1 || effective_w < 1) {
            throw std::invalid_argument("Bad dx,dy for text_at with Pt: " + std::to_string(x) + ", " + std::to_string(y) +
                                                " and w,h:" + std::to_string(w) + ", " + std::to_string(h));
        }
        std::stringstream space_stream(text);
        std::istream_iterator<std::string> begin(space_stream);
        std::istream_iterator<std::string> end;
        std::vector<std::string> words(begin, end);
        std::vector<std::string> result(effective_h);
        int result_idx = 0;
        for (const auto& word : words) {
            if (strlen(result[result_idx] + word) + 1 > effective_w) {
                result_idx++;
                if (result_idx >= effective_h) {
                    break;
                }
            }
            result[result_idx] += word + " ";
        }
        content_at(p, result);
    }
};


