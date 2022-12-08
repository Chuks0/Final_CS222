#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <format>
#include <algorithm>
#include "sc.h"
#include "Cards.h"
#include "dealer.h"
#include "hands.h"
#include "player.h"


//CS222 Final - Texas Hold'em Companion
//Fall Semester 2022 
//Brogan Murray, Chukwuebuka Ozodi
//Jo Gravelle, Mackenzie Balanganayi


int Lines(std::string path);

void card_input(std::vector<Card>& deck, std::string path, int card_nums);

void initialize_player_list(std::vector<player>& playerl, int p_num);

void get_user_input(std::vector<Card>& deck, std::vector<player>& playerl, int p_num);


int main() {
	std::string path = "Data/CardList.csv";
	std::string output_file = "Data\\Balance.csv";
	const int MAX_PLAYERS = 4;
	int card_num = Lines(path) - 1;
	std::vector<Card> deck;
	std::vector<player> players;
	card_input(deck, path, card_num);
	srand(time(NULL));


	std::cout << "Welcome to the Texas Hold'em Companion program.\n"
		"\nBelow are the list of card suits and values are their corresponding numbers:\n" << std::endl;
	std::cout << "Suits: 1) Hearts    2) Spades    3) Diamonds    4) Clubs" << std::endl;
	std::cout << "Numbers: 1) ACE     2-10         11) Jack       12) Queen     13) King \n" << std::endl;
	std::cout << "\tEnter Q to Quit the program at certain points." << std::endl;

	bool playing = true;
	while (playing) {

		bool valid_in = false;
		int num_p = 0;
		std::string num_of_players;
		while (num_p <= 0 || num_p > 4)
		{
			std::cout << "\nHow many people are going to be playing? [Enter a number 1-" << MAX_PLAYERS << "]: ";

			while (!valid_in) {
				std::getline(std::cin, num_of_players);

				if (num_of_players.compare("Q") == 0 || num_of_players.compare("q") == 0) {
					std::cout << "Exiting program. Thanks for playing!" << std::endl;
					return 1;
				}
				for (int i = 0; i < MAX_PLAYERS; i++) {
					if (num_of_players.compare(std::to_string(i+1)) == 0) {
						valid_in = true;
					}	
				}
				if (!valid_in) std::cout << "\n[Enter a number 1-" << MAX_PLAYERS << "]: " << std::endl;
			}
			num_p = std::stoi(num_of_players);
			if (num_p <= 0) {
				std::cout << "There must be at least 1 player, please try again." << std::endl;
			}
			if (num_p > 4) {
				std::cout << "There cannot be more than 4 players, please try again." << std::endl;
			}
		}

		initialize_player_list(players, num_p);

		std::string deposit;
		std::cout << std::endl;
		for (int i = 0; i < num_p; i++) {
			double user_deposit = 0;
			while (user_deposit <= 0)
			{
				std::cout << "Please enter the amount of the initial deposit for player " << i + 1 << ": $";
				valid_in = false;
				while (!valid_in)
				{
					std::getline(std::cin, deposit);
					valid_in = true;
					std::for_each(deposit.begin(), deposit.end(), [&valid_in](char& c) {if (!std::isdigit(c)) valid_in = false; });
					if (deposit.compare("Q") == 0 || deposit.compare("q") == 0) {
						std::cout << "Exiting program. Thanks for playing!" << std::endl;
						return 1;
					}
					if (!valid_in) std::cout << "\n[Enter a number]: " << std::endl;
				}

				if (!deposit.empty()) {
					user_deposit = std::stod(deposit);
					players[i].player_wallet.set_balance(user_deposit);
				}
				if (user_deposit <= 0) {
					std::cout << "Invalid deposit! Please try again. " << std::endl;
				}
			}
		}


		std::cout << "\nWould you like to enter your cards manually or have them dealt to you? \n\t[Enter 'M' for manual or 'D' for dealt]: ";
		bool valid = false;
		bool dealhand = false;
		while (valid == false) {
			std::string user_move;
			std::getline(std::cin, user_move);
			if (user_move.compare("M") == 0 || user_move.compare("m") == 0) {
				valid = true;
			}
			else if (user_move.compare("D") == 0 || user_move.compare("d") == 0) {
				valid = true;
				dealhand = true;
			}
			else {
				std::cout << "Invalid input. Please try again: ";
			}
		}
		valid = false;

		if (dealhand == false) {
			get_user_input(deck, players, num_p);
		}
		else if (dealhand == true) {
			if (players.size() == 1) {
				std::cout << "The dealer deals 2 cards out to the lone player." << std::endl;
			}
			else {
				std::cout << "The dealer deals 2 cards out to each of the " << players.size() << " players." << std::endl;
			}

			for (int i = 0; i < players.size(); i++) {
				players[i].generate_player_hand(deck);
			}
		}
		dealhand = false;

		s_c s;
		dealer d;
		d.generate_dealer_hand(deck);

		//round 1
		bool valid_move = false;
		std::cout << "\n\tThe first round of betting: " << std::endl;
		std::string user_move;
		s.c(deck, players, d, num_p);
		for (int i = 0; i < num_p; i++) {
			if (!players[i].get_fold()) {
				std::cout << "\nPlayer " << i + 1 << "'s turn: " << std::endl;
				std::cout << "\nYour cards: \n[Suit, Value]" << std::endl;
				players[i].player_hand.print_hand();


				std::cout << "\nYour current hand strength is " << (int)players[i].get_rank() << "/55." << std::endl;
				std::cout << "\n\rEnter Your Move ('F' to Fold, 'C' to Check, or 'B' to Bet): ";

				while (valid_move == false) {
					std::getline(std::cin, user_move);
					if (user_move.compare("f") != 0 && user_move.compare("F") != 0 && user_move.compare("b") != 0 && user_move.compare("B") != 0 && user_move.compare("c") != 0 && user_move.compare("C") != 0) {
						std::cout << "Invalid input! Please try again." << std::endl;
					}
					else {
						valid_move = true;
					}
				}
				valid_move = false;

				if (user_move.compare("b") == 0 || user_move.compare("B") == 0) {
					players[i].player_wallet.print_funds();
					players[i].player_wallet.set_bet(players[i].player_wallet.get_balance());
				}
				if (user_move.compare("c") == 0 || user_move.compare("C") == 0) {
					std::cout << "You've checked." << std::endl;
					players[i].player_wallet.print_funds();
				}
				if (user_move.compare("f") == 0 || user_move.compare("F") == 0) {
					std::cout << "You have successfully folded." << std::endl;
					players[i].player_wallet.file_out(players[i].player_wallet, output_file, true, players[i].get_rank(), i + 1);
					players[i].set_fold(true);
				}
			}
		}
		//end round1

		//round2
		std::cout << "\n\n\tThe second round: " << std::endl;
		std::cout << "The dealer deals out the flop, the three community cards." << std::endl;
		std::cout << "The community cards: " << std::endl;
		s.c(deck, players, d, num_p);
		for (int i = 0; i < num_p; i++) {
			if (!players[i].get_fold()) {
				d.print_dealer_hand();
				std::cout << "\nPlayer " << i + 1 << "'s turn: " << std::endl;
				std::cout << "\nYour cards: \n[Suit, Value]" << std::endl;
				players[i].player_hand.print_hand();

				std::cout << "\nYour current hand strength is " << (int)players[i].get_rank() << "/55." << std::endl;
				std::cout << "\n\rEnter Your Move ('F' to Fold, 'C' to Check, or 'B' to Bet): ";

				while (valid_move == false) {
					std::getline(std::cin, user_move);
					if (user_move.compare("f") != 0 && user_move.compare("F") != 0 && user_move.compare("b") != 0 && user_move.compare("B") != 0 && user_move.compare("c") != 0 && user_move.compare("C") != 0) {
						std::cout << "Invalid input! Please try again." << std::endl;
					}
					else {
						valid_move = true;
					}
				}
				valid_move = false;

				if (user_move.compare("b") == 0 || user_move.compare("B") == 0) {
					players[i].player_wallet.print_funds();
					players[i].player_wallet.set_bet(players[i].player_wallet.get_balance());
				}
				if (user_move.compare("c") == 0 || user_move.compare("C") == 0) {
					std::cout << "You've checked." << std::endl;
					players[i].player_wallet.print_funds();
				}
				if (user_move.compare("f") == 0 || user_move.compare("F") == 0) {
					std::cout << "You have successfully folded." << std::endl;
					players[i].player_wallet.file_out(players[i].player_wallet, output_file, true, players[i].get_rank(), i + 1);
					players[i].set_fold(true);
				}
			}
		}
		//end round 2


		//round3
		std::cout << "\n\n\tThe third round: " << std::endl;
		std::cout << "The dealer draws the turn, the fourth community card." << std::endl;
		d.add_dealer_card(deck, 4);
		std::cout << "The community cards: " << std::endl;
		s.c(deck, players, d, num_p);
		for (int i = 0; i < num_p; i++) {
			if (!players[i].get_fold()) {
				d.print_dealer_hand();
				std::cout << "\nPlayer " << i + 1 << "'s turn: " << std::endl;
				std::cout << "\nYour cards: \n[Suit, Value]" << std::endl;
				players[i].player_hand.print_hand();

				std::cout << "\nYour current hand strength is " << (int)players[i].get_rank() << "/55." << std::endl;
				std::cout << "\n\rEnter Your Move ('F' to Fold, 'C' to Check, or 'B' to Bet): ";

				while (valid_move == false) {
					std::getline(std::cin, user_move);
					if (user_move.compare("f") != 0 && user_move.compare("F") != 0 && user_move.compare("b") != 0 && user_move.compare("B") != 0 && user_move.compare("c") != 0 && user_move.compare("C") != 0) {
						std::cout << "Invalid input! Please try again." << std::endl;
					}
					else {
						valid_move = true;
					}
				}
				valid_move = false;

				if (user_move.compare("b") == 0 || user_move.compare("B") == 0) {
					players[i].player_wallet.print_funds();
					players[i].player_wallet.set_bet(players[i].player_wallet.get_balance());
				}
				if (user_move.compare("c") == 0 || user_move.compare("C") == 0) {
					std::cout << "You've checked." << std::endl;
					players[i].player_wallet.print_funds();
				}
				if (user_move.compare("f") == 0 || user_move.compare("F") == 0) {
					std::cout << "You have successfully folded." << std::endl;
					players[i].player_wallet.file_out(players[i].player_wallet, output_file, true, players[i].get_rank(), i + 1);
					players[i].set_fold(true);
				}
			}
		}
		//end round 3

		//round4
		std::cout << "\n\n\tThe fourth round: " << std::endl;
		std::cout << "The dealer draws the final card, also known as the river." << std::endl;
		d.add_dealer_card(deck, 5);
		std::cout << "The community cards: " << std::endl;
		s.c(deck, players, d, num_p);
		for (int i = 0; i < num_p; i++) {
			if (!players[i].get_fold()) {
				d.print_dealer_hand();
				std::cout << "\nPlayer " << i + 1 << "'s turn: " << std::endl;
				std::cout << "\nYour cards: \n[Suit, Value]" << std::endl;
				players[i].player_hand.print_hand();

				std::cout << "\nYour current hand strength is " << (int)players[i].get_rank() << "/55." << std::endl;
				std::cout << "\n\rEnter Your Move ('F' to Fold, 'C' to Check, or 'B' to Bet): ";

				while (valid_move == false) {
					std::getline(std::cin, user_move);
					if (user_move.compare("f") != 0 && user_move.compare("F") != 0 && user_move.compare("b") != 0 && user_move.compare("B") != 0 && user_move.compare("c") != 0 && user_move.compare("C") != 0) {
						std::cout << "Invalid input! Please try again." << std::endl;
					}
					else {
						valid_move = true;
					}
				}
				valid_move = false;

				if (user_move.compare("b") == 0 || user_move.compare("B") == 0) {
					players[i].player_wallet.print_funds();
					players[i].player_wallet.set_bet(players[i].player_wallet.get_balance());
				}
				if (user_move.compare("c") == 0 || user_move.compare("C") == 0) {
					std::cout << "You've checked." << std::endl;
					players[i].player_wallet.print_funds();
				}
				if (user_move.compare("f") == 0 || user_move.compare("F") == 0) {
					std::cout << "You have successfully folded." << std::endl;
					players[i].player_wallet.file_out(players[i].player_wallet, output_file, true, players[i].get_rank(), i + 1);
					players[i].set_fold(true);
				}
			}
		}
		//end round4

		s.c(deck, players, d, num_p);
		std::cout << players[0].get_rank() << std::endl;
		std::cout << "\n\nEnd of the game. Card Summary: " << std::endl;
		std::cout << "The dealers cards: \n[Suit, Value]" << std::endl;
		d.player_hand.print_hand();
		for (int i = 0; i < players.size(); i++) {
			std::cout << "\nPlayer " << i + 1 << "'s cards: \n[Suit, Value]" << std::endl;
			players[i].player_hand.print_hand();
			std::cout << "Player " << i + 1 << "'s hand strength is " << (int)players[i].get_rank() << " / 55." << std::endl;
		}
		std::cout << std::endl;


		for (int i = 0; i < players.size(); i++) {
			std::cout << "\nPlayer " << i + 1 << ", enter results: " << std::endl;
			players[i].player_wallet.file_out(players[i].player_wallet, output_file, false, players[i].get_rank(), i + 1);
		}


		std::cout << "\nWould you like to play again? [Enter 'Y' or 'N']: ";
		bool reset = false;
		while (valid_move == false) {
			std::string user_move;
			std::getline(std::cin, user_move);
			if (user_move.compare("Y") == 0 || user_move.compare("y") == 0) {
				reset = true;
				valid_move = true;
			}
			else if (user_move.compare("N") == 0 || user_move.compare("n") == 0) {
				reset = false;
				valid_move = true;
			}
			else {
				std::cout << "Invalid input. Please try again: ";
			}
		}
		if (reset == true) {
			std::cout << "\nResetting program...\n\n\n\n";
			std::cout << "Welcome once more to the Texas Hold'em Companion program.\n"
				"\nAs a reminder, below are the list of card suits and values are their corresponding numbers:\n" << std::endl;
			std::cout << "Suits: 1) Hearts    2) Spades    3) Diamonds    4) Clubs" << std::endl;
			std::cout << "Numbers: 1) ACE     2-10         11) Jack       12) Queen     13) King \n" << std::endl;
			std::cout << "\tEnter Q to Quit the program at certain points." << std::endl;
			playing = true;
		}
		else if (reset == false) {
			std::cout << "\nClosing program...\n\n\n\n";
			playing = false;
		}

	}//closing bracket for playing loop


	std::cout << "Please check the output file to access player balance info!" << std::endl;

	return 0;
}

