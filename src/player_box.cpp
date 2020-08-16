#include "player_box.hpp"
#include <cmath>


PlayerBox::PlayerBox(
        Account &_account,
        Shoes &_shoes,
        size_t _bet,
        std::vector<Card> _cards
)
    : Box{ _shoes, std::move(_cards) }
    , account{ _account }
    , bet{ _bet }
    , insurance{ 0 }
{
    ++PlayerBox::num_boxes;
}

PlayerBox::PlayerBox(const PlayerBox& other) noexcept
    : Box{other.shoes, other.hand}
    , account{other.account}
    , bet{ other.bet }
    , insurance{ other.insurance }
{
    ++PlayerBox::num_boxes;
}

PlayerBox& PlayerBox::operator=(const PlayerBox& other) noexcept
{
    if(&other == this)
        return *this;

    shoes = other.shoes;
    account = other.account;
    bet = other.bet;
    insurance = other.insurance;
    ++PlayerBox::num_boxes;
    return *this;
}

PlayerBox::~PlayerBox()
{
	--PlayerBox::num_boxes;
}

bool PlayerBox::is_split_possible() const noexcept
{
	return hand.size() == 2 &&
            Card::equal_score(hand[0], hand[1]) &&
            PlayerBox::num_boxes < 4 &&
            is_double_possible();
}

bool PlayerBox::is_double_possible() const noexcept
{
	return hand.size() == 2 &&
            account.is_charge_possible(bet);
}

bool PlayerBox::is_insurance_possible(
	const DealerBox& dealer) const noexcept
{
	return num_boxes == 1 &&
            dealer.is_blackjack_possible() &&
            account.is_charge_possible(bet / 2);
}

void PlayerBox::play_hit()
{
    take_card();
}

void PlayerBox::play_stand()
{
    set_status(boxStatus::Stand);
}

void PlayerBox::play_double()
{
    account.charge(bet);
    bet *= 2;
    take_card();
}

void PlayerBox::play_insure()
{
    insurance = bet / 2;
    account.charge(insurance);
}


PlayerBox PlayerBox::play_split()
{
    account.charge(bet);
    PlayerBox box {account, shoes, bet, {hand.back()}};
    hand.pop_back();
    take_card();
    box.take_card();
    return box;
}
