template<typename UI, typename C>
Game<UI, C>::Game(ui_ptr<UI>& ui, size_t initial_balance, size_t num_decks)
    : ui{ui}
    , account{ initial_balance }
    , shoes{ num_decks }
    , dealer_box{ shoes }
{
    ui->set_pointers(&account, &dealer_box, &player_boxes);
    player_boxes.reserve(4);
}

template<typename UI, typename C>
bool Game<UI, C>::round()
{
    reset();
    auto bet = ui->make_bet();
    account.charge(bet);
    player_boxes.emplace_back(account, shoes, bet);

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

    for (auto& box : player_boxes)
        result(box);

    display_results();

    // can play until player has some money
    return !account.is_busted();
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
    auto pos = std::find_if(
            player_boxes.begin(),
            player_boxes.end(),
            [&box](auto& b) { return &box == &b; });
    if (pos == player_boxes.cend())
        throw std::logic_error{"Vector doesn't contain the box."};

    if (box.blackjack())
    {
        box.status = boxStatus::BlackJack;
        return;
    }

    // form an answer set to choose from on the next step
    std::unordered_set<std::string> answers{
        "Hit",
        "Stand"
    };
    if (box.is_split_possible()) answers.insert("Split");
    if (box.is_double_possible()) answers.insert("Double");
    if (box.is_insurance_possible(dealer_box)) answers.insert("Insure");

    while (box.in_game())
    {
        auto answer = ui->collect_answer(answers);
        if (answer == playerAnswer::Hit)
        {
            box.play_hit();
        }
        else if (answer == playerAnswer::Stand)
        {
            box.play_stand();
        }
        else if (answer == playerAnswer::Double)
        {
            box.play_double();
            // stop taking cords immediately after doubling
            return;
        }
        else if (answer == playerAnswer::Insure)
        {
            box.play_insure();
            // after insurance, we still can
            // do Double Down or Split
            answers.erase("Insure");
            continue;
        }
        else if (answer == playerAnswer::Split)
        {
            auto new_pos = player_boxes.emplace(pos+1, box.play_split());
            players_move(box);
            return;
        }
        // after the first move, the player
        // cannot split, double or insure
        answers.erase("Split");
        answers.erase("Double");
        answers.erase("Insure");
    }
}

template<typename UI, typename C>
void Game<UI, C>::display_results()
{
    ui->show_results();
}

template <typename UI, typename C>
void Game<UI, C>::result(PlayerBox & box)
{
    float coef{ 0. };
    std::string message{ "Lost!" };

    if (box.blackjack())
    {
        coef = 2.5; message = "BlackJack!!!";
    }
    else if (box.busted())
    {
        coef = 0.; message = "Busted!";
    }
    else if (box.get_status() == boxStatus::Stand &&
             (box.get_score() > dealer_box.get_score() ||
              dealer_box.busted()))
    {
        coef = 2.0; message = "Won!";
    }
    else if (box.get_score() == dealer_box.get_score() &&
             box.get_status() == boxStatus::Stand &&
             dealer_box.get_status() == boxStatus::Stand)
    {
        coef = 1.0; message = "Draw.";
    }
    account.pay(coef * box.get_bet_size());

    auto insurance = box.get_insurance_size();
    if (dealer_box.blackjack() && insurance)
    {
        account.pay(2 * insurance); message += ". Insured!";
    }
    ui->add_message(message);
}


template<typename UI, typename C>
void Game<UI, C>::reset()
{
    player_boxes.clear();
    dealer_box.reset();
    if (shoes.is_reset_needed())
        shoes.reset();
}
