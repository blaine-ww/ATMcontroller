/** A class of banking transactions for implementation of ATM.
@file ATM.h */

#ifndef _ATM_LOOKUP
#define _ATM_LOOKUP

#include <iostream>
#include <string>
#include <algorithm>
//#include <iomanip>
#include <climits>
//#include <stdexcept>

using namespace std;



/* Bank Vault to be accesed through API (for now enum)
   Each enum member represents a separate bank that is
   identified by first digit of inserted card number 	
 */ 
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



/* API data retrieved will be stored in User struct
   Return API data, parse, and assign it to the User struct
 */
struct User{
	Bank bank;			// Linked Bank
	//string account;
	int balance;		// Checking balance reflected after ATM login
	bool pinisvalid;	// PIN cross-checked with API, prevents unauthorized access
};



class ATM{
protected:
	User user;
	User getAPIinfo();
	void updateBalance();

private:
	static const int PIN_SIZE = 4;	// Pre-determined length of card number
	static const int CC_SIZE = 16;	// Pre-determined length of PIN passcode

	string CCnum;					// Inserted card number, CC_SIZE digit string
	string PIN;						// Inserted PIN passcode, PIN_SIZE digit string
	bool pinApproved;				// true, if PIN accepted 
	bool logOut;					// true, if user transactions ended
	int rollingBalance;				// track present balance (inital value from API)
	Bank associatedBank;			// Linked bank from API				
	

	/** Retrieves inserted card number
	@return CCnum string of valid inserted card number */
	string getCC() const;

	/** Retrieves PIN passcode 
	@return PIN string of valid inserted PIN passcode */
	string getPIN() const;	
	
	/** Retrieves banking institution associated with card number 
	@return Bank enum member associated with first digit of card number */
	Bank getBank() const;
	
	/** Retrieves account balance
	@return rollingBalance present account balance in whole dollars */
	int getBalance() const;
	

	/** Outputs error message for invalid card number inserted */
	void CC_ERROR();
	
	/** Outputs error message for invalid PIN passcode inserted */
	void PIN_ERROR();
	
	/** Outputs error message for invalid access to account balance with incorrect card or 		PIN combination */
	void BALANCE_ERROR();

	/** Outputs error message for user attempting to access transactions without inserting 		card number */
	void INPUT_ERROR();
	
	/** Outputs error message for insufficient funds for withdrawal */
	void OVERDRAWN_ERROR();
	
	/** Outputs error message for user attempting to withdraw/deposit negative amount */
	void NEGATIVEINPUT_ERROR();
	
	/** Outputs error message for user attempting to access transactions after logging out */
	void LOGOUT_ERROR();
	


public:

	ATM();	//ATM() : CCnum(""), PIN(""), pinApproved(false), rollingBalance(0), associatedBank(Bank(0)){}
	ATM(string cc, string pin); //	@param cc as card number and pin as PIN passcode
	~ATM();

	/** Inserts card number via console (void) or parameter (string num) */
	void insertCC();
	void insertCC(string num);
	
	/** Inserts PIN passcode via console (void) or parameter (string num) */
	void insertPIN();
	void insertPIN(string num);
	
	/** Sees whether PIN passcode is valid 
	@return True if PIN is accepted by API */
	bool checkPIN(); 
	
	/** Prints out censored card number with last 4-digits showing */
	void showCC();
	
	/** Prints out censored PIN with last digit showing */
	void showPIN();
	
	/** Retrieves deposit amount from user  
	@post If the amount declared is positive, balance updated
	@param  amtDeposit is the amount in dollars deposited from ATM transaction
	@return New balance after deposit */
	int deposit(const int amtDeposit);

	/** Retrieves withdrawal amount from user
	@post If the amount declared is positive and not overdrawn, balance updated
	@param  amtWithdraw is the amount in dollars withdrawn from ATM transaction 
	@return New balance after withdrawal */
	int withdraw(const int amtWithdraw);
	
	/** User-initiated logout of account
   		Clear all previous class members
   		Reset all previous class members */
	void logout();

	/** Outputs to console current account balance in dollars */
	void printBalance();
	
	/** Outputs generic welcome message with associated bank */
	void printWelcomeMsg();
	
	/** Outputs message of withdrawal initiation 
	@param amtDeposit is the amount in dollars deposited from ATM transaction */
	void printDepositMsg(const int amtDeposit);
	
	/** Outputs message of deposit initiation
	@param amtWithdrawal is the amount in dollars withdrawn from ATM transaction */
	void printWithdrawMsg(const int amtWithdraw);
	
	/** Prints . . . to indicate transaction is in progress */
	void printProcessingMsg();
	
	/** Prints out <<SUCCESS>> to indicate ATM transaction completed */
	void printSucessMsg();
	
	/**  Prints out farewell message to end ATM transaction with current inserted card */
	void printLogoutMsg();
	
}; // end of ATM
#endif