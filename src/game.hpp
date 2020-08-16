#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include "account.hpp"
#include "player_box.hpp"
#include "dealer_box.hpp"
#include "ui.hpp"

template<typename UI> using ui_ptr = std::shared_ptr<UI>;


template<typename UI,
        typename = std::enable_if_t<
                std::is_base_of_v<BaseUI, UI>>
        >
class Game
{
    Shoes shoes;
    ui_ptr<UI> ui;

    Account account;
    DealerBox dealer_box;
    std::vector<PlayerBox> player_boxes;
public:
    explicit Game(
            ui_ptr<UI>& ui,
            size_t initial_balance = 1000,
            size_t num_decks = 2);

    bool round();
    void dealers_move();
    void players_move(PlayerBox&);
    void result(PlayerBox&);

    void display_results();
    void reset();
};

#include "game.tpp"
#endif
