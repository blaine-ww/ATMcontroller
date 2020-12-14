/**  A class of banking transactions for implementation of ATM
that includes processing card number and PIN password,
returning account balance, and  withdrawal and deposit, 
@file ATM.cpp */


#include "ATM.h"
#include "Exceptions.cpp"
#include "Messages.cpp"

/* ATM() constructor 
	string CCnum;	// String representation of card number inserted into ATM
	string PIN;		// String representation of PIN password to unlock balance
	bool pinApproved; 	// PIN cross-checked with API, prevents unauthorized access
	bool logOut;		// User ended transaction, prevents unauthorized access
	int rollingBalance; // Checking balance reflected after ATM login
	Bank associatedBank;// Linked Bank
	User user;			// API returned struct with card associated bank, balance, pin check 
 */
ATM::ATM() : CCnum(""), PIN(""), pinApproved(false), logOut(false), rollingBalance(INT_MIN), associatedBank(Bank(0)), user({{Bank(0)},{0}}){
}



/* ATM(string CCnum, string PIN) constructor 
 */
ATM::ATM(string cc, string pin) : CCnum(cc), PIN(pin), pinApproved(false), logOut(false), rollingBalance(0), associatedBank(Bank(0)), user({{Bank(0)},{0}}){
}



/* ATM destructor
 */
ATM::~ATM(){
	//delete user; Simplified to creating declaring user struct on stack, otherwise would have declared User with pointer.
}



/* Return API data, parse, and assign it to the User struct
	struct User{
		Bank bank;		 // Linked Bank
		int balance;	 // Checking balance reflected after ATM login
		bool pinisvalid; // PIN cross-checked with API, prevents unauthorized access
	};

	Note this is artificial data, that would otherwise be produced via API call
 */
User ATM::getAPIinfo(){
	
	// Get API data, parse, and assign it to the struct.
    
    /*struct User user = {
        .bank = Bank(b),//g_strdup(json_object_get_string_member(stuff, "bank")),
        .balance = 1000 //json_object_get_int_member(stuff, "balance")
    };*/

    printProcessingMsg();

    int b = CCnum[0]-'0';		// Taking the first digit of user input card number to assign associated Bank

    /*** Note this is artificial data, that would otherwise be produced via API call ***/
    user.bank = Bank(b);		// Artificial Bank assignment through enum struct
    user.balance = 1000;		// Artificial dollar balance reflected from user account
    user.pinisvalid = true;		// Artificial approval of PIN inserted

	associatedBank=user.bank;	// Assign to ATM class members
	rollingBalance=user.balance;
	pinApproved=user.pinisvalid;

	return user;
}



/* Set API data, for now just update user
 */
void ATM::updateBalance(){
	user.balance=rollingBalance; //user.balance=newBalance;
}



/* Returns string card number, digits only of CC_size length
 */
string ATM::getCC(void) const{
	return CCnum;
}



/* Returns string PIN, digits only of PIN_size length
 */
string ATM::getPIN(void) const{
	return PIN;
}



/* Returns whole dollar balance, if PIN is correct
 */
int ATM::getBalance(void) const{
	return (pinApproved) ? rollingBalance : INT_MIN;
}



/* Returns card number's associated bank, if PIN is correct
 */
Bank ATM::getBank(void) const{
	return (pinApproved) ? associatedBank : Bank(0);
}



/* insertCC() // Set card number
   Redirect to insertCC(string)
 */
void ATM::insertCC(){
	string num; // Declare empty string
	insertCC(num);
}



/* insertCC(string num) // Set card number
   Accept user string input and parse out unwanted char
   until valid CC_SIZE(16-digit) string input is entered
 */
void ATM::insertCC(string num){

	do{
		cout << "\nPlease insert your debit card number followed by Enter: \n";
		if (num.empty())
			getline(cin,num);

		num.erase(remove_if(num.begin(), num.end(), 
			[](unsigned char x){return !isdigit(x);}), 
			num.end());

		if (num.size()>CC_SIZE)
			num.erase(num.begin()+CC_SIZE,num.end());
		else if (num.size()<CC_SIZE){
			cout <<"You have entered a " << num.size() << " digit card number.\n";
			CC_ERROR();
			num.clear(); 
		}

	}while(num.size()<CC_SIZE);  //CC_SIZE(16) digit

	CCnum=num;
}



