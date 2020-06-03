#pragma once
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include "Shoes.h"

using shoes_ptr = std::shared_ptr<Shoes>;
template<class UI>
using outer_ptr = std::shared_ptr<UI>;


template<class UI>
class Box :
	public std::enable_shared_from_this<Box<UI>>
{
protected:
	shoes_ptr					shoes;
	outer_ptr<UI>				outer;
	std::array<unsigned, 2U>	score;
	std::vector<Card>			hand;
	boxStatus					status;
	virtual void				refreshStatus() noexcept;
	void						refreshScore() noexcept;
public:
	using Boxes = std::vector<std::shared_ptr<Box<UI>>>;
	// Конструктор позволяет задать карты, 
	// с которыми должен быть создан бокс
	Box(const shoes_ptr& _shoes, const outer_ptr<UI>& _outer,
		std::vector<Card>&& _cards = std::vector<Card>())
		: shoes{ _shoes }, outer{ _outer },
		score{ 0U, 0U }, hand{ _cards }
	{
		refreshScore();
		refreshStatus();
	}
	virtual void	play(Boxes&) = 0;
	void			takeCard() noexcept;
	const unsigned	getScore() const noexcept { return score[0]; }
	const boxStatus getStatus() const noexcept { return status; }
	const std::vector<Card>& 
					getHand() const noexcept { return hand; }
	bool			isBlackJack() const noexcept;
	virtual			~Box() = default;
};

/// -------Реализация шаблонных методов-------
#include "Box.hh"