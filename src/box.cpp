#include "box.hpp"


void Box::take_card() noexcept
{
	try
	{
		hand.emplace_back(shoes->get_card());
        refresh_score();
        refresh_status();
	}
	catch (std::runtime_error& e)
	{
		std::clog << "Runtime error: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Something's wrong: " << e.what() << std::endl;
	}
}

void Box::reset()
{
    status = boxStatus::InGame;
    hand.clear();
}

void Box::refresh_score() noexcept
{
	score[0] = score[1] = 0;
	for (const auto& card : hand)
	{
		if (card.get_value() == cardValue::Ace)
		{
			if(score[0] > 11) score[1] += 10;
			score[0] += 10;
		}
		score[0] += card.get_score();
		score[1] += card.get_score();
	}
	if (score[0] > 21 && score[1])
	{
		score[0] = score[1];
		score[1] = 0;
	}
	else if (score[0] == 21)
	{
		score[1] = 0;
	}
}

void Box::refresh_status() noexcept
{
	status = boxStatus::InGame;
	if (score[0] > 21)
		status = boxStatus::Busted;
	else if (score[0] == 21)
	    status = hand.size() == 2
	            ? boxStatus::BlackJack
	            : boxStatus::Stand;
}
