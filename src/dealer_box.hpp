#ifndef DEALER_BOX_HPP
#define DEALER_BOX_HPP

#include "box.hpp"
#include <utility>


class DealerBox : public Box
{
public:
	explicit DealerBox(Shoes &_shoes) : Box{_shoes } {}

	void refresh_status() noexcept override;
	[[nodiscard]] bool is_blackjack_possible() const;
};

#endif