int Lines(std::string path) {
	std::ifstream stream;
	stream.open(path);

	int line_num = 0;

	std::string line;
	while (std::getline(stream, line)) {
		line_num++;
	}

	stream.close();
	return line_num;
}

void card_input(std::vector<Card>& deck, std::string path, int card_nums) {
	deck.clear();
	std::ifstream stream;
	stream.open(path);

	std::string line;
	std::getline(stream, line);
	for (int i = 0; i < card_nums; i++) {
		std::getline(stream, line);
		std::stringstream ss(line);

		std::string substr;
		std::getline(ss, substr, ',');
		int suit = std::stoi(substr);

		std::getline(ss, substr, ',');
		int card_num = std::stoi(substr);
		Card new_card(suit, card_num);
		deck.push_back(new_card);
	}
	stream.close();
}

void initialize_player_list(std::vector<player>& playerl, int p_num) {
	playerl.clear();
	player p1;
	player p2;
	player p3;
	player p4;
	playerl.push_back(p1);
	playerl.push_back(p2);
	playerl.push_back(p3);
	playerl.push_back(p4);

	while (playerl.size() != p_num) {
		playerl.pop_back();
	}
}

void get_user_input(std::vector<Card>& deck, std::vector<player>& playerl, int p_num) {
	std::string cardparse = " ";
	bool getcard = false;
	bool cardcheck = false;
	bool valid = false;
	int cardnum;
	int cardsuit;

	for (int i = 0; i < p_num; i++) {
		valid = false;
		std::cout << "Player " << i + 1 << ": " << std::endl;

		for (int k = 1; k <= 2; k++) {
			valid = false;
			while (valid == false) {
				std::cout << "Please enter the suit for card " << k << ": ";
				while (getcard == false) {
					std::getline(std::cin, cardparse);
					while (stoi(cardparse) > 4 || stoi(cardparse) < 0) {
						std::cout << "Invalid input! Please enter a valid suit: ";
						std::getline(std::cin, cardparse);
					}
					cardsuit = stoi(cardparse);
					getcard = true;
					//std::cout << "The card suit is: " << cardsuit << std::endl;
				}
				getcard = false;

				std::cout << "Please enter the value of card " << k << ": ";
				while (!getcard) {
					std::getline(std::cin, cardparse);
					while (stoi(cardparse) > 13 || stoi(cardparse) < 0) {
						std::cout << "Invalid input! Please enter a valid value: ";
						std::getline(std::cin, cardparse);
					}
					cardnum = stoi(cardparse);
					getcard = true;
					//std::cout << "The card num is: " << cardnum << std::endl;
				}
				getcard = false;

				//std::cout << "Generating card...!" << std::endl;
				Card c1(cardsuit, cardnum);

				while (!cardcheck) {
					for (int j = 0; j < deck.size(); j++) {
						if (c1.get_num() == deck[j].get_num() && c1.get_suit() == deck[j].get_suit()) {
							deck.erase(deck.begin() + j);
							playerl[i].player_hand.add_card(c1);
							cardcheck = true;
							valid = true;
							std::cout << "------Card added------" << std::endl;
							break;
						}
					}
					if (!cardcheck && !valid) {
						std::cout << "Card is not in the deck! Please enter a new card." << std::endl;
						break;
					}
				}
				cardcheck = false;
			}
		}
	}
}