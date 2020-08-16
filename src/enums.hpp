#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class cardSuit : short
{
    Spades = 1, Hearts,
    Clubs, Diamonds
};

enum class cardValue : short
{
    Ace = 1, Two, Three, Four,
    Five, Six, Seven, Eight,
    Nine, Ten, Jack, Queen, King,
};

enum class boxStatus : short
{
    BlackJack, Stand,
    Busted, InGame
};

enum class playerAnswer : short
{
    Split, Stand,
    Hit, Double,
    Insure
};

#endif
