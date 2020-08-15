#include <sstream>
#include "gui.hpp"


GUI::GUI(const sf::Texture& texture, const sf::Font& font)
	: window{ sf::VideoMode{ 1136, 640 }, "BlackJack Application" }
	, backGround{ texture }
	, fontOfText{ font }
	, buttons{
		std::make_pair("Hit", sf::Button{sf::Vector2f{ 50, 480 }, GLOBALS::BUTTON_SIZE, "Hit", font }),
		std::make_pair("Stand", sf::Button{sf::Vector2f{ 50, 560 }, GLOBALS::BUTTON_SIZE, "Stand", font }),
		std::make_pair("Double", sf::Button{sf::Vector2f{ 986, 480 }, GLOBALS::BUTTON_SIZE, "Double", font }),
		std::make_pair("Split", sf::Button{sf::Vector2f{ 986, 560 }, GLOBALS::BUTTON_SIZE, "Split", font }),
		std::make_pair("Insure", sf::Button{sf::Vector2f{ 350, 560 }, GLOBALS::BUTTON_SIZE, "Insure", font }),
		std::make_pair("OK",  sf::Button{sf::Vector2f{ 686, 560 }, GLOBALS::BUTTON_SIZE, "OK", font })
	}
{}

GUI::~GUI()
{
    if (window.isOpen()) window.close();
	exit(0);
}

playerAnswer GUI::collect_answer(
	std::unordered_set<std::string>& answerSet)
{
	while (window.isOpen())
	{
		window.clear();
        draw_elements();
		window.display();
		sf::Event ev{};
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				for (auto& answer : answerSet)
				{
					if (buttons[answer].contains(sf::Mouse::getPosition(window))
						&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
						return GLOBALS::_strAnswMap[answer];
				}
			}
			if (ev.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
	}
}

unsigned GUI::make_bet()
{
	std::string str;
	unsigned num{ 0 };
	while (window.isOpen())
	{
		window.clear();
        draw_elements();
        draw_bet(str);
		window.display();
		sf::Event ev{};
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::TextEntered)
			{
				if (ev.text.unicode >= 48 && ev.text.unicode <= 57
					&& 10 * num + ev.text.unicode - 48 <= *balance)
				{
					num = 10 * num + ev.text.unicode - 48;
					str += ev.text.unicode;
				}
			}
			if (ev.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)
					&& str.length())
				{
					str.pop_back();
					num /= 10;
				}
			}
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				if (buttons["OK"].contains(sf::Mouse::getPosition(window))
					&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && num)
				{
					return num;
				}
			}
			if (ev.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
	}
}

void GUI::add_message(const std::string& message)
{
	messages.emplace_back(message);
}

void GUI::show_results()
{
	while (window.isOpen())
	{
		window.clear();
        draw_elements();
        draw_messages();
		window.display();
		sf::Event ev{};
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				if (buttons["OK"].contains(sf::Mouse::getPosition(window))
					&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					messages.clear();
					return;
				}
			}
			if (ev.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
	}
}

void GUI::draw_messages()
{
	auto size = messages.size();
	if (size != boxes->size() - 1)
	{
		throw std::logic_error{ "Something's gone wrong" };
	}
	for (unsigned i = 0; i < size; ++i)
	{
		auto text = sf::Text{ messages[i], fontOfText };
		text.setPosition(sf::Vector2f{
                GLOBALS::TABLE_SIZE.x / (size + 1) * (i + 1) - 72,
                GLOBALS::_playerBoxLineY - 30
		});
		window.draw(text);
	}
}

void GUI::draw_elements()
{
	window.draw(backGround);
	for (auto& pair : buttons)
	{
		window.draw(pair.second);
	}
    draw_boxes();
    draw_balance();
}

void GUI::draw_card(const sf::Vector2f& pos, const Card& c)
{
	sf::Texture texture;
	if (!texture.loadFromFile(getCardImageFileName(c))) { exit(1); }
	sf::Sprite cardSprite{ texture };
	cardSprite.setPosition(pos);
	window.draw(cardSprite);
}

void GUI::draw_card(const sf::Vector2f& pos)
{
	sf::Texture texture;
	if (!texture.loadFromFile(GLOBALS::CARD_BACK_FILE)) { exit(1); }
	sf::Sprite cardSprite{ texture };
	cardSprite.setPosition(pos);
	window.draw(cardSprite);
}

void GUI::draw_box(const sf::Vector2f& pos, const Box& box)
{
	auto hand_copy = box.get_hand();
	auto score = box.get_score();
	auto num_cards = hand_copy.size();
	for (unsigned i = 0; i < num_cards; ++i)
	{
        draw_card(sf::Vector2f{
                pos.x + i * GLOBALS::_cardOffset, pos.y
        }, hand_copy[i]);
	}
	std::ostringstream score_stream;
	score_stream << "Score: " << score;
	sf::Text text{ score_stream.str(), fontOfText };
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f{ pos.x, pos.y + GLOBALS::CARD_SIZE.y });
	if(num_cards) window.draw(text);
}

void GUI::draw_boxes()
{
	auto num_boxes = boxes->size();
	if (num_boxes == 0) return;
	for (unsigned i = 0; i < num_boxes - 1; ++i)
	{
        draw_box(sf::Vector2f{
                GLOBALS::TABLE_SIZE.x / num_boxes * (i + 1) - 72,
                GLOBALS::_playerBoxLineY
        }, *(*boxes)[i]);
	}
	if ((*boxes)[num_boxes - 1]->get_hand().size() == 1)
	{
        draw_card(sf::Vector2f{
                GLOBALS::TABLE_SIZE.x / 2 - GLOBALS::_cardOffset - 72,
                GLOBALS::_dealerBoxLineY
        });
	}
    draw_box(sf::Vector2f{
            GLOBALS::TABLE_SIZE.x / 2 - 72,
            GLOBALS::_dealerBoxLineY
    }, *(*boxes)[num_boxes - 1]);
}

void GUI::draw_bet(const std::string& bet)
{
	std::string str{ "Bet:  " };
	str += bet;
	sf::Text text{ str, fontOfText };
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f{ 50, 90 });
	window.draw(text);
}

void GUI::draw_balance()
{
	std::ostringstream stream;
	stream << "Balance: " << *balance;
	sf::Text text{ stream.str(), fontOfText };
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f{ 50, 60 });
	window.draw(text);
}

std::string getCardImageFileName(const Card& c)
{
	std::ostringstream filename;
	filename << "../assets/";
	auto val = c.get_value();
	switch (val)
	{
	case cardValue::Ace:
		filename << "A";
		break;
	case cardValue::King:
		filename << "K";
		break;
	case cardValue::Queen:
		filename << "Q";
		break;
	case cardValue::Jack:
		filename << "J";
		break;
	default:
		filename << static_cast<short>(val);
		break;
	}
	auto suit = c.get_suit();
	switch (suit)
	{
	case cardSuit::Spades:
		filename << "S";
		break;
	case cardSuit::Hearts:
		filename << "H";
		break;
	case cardSuit::Clubs:
		filename << "C";
		break;
	case cardSuit::Diamonds:
		filename << "D";
		break;
	}
	filename << ".png";
	return filename.str();
}