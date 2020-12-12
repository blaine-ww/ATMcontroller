/* Print out messages


*/


void ATM::printWelcomeMsg(void){
	
	printSucessMsg();
	cout << "Welcome to ";
	switch(associatedBank){
    case Bank::Bank_A  : cout << "Bank of A.\n";   break;
    case Bank::Bank_B  : cout << "Bank of B.\n";   break;
    case Bank::Bank_C  : cout << "Bank of C.\n";   break;
    case Bank::Bank_D  : cout << "Bank of D.\n";   break;
    case Bank::Bank_E  : cout << "Bank of E.\n";   break;
    case Bank::Bank_F  : cout << "Bank of F.\n";   break;
    case Bank::Bank_G  : cout << "Bank of G.\n";   break;
    case Bank::Bank_H  : cout << "Bank of H.\n";   break;
    case Bank::Bank_I  : cout << "Bank of I.\n";   break;
    default: cout << "This banking card not listed with this ATM. Can withdraw with extra ATM fee.\n";
	}

}


void ATM::printDepositMsg(const int amtDeposit){
	cout << "\nYou are attempting to deposit $" << amtDeposit<<"\n";
}


void ATM::printWithdrawMsg(const int amtWithdraw){
	cout << "\nYou are attempting to withdraw $"<< amtWithdraw <<"\n";
}


void ATM::printProcessingMsg(){
	printf("\t.\n\t.\n\t.\n");
	
}

void ATM::printSucessMsg(){
	cout << "  << SUCCESS >>  ";
}

void ATM::printLogoutMsg(void){

	cout << "You have logged out. Have a nice day. :]\n\n\n";
}


void ATM::printBalance(void){

	//cout << setprecision(2) << fixed;

	if (pinApproved && !logOut && !getPIN().empty())
		cout << "You have $" << getBalance() << ".00 remaining in your account.\n\n"; 
	//else if (!pinApproved)
	//	LOGOUT_ERROR();
	else 
		BALANCE_ERROR();
		
}


