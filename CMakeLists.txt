cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME BlackJack)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
find_package(SFML REQUIRED COMPONENTS graphics system window)

add_executable(BlackJack
        include/BaseOuter.h
        include/Box.h
        include/Box.hh
        include/Button.h
        include/card.hpp
        include/DealerBox.h
        include/DealerBox.hh
        include/enums.hpp
        include/Game.h
        include/Game.hh
        include/Globals.h
        include/Persons.h
        include/PlayerBox.h
        include/PlayerBox.hh
        include/resource.h
        include/Shoes.h
        include/WindowOuter.h
        src/Button.cpp
        src/card.cpp
        src/Main.cpp
        src/Persons.cpp
        src/Shoes.cpp
        src/WindowOuter.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        include
        assets
        src)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SFML_LIBRARIES})
