#include "player_box.hpp"


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
            player->is_bet_possible(bet);
}

bool PlayerBox::is_insurance_possible(
	const DealerBox& dealer) const noexcept
{
	return num_boxes == 1 &&
            dealer.is_blackjack_possible() &&
            player->is_bet_possible(bet / 2);
}

void PlayerBox::make_bet()
{
	(*player) -= bet;
}

void PlayerBox::pay_reward(boxStatus dealer_status, unsigned dealer_score)
{
	float coef{ 0.0 };
	std::string message{ "Lose" };
	if (status == boxStatus::BlackJack)
	{
		coef = 2.5; message = "BlackJack!";
	}
	else if (status == boxStatus::Stand &&
		(score[0] > dealer_score ||
			dealer_status == boxStatus::Busted))
	{
		coef = 2.0; message = "Won!";
	}
	else if (score[0] == dealer_score &&
		status == boxStatus::Stand &&
		dealer_status == boxStatus::Stand)
	{
		coef = 1.0; message = "Pushed.";
	}
	if (status == boxStatus::Busted) message = "Busted!";
	(*player) += coef * bet;
	if (dealer_status == boxStatus::BlackJack && insurance)
	{
		(*player) += 2 * insurance; message += ". Insured!";
	}
	// ui->add_message(message);
}
