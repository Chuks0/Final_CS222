#pragma once
#include <vector>
#include "Cards.h"

class hands {
protected:
    std::vector<Card> hand;
public:
    hands();
    std::string to_format(const int number);
    std::string get_suit_string(int i);
    void add_card(Card);
    int get_number_of_cards();
    std::vector<Card> get_hand();
    void empty_hand();
    void print_hand(); 
};