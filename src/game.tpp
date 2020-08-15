template<typename UI, typename C>
bool Game<UI, C>::round()
{
	reset();
    player_boxes.emplace_back(player, shoes);
    player_boxes[0].make_bet(ui->make_bet());

    // two cards for a player
    player_boxes[0].take_card();
    player_boxes[0].take_card();

    // one card for a dealer
	dealer_box.take_card();

    // boxes may be added during the round,
    // so no iterators / for (auto e : arr)
	for (size_t i = 0; i < player_boxes.size(); ++i)
        players_move(player_boxes[i]);

	dealers_move();
	auto dealer_status = dealer_box.get_status();
	auto dealer_score = dealer_box.get_score();

	for (auto& box : player_boxes)
	    box.pay_reward(dealer_status, dealer_score);

    display_results();

	// can play until player has some money
	return !player->is_busted();
}

template<typename UI, typename C>
void Game<UI, C>::dealers_move()
{
    // take one card, check for BlackJack
    dealer_box.take_card();
    if (dealer_box.blackjack()) return;

    // if not BlackJack and there is at least one
    // not busted player's box, dealer will start
    // taking cards
    bool is_dealer_move_needed{false};
    for (const auto& box : player_boxes)
        if (!box.busted()) is_dealer_move_needed = true;

    if (!is_dealer_move_needed)
    {
        dealer_box.set_status(boxStatus::Stand);
        return;
    }

    while (dealer_box.in_game())
        dealer_box.take_card();
}

template<typename UI, typename C>
void Game<UI, C>::players_move(PlayerBox& box)
{
    auto pos = std::find(
            player_boxes.cbegin(),
            player_boxes.cend(),
            box);
    if (pos == player_boxes.cend())
        throw std::logic_error{"Vector doesn't contain the box."};

    if (box.blackjack())
    {
        box.status = boxStatus::BlackJack;
        return;
    }

    // form an answer set to choose from on the next step
    std::unordered_set<std::string> answerSet{
        "Hit",
        "Stand"
    };
    if (box.is_split_possible()) answerSet.insert("Split");
    if (box.is_double_possible()) answerSet.insert("Double");
    if (box.is_insurance_possible(dealer_box)) answerSet.insert("Insure");

    /// Игра продолжается до тех пор, пока
    /// на боксе стоит соответствующий статус.
    /// Иначе, игра на этом боксе завершена
    while (box.in_game())
    {
        auto answer = ui->collect_answer(answerSet);
        if (answer == playerAnswer::Split)
        {
            /// Добвляем в вектор после текущего лемента
            /// новый динамически созданный бокс, берем по карте
            auto next_pos = player_boxes.emplace(pos + 1,
                                          std::make_shared<PlayerBox>(
                                                  player, shoes, box.bet,
                                                  std::vector<Card>{ box.hand.back() }
                                          ));
            box.hand.pop_back();
            box.take_card();
            (*player) -= box.bet;
            (*next_pos)->take_card();
            /// Рекурсивно вызываем метод round для текущего бокса
            players_move(box);
            return;
        }
        else if (answer == playerAnswer::Double)
        {
            (*player) -= box.bet;
            box.bet *= 2;
            box.take_card();
            return;
        }
        else if (answer == playerAnswer::Insurance)
        {
            box.insurance = box.bet / 2;
            (*player) -= box.insurance;
            /// После страховки игрок еще может
            /// разделить руку или удвоить ставку
            /// (наверное).
            answerSet.erase("Insure");
            continue;
        }
        else if (answer == playerAnswer::Hit)
        {
            box.take_card();
        }
        else if (answer == playerAnswer::Stand)
        {
            box.set_status(boxStatus::Stand);
        }
        /// После первого хода (кроме страховки)
        /// игрок уже не может ни застраховаться,
        /// ни удвоить, ни разделить руку
        answerSet.erase("Split");
        answerSet.erase("Double");
        answerSet.erase("Insure");
    }
}

template<typename UI, typename C>
void Game<UI, C>::display_results()
{
    ui->show_results();
}

template<typename UI, typename C>
void Game<UI, C>::reset()
{
    player_boxes.clear();
    dealer_box.reset();
    if (shoes->is_reset_needed())
	    shoes->reset();
}
