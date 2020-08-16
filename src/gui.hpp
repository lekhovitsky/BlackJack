#ifndef GUI_HPP
#define GUI_HPP

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "ui.hpp"
#include "button.hpp"
#include "globals.hpp"


class GUI :	public BaseUI
{
	sf::RenderWindow		  window;
	sf::Sprite				  backGround;
	sf::Font				  font;
	std::map<
	    std::string, sf::Button
	    >       			  buttons;
	std::vector<std::string>  messages;
public:
	GUI(const sf::Texture& texture, const sf::Font& font);
	~GUI() override;

	playerAnswer			collect_answer(AnswerSet&) override;
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
};

#endif
