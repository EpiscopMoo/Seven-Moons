#include <locale>
#include "controller/ExtensionManager.hpp"

int main() {
    setlocale(LC_CTYPE, "ru_RU.UTF8");
    ExtensionManager game_manager;
    game_manager.do_game();
    return 0;
}