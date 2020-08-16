#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <cstddef>
#include <algorithm>


class Account
{
    size_t balance;
public:
    explicit Account(size_t initial_balance) : balance{initial_balance} {}

    [[nodiscard]] bool is_busted() const noexcept { return !balance; }
    [[nodiscard]] bool is_charge_possible(size_t amount) const noexcept { return balance > amount; }
    [[nodiscard]] size_t get_balance() const noexcept { return balance; }

    void charge(size_t amount) { balance -= std::min(amount, balance); }
    void pay(size_t amount) { balance += amount; }
};

#endif
