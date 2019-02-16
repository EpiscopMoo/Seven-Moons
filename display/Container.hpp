#pragma once
#include <string>
#include <vector>
#include <ncurses.h>
#include "../logic/Point.hpp"

struct WinType {
    static constexpr const char* CWINDOW = "cwindow";
    static constexpr const char* MENU = "menu";
    static constexpr const char* NONE = "none";
};

class Container {

protected:

    int w = 0;
    int h = 0;
    int gx = 0;
    int gy = 0;
    std::string title;
    std::string hint;

public:
    virtual void content_at(Point p, const std::vector<std::string> &strings) = 0;

    virtual void text_at(const std::string& text) = 0;

    virtual void titled_text_at(const std::string& title, const std::string& text) = 0;

    virtual void print_at(Point p, const std::string &str) = 0;

    virtual void print_at(Point p, const char *str_raw) = 0;

    virtual void print_border(chtype hor, chtype vert, chtype corner) = 0;

    virtual void set_title(const std::string& _title) {
        title = _title;
    };

    virtual void set_hint(const std::string& _hint) {
        hint = _hint;
    };

    virtual void set_hint(const char* _hint) {
        set_hint(std::string(_hint));
    };

    virtual void print_border() = 0;

    virtual void update() = 0;

    virtual int get_h() {
        return h;
    }

    virtual int get_w() {
        return w;
    }

    virtual Point get_position() {
        return {gx, gy};
    }

    virtual Point get_center() {
        return { w/2, h/2 };
    }

    static std::string type_name() { return "none"; };

    virtual WINDOW* raw() = 0;

    virtual ~Container() = default;
};
