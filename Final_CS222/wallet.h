#pragma once
class wallet {
protected:
	double balance;
	double totalbet; 
	double bet;

public:
	wallet();
	void set_balance(double balance);
	double get_balance();
	double get_bet();
	void file_out(wallet funds, std::string output_file, bool flop, double hand_strength, int index);
	void print_funds();
	void set_bet(double balance);
	void print_bet(); 
};