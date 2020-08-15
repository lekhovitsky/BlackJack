#ifndef GUI_HPP
#define GUI_HPP

#include <map>
#include "box.hpp"
#include <memory>
#include "button.hpp"
#include "globals.hpp"
#include "ui.hpp"
#include <SFML/Graphics.hpp>


std::string getCardImageFileName(const Card& c);


class GUI :
	public BaseUI
{
    using Boxes = typename Box::Boxes;
	sf::RenderWindow		  window;
	sf::Sprite				  backGround;
	sf::Font				  fontOfText;
	std::map<std::string,
		sf::Button>			  buttons;
	std::vector<std::string>  messages;
    std::shared_ptr<unsigned> balance;
    std::shared_ptr<Boxes>	  boxes;
public:
	GUI(const sf::Texture& texture, const sf::Font& font);
	~GUI() override;

	playerAnswer			collect_answer(std::unordered_set<std::string>&) override;
	unsigned				make_bet() override;
	void					add_message(const std::string&) override;
	void					show_results() override;

	void					draw_messages();
	void					draw_elements();
	void					draw_card(const sf::Vector2f& pos, const Card& c);
	void					draw_card(const sf::Vector2f& pos);
	void					draw_box(const sf::Vector2f& pos, const Box& box);
	void					draw_boxes();
	void					draw_bet(const std::string&);
	void					draw_balance();

	template<typename T1, typename T2>
	void setBoxesAndSum(T1&& boxes_ptr, T2&& sum_ptr);
};

template<typename T1, typename T2>
void GUI::setBoxesAndSum(T1&& boxes_ptr, T2&& sum_ptr)
{
	boxes = std::forward<std::shared_ptr<Boxes>>(boxes_ptr);
    balance = std::forward<std::shared_ptr<unsigned>>(sum_ptr);
}

#endif
