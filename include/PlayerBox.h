#pragma once
#include "Persons.h"
#include "DealerBox.h"
#include <unordered_set>

using player_ptr = std::shared_ptr<Player>;

template<class UI>
class PlayerBox :
	public Box<UI>
{
protected:
	player_ptr	player;
	unsigned	bet;
	unsigned	insurance;
public:
	static unsigned num_boxes;
	PlayerBox(
		const player_ptr& _player, const shoes_ptr& _shoes,
		const outer_ptr<UI>& _outer, unsigned _bet = 0U,
		std::vector<Card>&& _cards = std::vector<Card>()
	);
	~PlayerBox();

	void play(Boxes&) override;
	void makeBet();
	void payReward(boxStatus, unsigned);

	bool split_is_possible() const noexcept;
	bool double_is_possible() const noexcept;
	bool insurance_is_possible(const DealerBox<UI>&) const noexcept;
};

/// -------Реализация шаблонных методов-------
#include "PlayerBox.hh"