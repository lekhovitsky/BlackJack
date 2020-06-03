#pragma once
#include "enums.hpp"
#include <unordered_set>

// Interface
class BaseOuter
{
public:
	BaseOuter() {}
	virtual ~BaseOuter() = default;
	virtual void showResults() = 0;
	virtual void addMessage(const std::string& message) = 0;
	virtual unsigned makeBet() = 0;
	virtual playerAnswer collectAnswer(
		std::unordered_set<std::string>& answerSet) = 0;
};