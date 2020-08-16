#include "dealer_box.hpp"


bool DealerBox::is_blackjack_possible() const
{
    // if there is only one opened card, and
    // it is one of Jack, Queen, King or Ace
    return hand.size() == 1 && (
            hand[0].get_score() == 1 ||
            hand[0].get_score() == 10);
}

void DealerBox::refresh_status() noexcept
{
    Box::refresh_status();
    if (!blackjack() && !busted() && score[0] >= 17)
        status = boxStatus::Stand;
}
