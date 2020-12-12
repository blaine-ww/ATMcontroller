

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

	//C.withdraw("ab");
	/*try {
		C.withdraw('ab'); 
	}

	catch (invalid_argument& e){
		cerr << e.what() << endl;
		return -1;
	}*/

	C.printBalance();

	C.deposit(-1); C.printBalance();

	C.logout();



	ATM* D = new ATM(); //ATM A;

	printf("\nThis is preliminary transaction for user D.\n");

	D->insertCC("2943167043907098"); 
	//A.insertCC(""); //To insert via console, can also directly input in main.cpp
	D->showCC();

	D->insertPIN("9876"); 
	//A.insertPIN("");//To insert via console
	D->showPIN();

	D->checkPIN();

	D->printBalance();

	//cout << "You are withdrawing.\n";

	D->deposit(11000); D->printBalance();

	//cout << "You are depositing.\n";

	D->withdraw(2000); D->printBalance();

	//D->logout();

	delete D; cout <<"Deleted user D\n";
	
	//Attempting to access card number;
	D->showCC(); D->showPIN(); 
	
	D->printBalance(); D->withdraw(100); D->deposit(70);


	cout << "\n\nATM Done\n";


}
