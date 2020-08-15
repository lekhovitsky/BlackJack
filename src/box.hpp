#ifndef BOX_HPP
#define BOX_HPP

#include <utility>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include "shoes.hpp"

// TODO: unite all boxes in a single file

using shoes_ptr = std::shared_ptr<Shoes>;


class Box
        : public std::enable_shared_from_this<Box>
{
public:
    std::vector<Card>			hand;
    shoes_ptr					shoes;
	std::array<unsigned, 2U>	score;
	boxStatus					status;
	virtual void				refresh_status() noexcept;
	void						refresh_score() noexcept;

public:
    using Boxes = std::vector<std::shared_ptr<Box>>;

	Box(
	        shoes_ptr _shoes,
		    std::vector<Card>&& _cards = {}
	)
		: shoes{std::move(_shoes)}
		, status{boxStatus::InGame}
		, score{0U, 0U}
		, hand{_cards}
	{
        refresh_score();
        refresh_status();
	}
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
