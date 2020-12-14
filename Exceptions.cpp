/* Error Compilation Messages
Note: Did not want to clutter main.cpp with exceptions (try catch) so simplified error messages to sub-function calls
@file Exceptions.cpp */


/** Outputs error message for invalid card number inserted  
  */
void ATM::CC_ERROR(){
	
	cout <<"Please insert " << CC_SIZE <<" card number. All trailing characters, non-digits, and excessive digits will be ignored.\n";
}


/**  Outputs error message for invalid PIN passcode inserted  
  */
void ATM::PIN_ERROR(){
	
	cout <<"Please insert " << PIN_SIZE <<" digit PIN. All trailing characters, non-digits, and excessive digits will be ignored.\n";
}


/** Ouputs error message for invalid access to account balance with incorrect card or 			PIN combination */
void ATM::BALANCE_ERROR(){
	
	cout << "Invalid card number and/or PIN combination. Cannot access account balance.\n";
}


/** Outputs error message for user attempting to access transactions without inserting 			card number */
void ATM::INPUT_ERROR(){
	cout << "You have not entered a valid card number yet.\n\n";
}


/** Outputs error message for insufficient funds for withdrawal
  */
void ATM::OVERDRAWN_ERROR(){
	cout << "You do not have enough to withdraw desired amount. Please try another amount.\n";
}


/** Outputs error message for user attempting to withdraw/deposit negative amount 
 */
void ATM::NEGATIVEINPUT_ERROR(){
	cout << "You have attempted to withdraw/deposit a negative amount. Please input a positive amount.\n";
}


/** Outputs error message for user attempting to access transactions after logging out 
  */
void ATM::LOGOUT_ERROR(){
	cout << "You have already logged out.\n\n\n";
}


