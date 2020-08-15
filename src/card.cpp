#include "card.hpp"
#include <stdexcept>


Card::Card(cardValue value, cardSuit suit) noexcept
    : _value{value}
    , _suit{suit} {}

Card::Card(size_t value) noexcept
    : _suit{static_cast<cardSuit>(value % NUM_SUITS + 1)}
    , _value{static_cast<cardValue>(value % NUM_VALUES + 1)} {}

void Card::set_suit(size_t value)
{
    if (value >= NUM_SUITS)
        throw std::invalid_argument { "For success cast value must be from 1 to 4" };
    _suit = static_cast<cardSuit>(value);
}

void Card::set_val(size_t value)
{
    if (value == 0 || value > NUM_VALUES)
        throw std::invalid_argument { "For success cast value must be from 1 to 13" };
    _value = static_cast<cardValue>(value);
}

unsigned Card::get_score() const noexcept
{
	if (_value == cardValue::Jack  ||
        _value == cardValue::Queen ||
        _value == cardValue::King)
	    return 10;
	return static_cast<unsigned>(_value);
}

bool Card::equal_score(const Card& c1, const Card& c2)
{
	return c1.get_score() == c2.get_score();
}
