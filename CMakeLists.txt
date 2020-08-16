cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME BlackJack)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics system window)

add_executable(BlackJack
        src/Main.cpp
        src/game.hpp
        src/game.tpp
        src/card.hpp
        src/card.cpp
        src/shoes.hpp
        src/shoes.cpp
        src/box.hpp
        src/box.cpp
        src/dealer_box.hpp
        src/dealer_box.cpp
        src/player_box.hpp
        src/player_box.cpp
        src/account.hpp
        src/ui.hpp
        src/gui.hpp
        src/gui.cpp
        src/button.hpp
        src/button.cpp
        src/enums.hpp
        src/globals.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        src assets)

target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics
        sfml-window
        sfml-system)
