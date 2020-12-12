#include "ATM.h"
#include "Exceptions.cpp"
#include "Messages.cpp"



ATM::ATM() : CCnum(""), PIN(""), pinApproved(false), logOut(false), rollingBalance(INT_MIN), associatedBank(Bank(0)), user({{Bank(0)},{0}}){
	/* CCnum="";
	PIN="";
	pinApproved=false; //logIn
	logOut=false;
	rollingBalance=INT_MIN;
	associatedBank=Bank(0);
	user={{Bank(0)},{0}}; */
}

ATM::ATM(string cc, string pin) : CCnum(cc), PIN(pin), pinApproved(false), logOut(false), rollingBalance(0), associatedBank(Bank(0)), user({{Bank(0)},{0}}){
}

ATM::~ATM(){
	CCnum.clear();
	PIN.clear();
	//delete user; Simplified to creating declaring user struct on stack, otherwise would have declared User with pointer.
}



string ATM::getCC(void) const{
	return CCnum;
}


string ATM::getPIN(void) const{
	return PIN;
}

int ATM::getBalance(void) const{

	return (pinApproved) ? rollingBalance : INT_MIN;

}


Bank ATM::getBank(void) const{

	return (pinApproved) ? associatedBank : Bank(0);
}

void ATM::insertCC(){
	
	string num; //16digit

	insertCC(num);

}
void ATM::insertCC(string num){
	
	//string num; //16digit

	//cout <<"\nWelcome to this generic ATM!\n";

	do{
		cout << "\nPlease insert your debit card number followed by Enter: \n";
		if (num.empty())
			getline(cin,num);
		//cin >> CCnum;
		//cin.clear();
		
		/*cout << "Press Enter to continue\n";
		if (cin.get()=='\n') //if (cin.get()=='#')
			cin.ignore();	*/
		//cout << num.size() << endl;

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

	}while(num.size()<CC_SIZE);

	CCnum=num;
}


void ATM::insertPIN(){
	
	string num; //4digit

	insertPIN(num);



}



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

User ATM::getAPIinfo(){
	
	// Get API data, parse, and assign it to the struct.
    int b = CCnum[0]-'0';

    /*struct User user = {
        .bank = Bank(b),//g_strdup(json_object_get_string_member(stuff, "bank")),
        .balance = 1000 //json_object_get_int_member(stuff, "balance")
    };*/

    printProcessingMsg();

    user.bank = Bank(b);
    user.balance = 1000;
    user.pinisvalid = true;

	associatedBank=user.bank;//Bank_A;
	rollingBalance=user.balance;
	pinApproved=user.pinisvalid;

	return user;

}

//void ATM::updateBalance(User user, int newBalance){
void ATM::updateBalance(){
	// Set API data, for now just update user
	//user.balance=newBalance;
	user.balance=rollingBalance;

}



bool ATM::checkPIN(void){

	user = getAPIinfo();


	//if (user==NULL)
	if (associatedBank==Bank(0)){   //bc user.bank may be null, cross check with Bank
		BALANCE_ERROR();
		pinApproved=false;
	}
	else
		printWelcomeMsg();
	
	// Check API returns valid bank

	return pinApproved;   //return (user!=NULL);

}


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
		NEGATIVEBALANCE_ERROR();

	//cout << "This is rollingBalance: " << rollingBalance <<endl;

	return rollingBalance;
}


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
		//cout << "This is rollingBalance: " << rollingBalance <<endl;
	}
	else  //negative deposit (amtDeposit<0)
		NEGATIVEINPUT_ERROR();
		//throw invalid_argument("You have attempted to withdraw/deposit a negative amount. Please input a positive amount.\n");
		//NEGATIVEINPUT_ERROR());	

	return rollingBalance;

}

void ATM::logout(){

	//Though this is performed in destructor, in case object is not deleted yet in main.cpp
	logOut=true;
	pinApproved=false;
	CCnum.clear();
	PIN.clear();

	printLogoutMsg();
}


void ATM::showCC(void){

	//cout << CCnum << endl;
	if (!getCC().empty())
		cout << "This is your card number: " << string(CC_SIZE-4,'*') << getCC().substr(CC_SIZE-4,CC_SIZE) << endl;
	else //if (!pinApproved)
		INPUT_ERROR();
	//else
		//LOGOUT_ERROR();
	
}

void ATM::showPIN(void){
	if (!getPIN().empty())
		cout << "This is your PIN: " << string(PIN_SIZE-1,'*') << getPIN().substr(PIN_SIZE-1,PIN_SIZE) << endl;
	else //if (!pinApproved)
		INPUT_ERROR();
	//else
		//LOGOUT_ERROR();

}



