#ifndef GAME_HPP
#define GAME_HPP

#include "player_box.hpp"
#include "dealer_box.hpp"
#include "ui.hpp"

template<typename UI> using ui_ptr = std::shared_ptr<UI>;


template<typename UI,
	typename = std::enable_if_t<
	std::is_base_of<BaseUI, UI>::value
	>>
class Game
{
	player_ptr player;
	dealer_ptr dealer;
	shoes_ptr  shoes;
	ui_ptr<UI> ui;

    DealerBox dealer_box;
	std::vector<PlayerBox> player_boxes;
public:
	Game(
            player_ptr& _player, dealer_ptr& _dealer,
            shoes_ptr& _shoes, ui_ptr<UI>& ui
	)
        : player(_player)
        , dealer(_dealer)
        , shoes(_shoes)
        , ui(ui) {}

    bool round();
	void dealers_move();
	void players_move(PlayerBox&);
	void display_results();
	void reset();
};

#include "game.tpp"
#endif
