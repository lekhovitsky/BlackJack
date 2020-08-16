#ifndef BASE_UI_HPP
#define BASE_UI_HPP

#include <memory>
#include <utility>
#include <vector>
#include <unordered_set>

#include "enums.hpp"
#include "account.hpp"
#include "dealer_box.hpp"
#include "player_box.hpp"

using AnswerSet = std::unordered_set<std::string>;


class BaseUI
{
protected:
    std::shared_ptr<Account>     account;
    std::shared_ptr<DealerBox>   dealer_box;
    std::shared_ptr<
        std::vector<PlayerBox>>  player_boxes;
public:
	BaseUI() = default;
	virtual ~BaseUI() = default;
	virtual void show_results() = 0;
	virtual void add_message(const std::string& message) = 0;
	virtual unsigned make_bet() = 0;
	virtual playerAnswer collect_answer(AnswerSet& answer_set) = 0;

    void set_pointers(Account *account_ptr,
                      DealerBox *dealer_box_ptr,
                      std::vector<PlayerBox> *player_boxes_ptr)
    {
        account.reset(account_ptr);
        dealer_box.reset(dealer_box_ptr);
        player_boxes.reset(player_boxes_ptr);
    }
};

#endif
