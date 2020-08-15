#ifndef CARD_HPP
#define CARD_HPP

#include "enums.hpp"
#include <cstddef>

#define NUM_VALUES 13
#define NUM_SUITS 4


class Card
{
    cardValue	_value;
	cardSuit	_suit;
public:
    explicit Card(size_t value) noexcept;
    Card(cardValue value, cardSuit suit) noexcept;

	Card(Card&&) noexcept = default;
	Card(const Card&) noexcept = default;
	Card& operator = (const Card&) noexcept = default;
	Card& operator = (Card&&) noexcept = default;

    [[nodiscard]] unsigned get_score() const noexcept;
    static bool equal_score(const Card&, const Card&);

    void set_suit(size_t value);
	void set_suit(const cardSuit& suit) noexcept { _suit = suit; }
    [[nodiscard]] const cardSuit& get_suit() const noexcept { return _suit; }

    void set_val(size_t value);
    void set_val(const cardValue& value) noexcept { _value = value; }
    [[nodiscard]] const cardValue& get_value() const noexcept { return _value; }
};

#endif
