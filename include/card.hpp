#pragma once
#include "enums.hpp"
#include <type_traits>
#include <stdexcept>

#define NUM_VALUES 13
#define NUM_SUITS 4

class Card {
    cardValue	_value;
	cardSuit	_suit;
public:
	Card(cardValue value, cardSuit suit) noexcept
		: _value{value }, _suit{suit } {}

    template<typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    explicit Card(const T& t_card) noexcept
            : _suit{static_cast<cardSuit>(t_card % NUM_SUITS + 1) }
            , _value{static_cast<cardValue>(t_card % NUM_VALUES + 1) } {}

	Card(Card&&) noexcept = default;
	Card(const Card&) noexcept = default;
	Card& operator = (const Card&) noexcept = default;
	Card& operator = (Card&&) noexcept = default;

	[[nodiscard]] unsigned get_score() const noexcept;
	[[nodiscard]] const cardSuit& get_suit() const noexcept { return _suit; }
	[[nodiscard]] const cardValue& get_value() const noexcept { return _value; }

    void set_suit(const cardSuit& suit) noexcept;
    template<typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
    void set_suit(const T& t_suit) {
        if (t_suit >= NUM_SUITS)
            throw std::invalid_argument { "For success cast value must be from 1 to 4" };
        _suit = static_cast<cardSuit>(t_suit);
    }

    void set_val(const cardValue& value) noexcept;
    template<typename T, typename = std::enable_if_t <std::is_unsigned_v<T>>>
    void set_val(const T& t_value) {
        if (t_value == 0 || t_value > NUM_VALUES)
            throw std::invalid_argument { "For success cast value must be from 1 to 13" };
        _value = static_cast<cardValue>(t_value);
    }


    static bool same_score(const Card&, const Card&);
};
