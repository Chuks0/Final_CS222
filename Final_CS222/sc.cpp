#include "sc.h"
#include "hands.h"
#include "Cards.h"
#include "dealer.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <map>

void s_c::c(std::vector<Card>& deck, std::vector<player>& hand, dealer& dealer, int length) {
	for (int i = 0; i < length; i++) {
		double p = 0;
		std::vector<HAND_TYPE> list = {
			ROYAL_FLUSH,
			STRAIGHT_FLUSH,
			FOUR_KIND,
			FULL_HOUSE,
			FLUSH,
			STRAIGHT,
			THREE_KIND,
			TWO_PAIR,
			ONE_PAIR,
			HIGH_CARD,
		};
		for (HAND_TYPE t : list) {
			std::vector<Card> h = hand[i].get_hand().get_hand();
			if (this->check(t, h, dealer)) {
				if (rankings.find(t) != rankings.end()) {
					p += rankings.find(t)->second;
				}
			}
		}
		p = p;
		hand[i].set_rank(p);
	}
}


bool s_c::check(HAND_TYPE& t, std::vector<Card>& c, dealer& dealer) {
	std::vector<Card> d = dealer.get_hand().get_hand();
	c.insert(c.end(), d.begin(), d.end());

	switch (t)
	{
	case ROYAL_FLUSH:
		return Royal_Flush(c);
		break;
	case STRAIGHT_FLUSH:
		return Straight_Flush(c);
		break;
	case FOUR_KIND:
		return Four_Kind(c);
		break;
	case FULL_HOUSE:
		return Full_House(c);
		break;
	case FLUSH:
		return Flush(c);
		break;
	case STRAIGHT:
		return Straight(c);
		break;
	case THREE_KIND:
		return Three_Kind(c);
		break;
	case TWO_PAIR:
		return Two_Pair(c);
		break;
	case ONE_PAIR:
		return One_Pair(c);
		break;
	case HIGH_CARD:
		return High_Card(c);
		break;
	default:
		return false;
		break;
	}
}
bool s_c::Royal_Flush(std::vector<Card>& c) {
	int s2 = 0;
	int num;
	std::map<int, int> h;
	for (int i = 0; i < c.size(); i++) {
		if (!check_suit(c)) return false;

		num = c[i].get_num();
		if (num == 1) {
			std::map<int, int>::iterator pos = h.find(1);
			if (pos == h.end()) {
				h.insert(std::make_pair(1, 1));
			}
			else {
				if (pos->second > 1) {
					pos->second++;
					s2++;
				}
			}
		}
		else
			if (num > 9) {
				std::map<int, int>::iterator pos = h.find(num);
				if (pos == h.end()) {
					h.insert(std::make_pair(num, 1));
				}
				else {
					if (pos->second > 1) {
						pos->second++;
						s2++;
					}
				}
			}
			else {
				s2++;
				if (s2 > 2) return false;
			}
	}
	return true;
}
bool s_c::Straight_Flush(std::vector<Card>& c) {
	return (check_sequ(c) && check_suit(c, 2)) ? true : false;
}
bool s_c::Four_Kind(std::vector<Card>& c) {
	return check_suit(c, 3);
}
bool s_c::Full_House(std::vector<Card>& c) {
	return check_pair(c, 3, 2);
}
bool s_c::Flush(std::vector<Card>& c) {
	return check_suit(c);
}
bool s_c::Straight(std::vector<Card>& c) {
	return check_sequ(c);
}
bool s_c::Three_Kind(std::vector<Card>& c) {
	return check_suit(c, 4);
}
bool s_c::Two_Pair(std::vector<Card>& c) {
	return check_pair(c, 2, 2);
}
bool s_c::One_Pair(std::vector<Card>& c) {
	return check_suit(c, 5);
}
bool s_c::High_Card(std::vector<Card>& c) {
	return true;
}

bool s_c::check_suit(std::vector<Card>& c, int b) {
	bool check = false;
	std::map<int, int> m;
	for (int i = 0; i < c.size(); i++) {
		int num = c[i].get_suit();
		std::map<int, int>::iterator pos = m.find(num);
		if (pos == m.end()) {
			m.insert(std::make_pair(num, 1));
		}
		else {
			pos->second++;
		}
	}
	std::for_each(m.begin(), m.end(), [&c, &check, &b](std::pair<const int, int>& i) {if (i.second >= c.size() - b) check = true; });
	return check;
}
bool s_c::check_number(std::vector<Card>& c, int b) {
	int check = 0;
	std::map<int, int> m;
	for (int i = 0; i < c.size(); i++) {
		int num = c[i].get_num();
		std::map<int, int>::iterator pos = m.find(num);
		if (pos == m.end()) {
			m.insert(std::make_pair(num, 1));
		}
		else {
			pos->second++;
		}
	}
	std::for_each(m.begin(), m.end(), [&c, &check, &b](std::pair<const int, int>& i) {if (i.second >= c.size() - b) { i.second = 0; check++; } });

	return (check >= 2) ? true : false;
}
bool s_c::check_pair(std::vector<Card>& c, int b, int d) {
	int check = 0;
	std::map<int, int> m;
	for (int i = 0; i < c.size(); i++) {
		int num = c[i].get_num();
		std::map<int, int>::iterator pos = m.find(num);
		if (pos == m.end()) {
			m.insert(std::make_pair(num, 1));
		}
		else {
			pos->second++;
		}
	}
	std::for_each(m.begin(), m.end(), [&c, &check, &b](std::pair<const int, int>& i) {if (i.second >= c.size() - b) { i.second = 0; check++; } });
	std::for_each(m.begin(), m.end(), [&c, &check, &d](std::pair<const int, int>& i) {if (i.second >= c.size() - d) { i.second = 0; check++; } });

	return (check >= 2) ? true : false;
}
bool s_c::check_sequ(std::vector<Card>& c) {
	bool check = false;
	std::sort(c.begin(), c.end(), [](Card& a, Card& b) -> bool {return std::isless(a.get_num(), b.get_num()); });
	int s = c[0].get_num();
	int n = s + 1;
	int a = 0;

	for (int i = 1; i < c.size(); i++) {
		if (c[i].get_num() == n) {
			n++;
			a++;
		}
		else
		{
			s = c[i].get_num();
			n = s + 1;
			a = 0;
		}
	}

	check = (a >= c.size() - 2) ? true : false;

	return check;
}

s_c::s_c()
{
}