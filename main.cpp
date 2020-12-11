/* Implement a simple ATM controller

Write code for a simple ATM. It doesn't need any UI (either graphical or console), but a controller should be implemented and tested.

Requirements
At least the following flow should be implemented:

Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw


For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.

Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future. And even if we integrate it with them, we'd like to test our code. Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task, but testing the controller part (not including bank system, cash bin etc) is within the scope.

A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.



Based on your work, another engineer should be able to implement the user interface. You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.



You can simplify some complex real world problems if you think it's not worth illustrating in the project.



How to submit
Please upload the code for this project to GitHub or anywhere, and post a link to your repository below. Please attach the instruction to clone your project, build and run tests in README.md file in the root directory of the repository.

*/

#include "ATM.cpp"


int main(){

	cout <<"Welcome to this generic ATM!\n";

	ATM A;

	printf("\nThis is preliminary transaction for user A.\n");

	A.insertCC("6758-2943167nv1-043907"); 
	//A.insertCC(""); //To insert via console, can also directly input in main.cpp
	A.showCC();

	A.insertPIN("12324"); 
	//A.insertPIN("");//To insert via console
	A.showPIN();

	A.checkPIN();

	A.printBalance();

	//cout << "You are withdrawing.\n";

	A.deposit(11000); A.printBalance();

	//cout << "You are depositing.\n";

	A.withdraw(2000); A.printBalance();

	A.logout();

	//Attempting to access card number;
	A.showCC(); A.showPIN(); 
	//delete A;
	A.printBalance(); A.withdraw(100); A.deposit(70);

	




	printf("\n\nThis is preliminary transaction for user B.\n");

	ATM B("09257902159702127","12342");   //Currently any account that begins with 0 is invalid.

	B.checkPIN();

	//cout << "You are depositing.\n";

	B.deposit(999); B.withdraw(9); B.printBalance();	

	B.logout();





	printf("\n\nThis is preliminary transaction for user C.\n");

	ATM C;

	C.insertCC(); C.showCC();
	C.insertPIN(); C.showPIN();

	C.checkPIN();

	C.printBalance();

	C.withdraw(11000); C.printBalance();


	C.deposit(100); C.printBalance();

	C.withdraw(-999); C.printBalance();

	C.deposit(-1); C.printBalance();

	C.logout();



	cout << "ATM Done\n";


}
