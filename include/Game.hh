template<class UI,
	typename C = std::enable_if_t<
	std::is_base_of<BaseOuter, UI>::type
	>>
	bool Game<UI, C>::round()
{
	reset();
	box_vec = typename Box<UI>::Boxes{
		std::make_shared<PlayerBox<UI>>(player, shoes, outer),
		std::make_shared<DealerBox<UI>>(dealer, shoes, outer)
	};
	makeBet<UI>(dynamic_cast<PlayerBox<UI>*>(
		box_vec[0].get()
		));
	box_vec[0]->takeCard();
	box_vec[0]->takeCard();
	box_vec[1]->takeCard();
	// Через индексы, поскольку итераторы
	// могут стать невалидными при вставке
	// новых боксов в вектор
	for (unsigned i = 0; i < box_vec.size(); ++i)
		box_vec[i]->play(box_vec);

	auto dealer_status = box_vec[box_vec.size() - 1]->getStatus();
	auto dealer_score = box_vec[box_vec.size() - 1]->getScore();
	for (unsigned i = 0; i < box_vec.size() - 1; ++i)
		payReward<UI>(dynamic_cast<PlayerBox<UI>*>(
			box_vec[i].get()
			), dealer_status, dealer_score);
	outer->showResults();
	box_vec.clear();
	return static_cast<bool>(player->getSum());
}

template<class UI,
	typename C = std::enable_if_t<
	std::is_base_of<BaseOuter, UI>::type
	>>
	void Game<UI, C>::reset()
{
	if (shoes->needToReset())
	{
		shoes->reset();
	}
}