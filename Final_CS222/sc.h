#pragma once
#include <vector>
#include <map>
#include <string>
#include "hands.h"
#include "dealer.h"
#include "player.h"

enum HAND_TYPE {
	ROYAL_FLUSH, // ONLY 4 HANDS 
	STRAIGHT_FLUSH, // 36 HANDS
	FOUR_KIND, // 624 HANDS
	FULL_HOUSE, // 3744 HANDS
	FLUSH, // 5108 HANDS
	STRAIGHT, // 10200 HANDS
	THREE_KIND, // 54912 HANDS
	TWO_PAIR, // 123552 HANDS
	ONE_PAIR, // 1098240 HANDS
	HIGH_CARD, // 1302548 OTHER HANDS
};

class s_c
{
public:
	s_c();
	void c(std::vector<Card>& deck, std::vector<player>& hands, dealer& dealer, int length);
private:
	std::map<HAND_TYPE, double> rankings = {
		{ROYAL_FLUSH, 10},
		{STRAIGHT_FLUSH, 9},
		{FOUR_KIND, 8},
		{FULL_HOUSE, 7},
		{FLUSH, 6},
		{STRAIGHT, 5},
		{THREE_KIND, 4},
		{TWO_PAIR, 3},
		{ONE_PAIR, 2},
		{HIGH_CARD, 1},
	};
	std::map<HAND_TYPE, double> posible_hands = {
		{ROYAL_FLUSH, 4},
		{STRAIGHT_FLUSH, 36},
		{FOUR_KIND, 624},
		{FULL_HOUSE, 3744},
		{FLUSH, 5108},
		{STRAIGHT, 10200},
		{THREE_KIND, 54912},
		{TWO_PAIR, 123552},
		{ONE_PAIR, 1098240},
		{HIGH_CARD, 1302548},
	};

	double NUMBER_OF_HANDS = 2598960;
	double NUMBER_OF_RANK = 55;

	bool check(HAND_TYPE& t, std::vector<Card>& c, dealer& dealer);
	bool Royal_Flush(std::vector<Card>& c);
	bool Straight_Flush(std::vector<Card>& c);
	bool Four_Kind(std::vector<Card>& c);
	bool Full_House(std::vector<Card>& c);
	bool Flush(std::vector<Card>& c);
	bool Straight(std::vector<Card>& c);
	bool Three_Kind(std::vector<Card>& c);
	bool Two_Pair(std::vector<Card>& c);
	bool One_Pair(std::vector<Card>& c);
	bool High_Card(std::vector<Card>& c);
	bool check_suit(std::vector<Card>& c, int b = 2);
	bool check_number(std::vector<Card>& c, int b);
	bool check_pair(std::vector<Card>& c, int b, int d);
	bool check_sequ(std::vector<Card>& c);

};