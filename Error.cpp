/* Error Compilation Messages

*/

void ATM::CC_ERROR(){
	
	cout <<"Please insert " << CC_SIZE <<" card number. All trailing characters, non-digits, and excessive digits will be ignored.\n";
}


void ATM::PIN_ERROR(){
	
	cout <<"Please insert " << PIN_SIZE <<" digit PIN. All trailing characters, non-digits, and excessive digits will be ignored.\n";
}


void ATM::BALANCE_ERROR(){
	
	cout << "Invalid card number and PIN combination. Cannot access account balance.\n";
}

void ATM::NEGATIVEBALANCE_ERROR(){
	cout << "You do not have enough to withdraw desired amount. Please try another amount.\n";
}

void ATM::NEGATIVEINPUT_ERROR(){
	cout << "You have attempted to withdraw/deposit a negative amount. Please input a positive amount.\n";
}


void ATM::LOGOUT_ERROR(){
	cout << "You have already logged out.\n\n\n";
}


void ATM::INPUT_ERROR(){
	cout << "You have not entered a valid card number yet.\n\n";
}