/* insertPIN() // Set PIN password
   Redirect to insertPIN(string)
 */
void ATM::insertPIN(){
	string num; // Declare empty string
	insertPIN(num);
}



/* insertPIN(string num) // Set PIN password
   Accept user string input and parse out unwanted char
   until valid PIN_SIZE(4-digit) string input is entered
 */
void ATM::insertPIN(string num){
	
	do{
		cout << "\nPlease insert your PIN followed by Enter: \n";
		if (num.empty())
			getline(cin,num);		

		num.erase(remove_if(num.begin(), num.end(), 
			[](unsigned char x){return !isdigit(x);}), 
			num.end());

		if (num.size()>PIN_SIZE)
			num.erase(num.begin()+PIN_SIZE,num.end());
		else if (num.size()<PIN_SIZE){
			cout <<"You have entered a " << num.size() << " digit PIN.\n";
			PIN_ERROR();
			num.clear();
		}

	}while(num.size()<PIN_SIZE);

	PIN=num;
}



/* After retrieving API data, cross-check whether user input PIN is valid
   Note: Due to artificial data, enum Bank(0) is intentionally set to be an invalid Bank,
   therefore any card number inputted with the first digit of '0' are deemed invalid
 */
bool ATM::checkPIN(void){

	user = getAPIinfo();

	//if (user==NULL)
	if (associatedBank==Bank(0)){   //bc user.bank may be null, cross check with Bank
		BALANCE_ERROR();
		pinApproved=false;
	}
	else
		printWelcomeMsg();
	
	// Check API returns valid user
	return pinApproved;   //return (user!=NULL);
}



/* Prints censored card number on ATM screen
 */
void ATM::showCC(void){

	//for (auto i:(CC_SIZE-4)/4) string censor += (string(4,'*')+ " ");

	if (!getCC().empty())
		cout << "This is your card number: " << (string(4,'*')+ " ")<< (string(4,'*')+ " ")<< (string(4,'*')+ " ") << getCC().substr(CC_SIZE-4,CC_SIZE) << endl;
	else //if (!pinApproved)
		INPUT_ERROR();
	//else
		//LOGOUT_ERROR();	
}



/* Prints censored PIN password on ATM screen
 */
void ATM::showPIN(void){
	if (!getPIN().empty())
		cout << "This is your PIN: " << string(PIN_SIZE-1,'*') << getPIN().substr(PIN_SIZE-1,PIN_SIZE) << endl;
	else //if (!pinApproved)
		INPUT_ERROR();
	//else
		//LOGOUT_ERROR();
}



/* deposit(int) // User-initiated deposit amount
   if positive amount, update user account balance
 */
int ATM::deposit(const int amtDeposit){

	printDepositMsg(amtDeposit);

	if (!pinApproved) //logOut ||
		INPUT_ERROR();

	else if (getPIN().empty())
		BALANCE_ERROR();

	else if (amtDeposit>0){
		//return remaining acct balance
		rollingBalance+=amtDeposit;
		printProcessingMsg();
		updateBalance();	//set new balance
		printSucessMsg();
	}
	else  //negative deposit (amtDeposit<0)
		NEGATIVEINPUT_ERROR();
		//throw invalid_argument("You have attempted to withdraw/deposit a negative amount. Please input a positive amount.\n");

	return rollingBalance;
}



/* withdraw(int) // User-initiated withdrawal amount
   if positive amount and enough balance, update user account balance
 */
int ATM::withdraw(const int amtWithdraw){

	printWithdrawMsg(amtWithdraw);

	//return remaining acct balance
	if (!pinApproved) //logOut || 
		INPUT_ERROR();

	else if (getPIN().empty())
		BALANCE_ERROR();

	else if ((rollingBalance-amtWithdraw)>0  && amtWithdraw>0){
		rollingBalance-=amtWithdraw;
		printProcessingMsg();
		updateBalance();	//set new balance
		printSucessMsg();
	}
	else if (amtWithdraw<0)
		NEGATIVEINPUT_ERROR();
	else
		OVERDRAWN_ERROR();

	return rollingBalance;
}







/* User-initiated logout of account
   Clear all previous class members
   Reset all previous class members
 */
void ATM::logout(){

	//Though this is performed in destructor, in case object is not deleted yet in main.cpp
	logOut=true;
	pinApproved=false;
	CCnum.clear();
	PIN.clear();

	printLogoutMsg();
}