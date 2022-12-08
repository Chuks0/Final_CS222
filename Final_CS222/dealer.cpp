#include "dealer.h" 
#include <iostream>


dealer::dealer() : player() {

}

void dealer::generate_dealer_hand(std::vector<Card>& deck) {
    switch (player_hand.get_number_of_cards()) {
    case 0:
        while (player_hand.get_number_of_cards() < 3) {
            int card_index = (rand() % static_cast<int>(deck.size()));
            Card new_card(deck[card_index].get_suit(), deck[card_index].get_num());
            player_hand.add_card(new_card);
            deck.erase(deck.begin() + card_index);
        }
        break;
    default:
        int card_index = (rand() % static_cast<int>(deck.size()));
        Card new_card(deck[card_index].get_suit(), deck[card_index].get_num());
        player_hand.add_card(new_card);
        deck.erase(deck.begin() + card_index);
        break;
    }
}

void dealer::add_dealer_card(std::vector<Card>& deck, int total_card) {
    switch (player_hand.get_number_of_cards()) {
    case 0:
        while (player_hand.get_number_of_cards() < total_card) {
            int card_index = (rand() % static_cast<int>(deck.size()));
            Card new_card(deck[card_index].get_suit(), deck[card_index].get_num());
            player_hand.add_card(new_card);
            deck.erase(deck.begin() + card_index);
        }
        break;
    default:
        int card_index = (rand() % static_cast<int>(deck.size()));
        Card new_card(deck[card_index].get_suit(), deck[card_index].get_num());
        player_hand.add_card(new_card);
        deck.erase(deck.begin() + card_index);
        break;
    }
}

void dealer::print_dealer_hand() {
    player_hand.print_hand(); 
}