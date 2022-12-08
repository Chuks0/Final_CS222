#pragma once

#include "player.h"
#include <vector>

class dealer : public player {
protected:

public:
	dealer(); 
	void generate_dealer_hand(std::vector<Card>&);
	void add_dealer_card(std::vector<Card>& deck, int total_card);
	void print_dealer_hand();
};
