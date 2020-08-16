#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace sf
{
    class Button
        : public sf::Drawable
    {
        sf::RectangleShape rect;
        sf::Text text;
    public:
        Button(
            const sf::Vector2f& pos, const sf::Vector2f& size,
            const std::string& str, const sf::Font& font,
            const sf::Color& background_color = sf::Color::Black,
            const sf::Color& text_color = sf::Color::White,
            const sf::Color& outline_color = sf::Color::White,
            float outline_thickness = 2.0
        ) noexcept;
        Button() {}
        virtual void draw(
            sf::RenderTarget& target, sf::RenderStates states
        ) const;
        bool contains(
            const sf::Vector2f& coord
        ) const noexcept;
        bool contains(
            const sf::Vector2i& coord
        ) const noexcept;
    };
}

#endif
