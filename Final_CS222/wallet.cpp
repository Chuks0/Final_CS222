#include <iostream>
#include "wallet.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

wallet::wallet() {
	balance = 0;
	totalbet = 0;
	bet = 0;
}
void wallet::set_bet(double balance) {
	std::string choice;
	std::cout << "Please enter bet choice: 1) 10% 2) 25% 3) 50% 4) 100% 5) custom:  ";
	std::getline(std::cin, choice);
	int bet_choice = std::stoi(choice);
	switch (bet_choice) {
	default:
		bet = 0;
		break;
	case 1:
		bet = balance * .10;
		break;
	case 2:
		bet = balance * .25;
		break;
	case 3:
		bet = balance * .50;
		break;
	case 4:
		bet = balance;
		break;
	case 5:
		std::string custom;
		std::cout << "Enter a custom bet amount: ";
		std::getline(std::cin, custom);
		bet = std::stod(custom);
		break;

	}
	if (bet > balance) {
		std::cout << "Invalid bet!" << std::endl;
		bet = balance;
		std::cout << "Bet auto adjusted to $" << bet << std::endl;
	}
	if (bet < 0) {
		std::cout << "Invalid bet!" << std::endl;
		bet = 0.00;
		std::cout << "Bet auto adjusted to $" << bet << std::endl;
	}
	std::cout << "You bet $" << bet << ". " << std::endl;
	this->balance = this->balance - bet;
	totalbet += bet;
	print_funds();
	print_bet();
}

void wallet::print_bet() {
	std::cout << "Your current total bet is $" << std::fixed << std::setprecision(2) << totalbet << "." << std::endl;
}

void wallet::file_out(wallet funds, std::string output_file, bool flop, double hand_strength, int index) {
	std::ofstream output;
	output.open(output_file, std::ios::app);

	if (flop) {
		funds.print_funds();
		bet = 0;
		return;
	}

	std::string choice;
	std::cout << "Report the Result (W for win, F for folded, L for loss): ";
	std::getline(std::cin, choice);
	if (choice.compare("F") == 0 || choice.compare("f") == 0) {
		std::cout << "Better luck next time." << std::endl;
		funds.balance = balance - bet;
		funds.print_funds();
	}
	if (choice.compare("L") == 0 || choice.compare("l") == 0) {
		std::cout << "Better luck next time!" << std::endl;
		funds.balance = balance - bet;
		funds.print_funds();
	}
	if (choice.compare("W") == 0 || choice.compare("w") == 0) {
		std::cout << "Congratulations! You win!" << std::endl;
		if (hand_strength >= 1 && hand_strength <= 10 && totalbet != 0) {
			funds.balance = ((balance + (totalbet * 2)) * 1.1);
		}
		if (hand_strength >= 11 && hand_strength <= 20 && totalbet != 0) {
			funds.balance = ((balance + (totalbet * 2)) * 1.3);
		}
		if (hand_strength >= 21 && hand_strength <= 30 && totalbet != 0) {
			funds.balance = ((balance + (totalbet * 2)) * 1.5);
		}
		if (hand_strength >= 31 && hand_strength <= 40 && totalbet != 0) {
			funds.balance = ((balance + (totalbet * 2)) * 1.7);
		}
		if (hand_strength >= 41 && hand_strength < 55 && totalbet != 0) {
			funds.balance = ((balance + (totalbet * 2)) * 2);
		}
		funds.print_funds();
	}
	output << "Player " << index << ", " << this->balance << std::endl;
	bet = 0;
	totalbet = 0;

	output.close();
}

double wallet::get_balance() {
	return balance;
}

double wallet::get_bet() {
	return bet;
}

void wallet::set_balance(double balance) {
	this->balance = balance;
}
void wallet::print_funds() {
	std::cout
		<< std::fixed
		<< std::setprecision(2)
		<< "Your current balance is $"
		<< balance
		<< ". "
		<< std::endl;
}