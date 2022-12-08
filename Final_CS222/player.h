#pragma once

#include <string>
#include "wallet.h"
#include "hands.h"

class player {
protected: 
	double player_rank = 0;
	bool fold = false;
public:
	bool get_fold();
	void set_fold(bool);
	wallet player_wallet;
	hands player_hand;
	player(); 
	wallet get_wallet(); 
	hands get_hand(); 
	void set_rank(double percent); 
	double get_rank(); 
	void generate_player_hand(std::vector<Card>& deck);
};