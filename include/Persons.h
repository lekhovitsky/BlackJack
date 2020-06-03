#pragma once
#include <string>
#include <memory>

class Person
{
protected:
	std::string name;
public:
	Person(std::string _name)
		: name{ std::move(name) }
	{}
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
	unsigned sum;
public:
	Player(std::string _name, unsigned _sum = 1000)
		: Person{ _name }, sum(_sum)
	{}
	Player(const Player&) = delete;
	Player(Player&&) noexcept = default;
	// Добавляет к сумме игрока сумму reward
	Player& operator += (unsigned reward) noexcept;
	// Уменьшает сумму игрока на сумму bet или
	// до нуля, если это невозможно
	Player& operator -= (unsigned bet) noexcept;
	bool bet_is_possible(unsigned bet) const noexcept;
	unsigned getSum() const noexcept { return sum; }
	std::shared_ptr<unsigned> getSumPtr() noexcept 
	{ 
		static auto ptr = std::shared_ptr<unsigned>(&sum);
		return ptr;
	}
};
