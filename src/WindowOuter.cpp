#include <sstream>
#include "WindowOuter.h"

WindowOuter::WindowOuter(const sf::Texture& texture, const sf::Font& font)
	: window{ sf::VideoMode{ 1136, 640 }, "BlackJack Application" }, 
	buttons{ 
		std::make_pair("Hit", sf::Button{ sf::Vector2f{ 50, 480 }, Globals::_standardButtonSize, "Hit", font }),
		std::make_pair("Stand", sf::Button{ sf::Vector2f{ 50, 560 }, Globals::_standardButtonSize, "Stand", font }),
		std::make_pair("Double", sf::Button{ sf::Vector2f{ 986, 480 }, Globals::_standardButtonSize, "Double", font }),
		std::make_pair("Split", sf::Button{ sf::Vector2f{ 986, 560 }, Globals::_standardButtonSize, "Split", font }),
		std::make_pair("Insure", sf::Button{ sf::Vector2f{ 350, 560 }, Globals::_standardButtonSize, "Insure", font }),
		std::make_pair("OK",  sf::Button{ sf::Vector2f{ 686, 560 }, Globals::_standardButtonSize, "OK", font })
	}
{
	backGround.setTexture(texture);
	fontOfText = font;
}

WindowOuter::~WindowOuter()
{
	/// ��� ��� ����� ��� �������� ����� ���� ���� ��� ����� ���������
	/// �������, � ����� � ������� ����������� ���������������� ����������
	/// � ������������� ��������, ���� ������� ������� �������� �����������
	/// ��������� � ���� ����������� ���� - ������� ��� ����� ����� �����������
	if (window.isOpen()) window.close();
	exit(0);
}

playerAnswer WindowOuter::collectAnswer(
	std::unordered_set<std::string>& answerSet)
{
	while (window.isOpen())
	{
		window.clear();
		drawElements();
		window.display();
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				for (auto& answer : answerSet)
				{
					if (buttons[answer].contains(sf::Mouse::getPosition(window))
						&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
						return Globals::_strAnswMap[answer];
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

unsigned WindowOuter::makeBet()
{
	std::string str;
	unsigned num{ 0 };
	while (window.isOpen())
	{
		window.clear();
		drawElements();
		drawBet(str);
		window.display();
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::TextEntered)
			{
				if (ev.text.unicode >= 48 && ev.text.unicode <= 57
					&& 10 * num + ev.text.unicode - 48 <= *playerSum)
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

void WindowOuter::addMessage(const std::string& message)
{
	messages.emplace_back(message);
}

void WindowOuter::showResults()
{
	while (window.isOpen())
	{
		window.clear();
		drawElements();
		drawMessages();
		window.display();
		sf::Event ev;
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

void WindowOuter::drawMessages()
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
			Globals::_tableSize.x / (size + 1) * (i + 1) - 72,
			Globals::_playerBoxLineY - 30
		});
		window.draw(text);
	}
}

void WindowOuter::drawElements()
{
	window.draw(backGround);
	for (auto& pair : buttons)
	{
		window.draw(pair.second);
	}
	drawBoxes();
	drawSum();
}

void WindowOuter::drawCard(const sf::Vector2f& pos, const Card& c)
{
	sf::Texture texture;
	if (!texture.loadFromFile(getCardImageFileName(c))) { exit(1); }
	sf::Sprite cardSprite{ texture };
	cardSprite.setPosition(pos);
	window.draw(cardSprite);
}

void WindowOuter::drawCard(const sf::Vector2f& pos)
{
	sf::Texture texture;
	if (!texture.loadFromFile(Globals::_cardBackImageFileName)) { exit(1); }
	sf::Sprite cardSprite{ texture };
	cardSprite.setPosition(pos);
	window.draw(cardSprite);
}

void WindowOuter::drawBox(const sf::Vector2f& pos, const Box<WindowOuter>& box)
{
	auto hand_copy = box.getHand();
	auto score = box.getScore();
	auto num_cards = hand_copy.size();
	for (unsigned i = 0; i < num_cards; ++i)
	{
		drawCard(sf::Vector2f{
			pos.x + i * Globals::_cardOffset, pos.y 
		}, hand_copy[i]);
	}
	std::ostringstream score_stream;
	score_stream << "Score: " << score;
	sf::Text text{ score_stream.str(), fontOfText };
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f{ pos.x, pos.y + Globals::_cardSize.y });
	if(num_cards) window.draw(text);
}

void WindowOuter::drawBoxes()
{
	auto num_boxes = boxes->size();
	if (num_boxes == 0) return;
	for (unsigned i = 0; i < num_boxes - 1; ++i)
	{
		drawBox(sf::Vector2f{ 
			Globals::_tableSize.x / num_boxes * (i + 1) - 72, 
			Globals::_playerBoxLineY 
		}, *(*boxes)[i]);
	}
	if ((*boxes)[num_boxes - 1]->getHand().size() == 1)
	{
		drawCard(sf::Vector2f{ 
			Globals::_tableSize.x / 2 - Globals::_cardOffset - 72, 
			Globals::_dealerBoxLineY
		});
	}
	drawBox(sf::Vector2f{
		Globals::_tableSize.x / 2 - 72,
		Globals::_dealerBoxLineY
	}, *(*boxes)[num_boxes - 1]);
}

void WindowOuter::drawBet(const std::string& bet)
{
	std::string str{ "Bet:  " };
	str += bet;
	sf::Text text{ str, fontOfText };
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f{ 50, 90 });
	window.draw(text);
}

void WindowOuter::drawSum()
{
	std::ostringstream stream;
	stream << "Sum: " << *playerSum;
	sf::Text text{ stream.str(), fontOfText };
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f{ 50, 60 });
	window.draw(text);
}

std::string getCardImageFileName(const Card& c)
{
	std::ostringstream filename;
	filename << "assets\\";
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