#ifndef _ATM_LOOKUP
#define _ATM_LOOKUP

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;



// Bank Vault to be accesed through API for now enum
enum Bank{  
	BankDoesNotExist, //0
	Bank_A, // 1
	Bank_B, // 2
	Bank_C, // 3
	Bank_D, // 4
	Bank_E, // 5
	Bank_F, // 6
	Bank_G, // 7
	Bank_H, // 8
	Bank_I, // 9
};


struct User{
	Bank bank;
	//string account;
	int balance;
	bool pinisvalid;
};


class ATM{
protected:
	User user;
	User getAPIinfo();
	void updateBalance();

private:
	static const int PIN_SIZE = 4;
	static const int CC_SIZE = 16;	

	string CCnum;
	string PIN;
	bool pinApproved;
	bool logOut;
	int rollingBalance;
	Bank associatedBank;
	
	string getPIN();
	string getCC();
	Bank getBank();
	int getBalance();
	//void connectBank(const Bank& theBank);
	//void updateBalance(User user, int newBalance);
	//void connectBank(const Bank& theBank, int newBalance);

	void CC_ERROR();
	void PIN_ERROR();
	void BALANCE_ERROR();
	void NEGATIVEBALANCE_ERROR();
	void NEGATIVEINPUT_ERROR();
	void LOGOUT_ERROR();
	void INPUT_ERROR();
	

	
	

public:

	ATM();
	//ATM() : CCnum(""), PIN(""), pinApproved(false), rollingBalance(0), associatedBank(Bank(0)){}
	ATM(string cc, string pin);
	~ATM();
	void insertCC();
	void insertCC(string num);
	void insertPIN();
	void insertPIN(string num);
	bool checkPIN(); //isValid
	void showCC();
	void showPIN();

	int withdraw(int amtWithdraw);
	int deposit(int amtDeposit);
	void logout();

	void printBalance();
	void printWelcomeMsg();
	void printDepositMsg();
	void printWithdrawMsg();
	void printProcessingMsg();
	void printSucessMsg();
	void printLogoutMsg();
	

};

#endif