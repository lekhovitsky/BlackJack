template<class UI>
PlayerBox<UI>::PlayerBox(
	const player_ptr& _player, const shoes_ptr& _shoes,
	const outer_ptr<UI>& _outer, unsigned _bet = 0U,
	std::vector<Card>&& _cards = std::vector<Card>()
) : player{ _player }, bet{ _bet }, insurance{ 0 },
Box{ _shoes, _outer, std::move(_cards) }
{
	++PlayerBox<UI>::num_boxes;
}

template<class UI>
PlayerBox<UI>::~PlayerBox()
{
	--PlayerBox<UI>::num_boxes;
}

template<class UI>
bool PlayerBox<UI>::split_is_possible() const noexcept
{
	return hand.size() == 2 &&
		Card::same_score(hand[0], hand[1]) &&
		PlayerBox<UI>::num_boxes < 4 &&
		double_is_possible();
}

template<class UI>
bool PlayerBox<UI>::double_is_possible() const noexcept
{
	return hand.size() == 2 &&
		player->bet_is_possible(bet);
}

template<class UI>
bool PlayerBox<UI>::insurance_is_possible(
	const DealerBox<UI>& dealer) const noexcept
{
	return num_boxes == 1 &&
		dealer.blackJack_is_possible() &&
		player->bet_is_possible(bet / 2);
}

template<class UI>
void PlayerBox<UI>::play(Boxes& box_vec)
{
	/// Проверяем, что текущий бокс принадлежит массиву 
	/// и запоминаем его позицию
	auto pos = std::find(box_vec.cbegin(), box_vec.cend(), shared_from_this());
	if (pos == box_vec.cend()) throw std::logic_error{
		"Vector doesn't contain the box."
	};
	/// Проверяем, чтобы массив содержал строго один бокс дилера
	auto dealer_pos = std::find_if(box_vec.begin(), box_vec.end(),
		[](std::shared_ptr<Box<UI>> ptr)->bool
	{
		return (bool)dynamic_cast<DealerBox<UI>*>(ptr.get());
	});
	if (dealer_pos != box_vec.cend() - 1) throw std::logic_error{
		"Vector doesn't contain dealer's box or contains more than one."
	};
	/// Если у игрока с раздачи 21 очко, ставим соответствующий
	/// статус и выходим из метода
	if (isBlackJack())
	{
		status = boxStatus::BlackJack;
		return;
	}
	/// Формируем множество вариантов,
	/// из которого игрок сможет выбирать свое
	/// следующее действие
	std::unordered_set<std::string> answerSet{
		"Hit", "Stand"
	};
	if (split_is_possible()) answerSet.insert("Split");
	if (double_is_possible()) answerSet.insert("Double");
	if (insurance_is_possible(
		*(dynamic_cast<DealerBox<UI>*>((*dealer_pos).get()))
	)) answerSet.insert("Insure");
	/// Игра продолжается до тех пор, пока 
	/// на боксе стоит соответствующий статус.
	/// Иначе, игра на этом боксе завершена
	while (status == boxStatus::InGame)
	{
		/// "Собираем" следующий шаг игрока
		auto answer = outer->collectAnswer(answerSet);
		if (answer == playerAnswer::Split)
		{
			/// Добвляем в вектор после текущего лемента
			/// новый динамически созданный бокс, берем по карте
			auto next_pos = box_vec.emplace(pos + 1,
				std::make_shared<PlayerBox<UI>>(
					player, shoes, outer, bet,
					std::vector<Card>{ hand.back() }
			));
			hand.pop_back();
			takeCard();
			(*player) -= bet;
			(*next_pos)->takeCard();
			/// Рекурсивно вызываем метод play для текущего бокса
			play(box_vec);
			return;
		}
		else if (answer == playerAnswer::Double)
		{
			(*player) -= bet;
			bet *= 2;
			takeCard();
			return;
		}
		else if (answer == playerAnswer::Insurance)
		{
			insurance = bet / 2;
			(*player) -= insurance;
			/// После страховки игрок еще может
			/// разделить руку или удвоить ставку
			/// (наверное).
			answerSet.erase("Insure");
			continue;
		}
		else if (answer == playerAnswer::Hit)
		{
			takeCard();
		}
		else if (answer == playerAnswer::Stand)
		{
			status = boxStatus::Stand;
		}
		/// После первого хода (кроме страховки)
		/// игрок уже не может ни застраховаться,
		/// ни удвоить, ни разделить руку
		answerSet.erase("Split");
		answerSet.erase("Double");
		answerSet.erase("Insure");
	}
}

template<class UI>
void PlayerBox<UI>::makeBet()
{
	bet = outer->makeBet();
	(*player) -= bet;
}

template<class UI>
void PlayerBox<UI>::payReward(
	boxStatus dealer_status, unsigned dealer_score)
{
	float coef{ 0.0 }; std::string message{ "Lose" };
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
	outer->addMessage(message);
}

template<class UI>
void makeBet(PlayerBox<UI>* ptr)
{
	ptr->makeBet();
}

template<class UI>
void payReward(PlayerBox<UI>* ptr,
	boxStatus dealer_status, unsigned dealer_score)
{
	ptr->payReward(dealer_status, dealer_score);
}