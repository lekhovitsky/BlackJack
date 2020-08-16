#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "enums.hpp"

#include <map>
#include <SFML/Graphics.hpp>


namespace GLOBALS
{
    const sf::Vector2f	TABLE_SIZE{1136, 640 };
    const sf::Vector2f	BUTTON_SIZE{100, 30 };
    const sf::Vector2f	CARD_SIZE{72, 96 };
    const float			_cardOffset = 12;

    const char* const   BACKGROUND_FILE = "../assets/table.png";
    const char* const	CARD_BACK_FILE = "../assets/back.png";
    const char* const	FONT_FILE = "../assets/CaviarDreams.ttf";
    const float			_dealerBoxLineY = 60;
    const float			_playerBoxLineY = 300;
    static std::map<std::string, playerAnswer> _strAnswMap{
        std::make_pair("Hit", playerAnswer::Hit),
        std::make_pair("Split", playerAnswer::Split),
        std::make_pair("Stand", playerAnswer::Stand),
        std::make_pair("Double", playerAnswer::Double),
        std::make_pair("Insure", playerAnswer::Insure)
    };
}

#endif
