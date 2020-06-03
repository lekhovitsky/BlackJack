#pragma once
#include "PlayerBox.h"
#include "DealerBox.h"
#include "BaseOuter.h"

template<class UI, 
	typename = std::enable_if_t<
	std::is_base_of<BaseOuter, UI>::value
	>>
class Game
{
	player_ptr player;
	dealer_ptr dealer;
	shoes_ptr  shoes;
	outer_ptr<UI> outer;
	typename Box<UI>::Boxes box_vec;
public:
	Game(
		player_ptr& _player, dealer_ptr& _dealer,
		shoes_ptr& _shoes, outer_ptr<UI>& _outer
	) : player(_player), dealer(_dealer),
		shoes(_shoes), outer(_outer)
	{}
	bool round();
	void reset();
	std::shared_ptr<typename Box<UI>::Boxes> getVecPtr() noexcept
	{
		static auto ptr =
			std::shared_ptr<typename Box<UI>::Boxes>(&box_vec);
		return ptr;
	}
};

/// -------Реализация шаблонных методов-------
#include "Game.hh"