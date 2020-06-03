#include "Shoes.h"
#include <random>
#include <ctime>
#include <algorithm>

Shoes::Shoes(size_t _num_decks)
	    : num_decks(_num_decks) {
	reset();
}

void Shoes::reset() {
	srand(time(NULL));
	static std::default_random_engine gen(rand());
	srand(0);
	for (size_t deck_index{ 0 }; deck_index < num_decks; ++deck_index) {
		for (size_t card_index{ 0 }; card_index < NUM_CARDS_IN_DECK; ++card_index)
		{
			cards.emplace_back(card_index);
		}
	}
	std::shuffle(cards.begin(), cards.end(), gen);
}

Card Shoes::getCard() {
	auto top_card = cards.back();
	cards.pop_back();
	return top_card;
}

bool Shoes::needToReset() const noexcept {
	return cards.size() < (3 * num_decks * NUM_CARDS_IN_DECK / 4);
}
