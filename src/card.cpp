#include "card.hpp"

void Card::set_suit(const cardSuit& suit) noexcept {
    _suit = suit;
}

void Card::set_val(const cardValue& value) noexcept {
    _value = value;
}

unsigned Card::get_score() const noexcept {
	if (_value == cardValue::Jack  ||
        _value == cardValue::Queen ||
        _value == cardValue::King) return 10;
	return static_cast<unsigned>(_value);
}

bool Card::same_score(const Card& c1, const Card& c2) {
	return c1.get_score() == c2.get_score();
}