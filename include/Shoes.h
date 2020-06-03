#pragma once
#include "card.hpp"
#include <vector>

#define NUM_CARDS_IN_DECK 56


class Shoes {
	std::vector<Card>	cards;
	size_t			num_decks;
public:
	explicit Shoes(size_t _num_decks = 1);
	Shoes(const Shoes&) = default;
	Shoes(Shoes&&) noexcept = default;
	void reset();
	Card getCard();
	[[nodiscard]] bool needToReset() const noexcept;
};