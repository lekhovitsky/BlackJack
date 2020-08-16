#include "gui.hpp"
#include "game.hpp"

unsigned PlayerBox::num_boxes = 0;


int main()
{
    sf::Font font;
    sf::Texture texture;

    if (!texture.loadFromFile(GLOBALS::BACKGROUND_FILE)
        || !font.loadFromFile(GLOBALS::FONT_FILE))
        exit(1);

    GUI gui {texture, font};
    auto gui_ptr = std::shared_ptr<GUI>(&gui);

	Game<GUI> game{gui_ptr};

	while (game.round());
	return 0;
}
