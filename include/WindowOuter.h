#pragma once
#include <map>
#include "Box.h"
#include <memory>
#include "Button.h"
#include "Globals.h"
#include "BaseOuter.h"
#include <SFML/Graphics.hpp>

class WindowOuter :
	public BaseOuter
{
	sf::RenderWindow		window;
	sf::Sprite				backGround;
	sf::Font				fontOfText;
	std::map<std::string,
		sf::Button>			buttons;
	std::shared_ptr<
		unsigned>			playerSum;
	std::shared_ptr<
		typename Box<WindowOuter
	>::Boxes>				boxes;
	std::vector<
		std::string>		messages;
public:
	WindowOuter(const sf::Texture&, const sf::Font&);
	~WindowOuter();
	// функция с узким контрактом, передача неправильных аргументов может
	// разрушить программу,поэтому передавайте множество лишь допустимых
	// строк: "Hit", "Double", "Stand", "Split", "Insure".
	playerAnswer			collectAnswer(std::unordered_set<std::string>&) override;
	unsigned				makeBet() override;
	void					addMessage(const std::string&) override;
	void					showResults() override;

	void					drawMessages();
	void					drawElements();
	void					drawCard(const sf::Vector2f& pos, const Card& c);
	void					drawCard(const sf::Vector2f& pos);
	void					drawBox(const sf::Vector2f& pos, const Box<WindowOuter>& box);
	void					drawBoxes();
	void					drawBet(const std::string&);
	void					drawSum();

	template<typename T1, typename T2>
	void setBoxesAndSum(T1&& boxes_ptr, T2&& sum_ptr);
};

std::string getCardImageFileName(const Card& c);
template<typename T1, typename T2>
void WindowOuter::setBoxesAndSum(T1&& boxes_ptr, T2&& sum_ptr)
{
	boxes = std::forward<std::shared_ptr<typename Box<WindowOuter>::Boxes>>(boxes_ptr);
	playerSum = std::forward<std::shared_ptr<unsigned>>(sum_ptr);
}
