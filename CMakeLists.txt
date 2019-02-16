cmake_minimum_required(VERSION 3.8)
project(roguelike)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lncursesw")
set(SOURCE_FILES main.cpp display/Display.hpp display/CWindow.hpp controller/ExtensionManager.hpp controller/Extension.hpp controller/signals/SignalBus.hpp controller/signals/Signal.hpp controller/signals/SimpleSignals.hpp controller/extensions/MapExtension.hpp logic/Point.hpp controller/extensions/MainWindowExtension.hpp controller/extensions/TermRefreshExtension.hpp display/Container.hpp display/WindowTree.hpp logic/json.hpp display/MenuWindow.hpp display/Colors.hpp controller/extensions/IntroExtension.hpp display/static_inits/Colors.cpp logic/MapAttributes.hpp logic/GameMap.hpp logic/MapObject.hpp logic/Character.hpp logic/Player.hpp controller/extensions/PlayerExtension.hpp controller/extensions/SelectionExtension.hpp logic/GenericStats.hpp logic/VisibilityCalculator.hpp)
add_executable(roguelike ${SOURCE_FILES})