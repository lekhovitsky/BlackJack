#pragma once
#include "Box.h"
#include "Persons.h"

using dealer_ptr = std::shared_ptr<Dealer>;

template<class UI>
class DealerBox :
	public Box<UI>
{
protected:
	dealer_ptr dealer;
public:
	DealerBox(const dealer_ptr& _dealer,
		const shoes_ptr& _shoes,
		const outer_ptr<UI>& _outer)
		: dealer{ _dealer }, Box{ _shoes, _outer }
	{}

	void play(Boxes&) override;
	void refreshStatus() noexcept override;
	bool blackJack_is_possible() const;
};

/// -------Реализация шаблонных методов-------
#include "DealerBox.hh"