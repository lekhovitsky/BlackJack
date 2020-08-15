#ifndef PLAYER_BOX_HPP
#define PLAYER_BOX_HPP

#include "box.hpp"
#include "person.hpp"
#include "dealer_box.hpp"
#include <utility>

using player_ptr = std::shared_ptr<Player>;


class PlayerBox :
	public Box
{
public:
	player_ptr	player;
	unsigned	bet;
	unsigned	insurance;
public:
	static unsigned num_boxes;
	PlayerBox(
            player_ptr _player,
            const shoes_ptr& _shoes,
            unsigned _bet = 0U,
            std::vector<Card>&& _cards = {}
	)
        : Box{ _shoes, std::move(_cards) }
        , player{std::move(_player)}
        , bet{ _bet }
        , insurance{ 0 }
	{
        ++PlayerBox::num_boxes;
	}
	~PlayerBox() override;

	void make_bet();
	void pay_reward(boxStatus, unsigned);

	[[nodiscard]] bool is_split_possible() const noexcept;
    [[nodiscard]] bool is_double_possible() const noexcept;
    [[nodiscard]] bool is_insurance_possible(const DealerBox&) const noexcept;
};

#endif
