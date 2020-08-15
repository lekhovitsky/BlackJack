#include "gui.hpp"
#include "game.hpp"

unsigned PlayerBox::num_boxes = 0;


int main()
{
    Player player;
    auto player_ptr = std::shared_ptr<Player>(&player);
    auto dealer_ptr = std::make_shared<Dealer>();
    auto shoes_ptr = std::make_shared<Shoes>(2);

    sf::Font font;
    sf::Texture texture;

    if (!texture.loadFromFile(GLOBALS::BACKGROUND_FILE))
        exit(1);

    if (!font.loadFromFile(GLOBALS::FONT_FILE))
        exit(1);

    GUI gui {texture, font};
    auto gui_ptr = std::shared_ptr<GUI>(&gui);

	Game<GUI> game{
            player_ptr,
            dealer_ptr,
            shoes_ptr,
            gui_ptr
	};

	gui.setBoxesAndSum(
	    game.get_boxes_ptr(),
	    player.get_balance_ptr()
	);

	while (game.round());
	return 0;
}
