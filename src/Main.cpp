#include "WindowOuter.h"
#include "Game.h"
unsigned PlayerBox<WindowOuter>::num_boxes = 0;

int main() 
{
	sf::Texture texture;
	if (!texture.loadFromFile("assets/Table.png")) { exit(1); }
	sf::Font font;
	if (!font.loadFromFile(Globals::_fontFileName)) { exit(1); }
	WindowOuter table{ texture, font };
	Player player("Player");
	auto dealer_ptr = std::make_shared<Dealer>();
	auto shoes_ptr = std::make_shared<Shoes>(2);
	auto player_ptr = std::shared_ptr<Player>(&player);
	auto table_ptr = std::shared_ptr<WindowOuter>(&table);
	Game<WindowOuter> game{ player_ptr, dealer_ptr, shoes_ptr, table_ptr };
	table.setBoxesAndSum(game.getVecPtr(), player.getSumPtr());
	while (game.round());
	return 0;
}