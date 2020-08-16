#ifndef BOX_HPP
#define BOX_HPP

#include <utility>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include "shoes.hpp"


class Box
{
public:
    std::vector<Card>			hand;
    Shoes					    &shoes;
	std::array<unsigned, 2U>	score;
	boxStatus					status;
	virtual void				refresh_status() noexcept;
	void						refresh_score() noexcept;

public:
	Box(Shoes &_shoes, std::vector<Card> _cards = {});

	void take_card() noexcept;
	void reset();

	[[nodiscard]] unsigned get_score() const noexcept { return score[0]; }
	void set_status(boxStatus s) { status = s; }
	[[nodiscard]] boxStatus get_status() const noexcept { return status; }
	[[nodiscard]] const std::vector<Card>& get_hand() const noexcept { return hand; }
	[[nodiscard]] bool busted() const noexcept { return status == boxStatus::Busted; }
    [[nodiscard]] bool in_game() const noexcept { return status == boxStatus::InGame; }
	[[nodiscard]] bool blackjack() const noexcept { return status == boxStatus::BlackJack; }
	virtual ~Box() = default;
};

#endif
