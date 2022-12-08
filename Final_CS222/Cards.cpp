#include <iostream>
#include "Cards.h"

Card::Card(int suit, int card_num) {
    this->suit = suit;
    this->card_num = card_num;
}

int Card::get_num() {
    return card_num;
}
int Card::get_suit() {
    return suit;
}

void Card::print() {
    std::cout
    << suit
    <<", "
    << card_num
    <<std::endl;
}