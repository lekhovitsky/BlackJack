#ifndef BASE_UI_HPP
#define BASE_UI_HPP

#include "enums.hpp"
#include <unordered_set>


class BaseUI
{
public:
	BaseUI() = default;
	virtual ~BaseUI() = default;
	virtual void show_results() = 0;
	virtual void add_message(const std::string& message) = 0;
	virtual unsigned make_bet() = 0;
	virtual playerAnswer collect_answer(
		std::unordered_set<std::string>& answerSet) = 0;
};

#endif
