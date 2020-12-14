/** Simplified Implementation of ATM Controller

Refer to @file README.md for further clarfications

Author: blaine-ww 

@file main.cpp */

#include "ATM.cpp"

int main(){

	cout <<"Welcome to this generic ATM!\n";

	printf("\nThis is preliminary transaction for user A.\n");

	ATM A;

	A.insertCC("6758-2943167nv1-043907"); A.showCC();
	//A.insertCC(""); //To insert via console, can also directly input in main.cpp
	
	A.insertPIN("12324"); A.showPIN();
	//A.insertPIN("");//To insert via console

	A.checkPIN(); A.printBalance();

	A.deposit(11000); A.printBalance();	
	A.withdraw(2000); A.printBalance();

	A.logout();
	
	//Attempting to access card number after logOut()
	A.showCC(); A.showPIN(); 
	
	A.printBalance(); A.withdraw(100); A.deposit(70);





	printf("\n\nThis is preliminary transaction for user B.\n");

	ATM B("09257902159702127","12342");   //Currently any account that begins with 0 is invalid. Refer to README.md or Bank enum for more details.

	B.checkPIN();

	B.deposit(999); B.printBalance();	//Denied access to deposit, withdraw, and balance
	B.withdraw(9); B.printBalance();	

	B.logout();





	printf("\n\nThis is preliminary transaction for user C.\n");

	ATM C;

	C.insertCC(); C.showCC();
	C.insertPIN(); C.showPIN();

	C.checkPIN(); C.printBalance();

	C.withdraw(11000); C.printBalance();	//Denied due to overdrawn balance
	C.deposit(100); C.printBalance();

	C.deposit(-1); C.printBalance();		//Denied due to negative int input

	C.logout();





	printf("\nThis is preliminary transaction for user D.\n");
	
	ATM* D = new ATM(); 	//ATM D;

	D->insertCC("2943167043907098");  //D->insertCC(""); To insert via console, can also directly input in main.cpp
	D->showCC();

	D->insertPIN("9876"); 	//D->insertPIN(""); To insert via console
	D->showPIN();

	D->checkPIN(); D->printBalance();

	D->deposit(1234); D->printBalance(); //cout << "You are depositing.\n";
	D->withdraw(100); D->printBalance(); //cout << "You are withdrawing.\n";

	D->logout();

	delete D; cout <<"Deleted user D\n";
	
	//Attempting to access card number after deleting user object;
	D->showCC(); D->showPIN(); 
	
	D->printBalance(); D->withdraw(100); D->deposit(70);


	cout << "\n\nATM Done\n";

}
