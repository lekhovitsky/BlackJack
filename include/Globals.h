#pragma once
#include <map>
#include "enums.hpp"
#include <SFML/Graphics.hpp>

namespace Globals
{
	const sf::Vector2f	_tableSize{ 1136, 640 };
	const sf::Vector2f	_standardButtonSize{ 100, 30 };
	const sf::Vector2f	_cardSize{ 72, 96 };
	const float			_cardOffset = 12;
	const char* const	_cardBackImageFileName = "Resources\\Back.png";
	const char* const	_fontFileName = "Resources\\CaviarDreams.ttf";
	const float			_dealerBoxLineY = 60;
	const float			_playerBoxLineY = 300;
	static std::map<std::string,
		playerAnswer>	_strAnswMap{
		std::make_pair("Hit", playerAnswer::Hit),
		std::make_pair("Split", playerAnswer::Split),
		std::make_pair("Stand", playerAnswer::Stand),
		std::make_pair("Double", playerAnswer::Double),
		std::make_pair("Insure", playerAnswer::Insurance)
	};
}