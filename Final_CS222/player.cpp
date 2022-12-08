#include "player.h"


player::player() {

}

hands player::get_hand() {
	return player_hand; 
}

wallet player::get_wallet() {
	return player_wallet; 
}

void player::set_fold(bool b) {
    this->fold = b;
}

bool player::get_fold() {
    return this->fold;
}

double player::get_rank() {
	return player_rank; 
}

void player::set_rank(double percent) {
	player_rank = percent;
}

void player::generate_player_hand(std::vector<Card>& deck) {
    switch (player_hand.get_number_of_cards()) {
    case 0:
        while (player_hand.get_number_of_cards() < 2) {
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


