#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <memory>
#include <utility>


class Person
{
protected:
	std::string name;
public:
	explicit Person(std::string _name)
		: name{ std::move(_name) } {}
	Person(const Person&) = delete;
	Person(Person&&) noexcept = default;
	virtual ~Person() = default;
};

class Dealer
	: public Person
{
public:
	Dealer()
		: Person("Dealer")
	{}
	Dealer(const Dealer&) = delete;
	Dealer(Dealer&&) noexcept = default;
};

class Player
	: public Person
{
protected:
	unsigned balance;
public:
	explicit Player(unsigned initial_balance = 1000)
		: Person{"Player"}, balance{initial_balance} {}
	Player(const Player&) = delete;
	Player(Player&&) noexcept = default;

	// TODO: zochem???
	Player& operator += (unsigned reward) noexcept;
	Player& operator -= (unsigned bet) noexcept;

	[[nodiscard]] bool is_busted() const noexcept { return balance > 0; }
	[[nodiscard]] bool is_bet_possible(unsigned bet) const noexcept { return bet <= balance; }
    [[nodiscard]] unsigned get_balance() const noexcept { return balance; }
};

#endif
