cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME BlackJack)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics system window)

add_executable(BlackJack
        src/ui.hpp
        src/box.hpp
        src/box.cpp
        src/button.hpp
        src/card.hpp
        src/dealer_box.hpp
        src/dealer_box.cpp
        src/enums.hpp
        src/game.hpp
        src/game.tpp
        src/globals.hpp
        src/person.hpp
        src/player_box.hpp
        src/player_box.cpp
        src/resource.h
        src/shoes.hpp
        src/gui.hpp
        src/button.cpp
        src/card.cpp
        src/main.cpp
        src/person.cpp
        src/shoes.cpp
        src/gui.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        src assets)

target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics
        sfml-window
        sfml-system)
