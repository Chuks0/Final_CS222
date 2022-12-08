#include <iostream>
#include "hands.h"
#include <iostream>
#include <sstream>
#include <iomanip>

hands::hands() {

}

int hands::get_number_of_cards() {
    return hand.size();
}

void hands::add_card(Card feedcard) {
    hand.push_back(feedcard);
}

std::vector<Card> hands::get_hand() {
    return hand;
}

void hands::empty_hand() {
    hand.clear();
}

std::string hands::to_format(const int number) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << number;
    std::string output = ss.str();
    ss.clear();
    return output;
}

std::string hands::get_suit_string(int i) {
    switch (i) {
    case 1:
        return "He";
        break;
    case 2:
        return "Sp";
        break;
    case 3:
        return "Di";
        break;
    case 4:
        return "Cl";
        break;
    default:
        return "♧♡♤♢";
        break;
    }
}


void hands::print_hand() {
    std::vector<std::string> lines;
    for (int i = 0; i < 9; i++) {
        lines.push_back("");
    }

    for (int i = 0; i < hand.size(); i++) {

        int num = hand[i].get_num();
        int suit = hand[i].get_suit();

        lines[0].append(" _______________ ");
        lines[1].append("|" + to_format(num) + " " + get_suit_string(suit));
        lines[1].append("          |");
        lines[2].append("|               |");
        lines[3].append("|               |");
        lines[4].append("|       " + to_format(num));
        lines[4].append("      |");
        lines[5].append("|               |");
        lines[6].append("|               |");
        lines[7].append("|          " + to_format(num) + " " + get_suit_string(suit));
        lines[7].append("|");
        lines[8].append("|_______________|");
    }

    for (int i = 0; i < 9; i++) {
        std::cout << lines[i] << std::endl;

    }
}