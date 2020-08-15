#ifndef DEALER_BOX_HPP
#define DEALER_BOX_HPP

#include "box.hpp"
#include "person.hpp"
#include <utility>

using dealer_ptr = std::shared_ptr<Dealer>;


class DealerBox
        : public Box
{
protected:
	dealer_ptr dealer;
public:
	DealerBox(
	        dealer_ptr _dealer,
		    const shoes_ptr& _shoes
	)
		: Box{_shoes }
		, dealer{std::move(_dealer)} {}

	void refresh_status() noexcept override;
	[[nodiscard]] bool is_blackjack_possible() const;
};

#endif
