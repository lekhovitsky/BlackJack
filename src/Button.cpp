#include "Button.h"

sf::Button::Button(
	const sf::Vector2f& pos, const sf::Vector2f& size,
	const std::string& str, const sf::Font& font,
	const sf::Color& background_color, const sf::Color& text_color,
	const sf::Color& outline_color, float outline_thikness
) noexcept
	: rect{ size }, text{ str, font } 
{
	rect.setPosition(pos);
	rect.setFillColor(background_color);
	rect.setOutlineThickness(5);
	rect.setOutlineColor(outline_color);
	text.setFillColor(text_color);
	float width = text.getGlobalBounds().width;
	text.setPosition({ pos.x + size.x / 2 - width / 2, pos.y - 4 });
}

void sf::Button::draw(
	sf::RenderTarget& target, sf::RenderStates states
) const
{
	target.draw(rect, states);
	target.draw(text, states);
}

bool sf::Button::contains(
	const sf::Vector2f& coord
) const noexcept
{
	return coord.x >= rect.getPosition().x && coord.x <= rect.getPosition().x + rect.getSize().x
		&& coord.y >= rect.getPosition().y && coord.y <= rect.getPosition().y + rect.getSize().y;
}

bool sf::Button::contains(
	const sf::Vector2i& coord
) const noexcept
{
	return contains(sf::Vector2f{ 
		static_cast<float>(coord.x),
		static_cast<float>(coord.y) });
}

