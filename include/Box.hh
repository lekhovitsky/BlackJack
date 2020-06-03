template<class UI>
void Box<UI>::takeCard() noexcept
{
	try
	{
		hand.emplace_back(
			shoes->getCard());
		refreshScore();
		refreshStatus();
	}
	catch (std::runtime_error& e)
	{
		std::clog << "Runtime error: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Something wrong: " << e.what() << std::endl;
	}
}

template<class UI>
void Box<UI>::refreshScore() noexcept
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

template<class UI>
void Box<UI>::refreshStatus() noexcept
{
	status = boxStatus::InGame;
	if (score[0] > 21)
		status = boxStatus::Busted;
	else if (score[0] == 21)
		status = boxStatus::Stand;
}

template<class UI>
bool Box<UI>::isBlackJack() const noexcept
{
	return (hand.size() == 2 && score[0] == 21);
}