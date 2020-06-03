#include "Persons.h"

Player& Player::operator+=(unsigned award) noexcept
{
	sum += award;
	return *this;
}

Player& Player::operator-=(unsigned bet) noexcept
{
	sum = (bet < sum) ? sum - bet : 0;
	return *this;
}

bool Player::bet_is_possible(unsigned bet) const noexcept
{
	return bet <= sum;
}
