#ifndef PLAYER_BOX_HPP
#define PLAYER_BOX_HPP

#include "box.hpp"
#include "account.hpp"
#include "dealer_box.hpp"
#include <utility>


class PlayerBox : public Box
{
	size_t	 bet;
	size_t	 insurance;
	Account& account;
public:
	static unsigned num_boxes;
	PlayerBox(
	        Account &_account,
	        Shoes &_shoes,
	        size_t _bet = 0,
	        std::vector<Card> _cards = {}
	);
	~PlayerBox() override;
    PlayerBox(const PlayerBox&) noexcept;
    PlayerBox& operator=(const PlayerBox&) noexcept;

	[[nodiscard]] bool is_split_possible() const noexcept;
    [[nodiscard]] bool is_double_possible() const noexcept;
    [[nodiscard]] bool is_insurance_possible(const DealerBox&) const noexcept;

    [[nodiscard]] size_t get_bet_size() const noexcept { return bet; }
    [[nodiscard]] size_t get_insurance_size() const noexcept { return insurance; }

    void play_hit();
    void play_stand();
    void play_double();
    void play_insure();
    [[nodiscard]] PlayerBox play_split();
};

#endif
