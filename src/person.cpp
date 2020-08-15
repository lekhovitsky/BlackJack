#include "person.hpp"

Player& Player::operator+=(unsigned reward) noexcept
{
    balance += reward;
	return *this;
}

Player& Player::operator-=(unsigned bet) noexcept
{
    balance = (bet < balance) ? balance - bet : 0;
	return *this;
}

