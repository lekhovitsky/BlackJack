template<class UI>
bool DealerBox<UI>::blackJack_is_possible() const
{
	return hand.size() == 1 &&
		(hand[0].get_value() == cardValue::Ace ||
                hand[0].get_score() == 10);
}

template<class UI>
void DealerBox<UI>::refreshStatus() noexcept
{
	status = boxStatus::InGame;
	if (score[0] > 21)
		status = boxStatus::Busted;
	else if (score[0] >= 17)
		status = boxStatus::Stand;
}

template<class UI>
void DealerBox<UI>::play(Boxes& box_vec)
{
	if (*(box_vec.cend() - 1) != shared_from_this())
		throw std::logic_error{
		"Vector doesn't contain the DealerBox."
	};

	if (hand.size() != 1)
		throw std::logic_error{
		"Dealer's hand must contain exactly one card at this step"
	};

	bool need_dealer_game{ false };

	for (auto& iter = box_vec.begin(); iter != box_vec.end() - 1; ++iter)
		if ((*iter)->getStatus() != boxStatus::Busted)
		{
			need_dealer_game = true;
			break;
		}

	takeCard();
	if (score[0] == 21)
	{
		status = boxStatus::BlackJack;
		return;
	}
	if (need_dealer_game)
		while (status == boxStatus::InGame) takeCard();
	else status = boxStatus::Stand;
}