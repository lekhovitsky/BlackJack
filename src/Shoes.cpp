#include "shoes.hpp"
#include <random>
#include <algorithm>

Shoes::Shoes(size_t _num_decks) : num_decks(_num_decks)
{
	reset();
}

void Shoes::reset()
{
    cards.clear();

	for (size_t deck_index{ 0 }; deck_index < num_decks; ++deck_index)
		for (size_t card_index{ 0 }; card_index < NUM_CARDS_IN_DECK; ++card_index)
			cards.emplace_back(card_index);

    std::random_device rand;
    std::mt19937 gen{rand()};
	std::shuffle(cards.begin(), cards.end(), gen);
}

Card Shoes::get_card()
{
	auto top_card = cards.back();
	cards.pop_back();
	return top_card;
}

bool Shoes::is_reset_needed() const noexcept
{
	return cards.size() < (2 * num_decks * NUM_CARDS_IN_DECK / 4);
}
