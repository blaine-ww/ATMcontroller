# Implement a simple ATM controller
Date: 12.11.2020
Author: [blaine-ww](http://www.github.com/blaine-ww)
@file _README.md_

## Scope

> Write code for a simple ATM. It doesn't need any UI (either graphical or console), but a controller should be implemented and tested.

## Requirements
> At least the following flow should be implemented:

* Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw

* For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.

> Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future. And even if we integrate it with them, we'd like to test our code. Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task, but testing the controller part (not including bank system, cash bin etc) is within the scope.

> A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.

> Based on your work, another engineer should be able to implement the user interface. You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.

> You can simplify some complex real world problems if you think it's not worth illustrating in the project.



## Build instructions:

* Clone   `git clone http://www.github.com/blaine-ww/ATMcontroller`

* Navigate `cd $_filepath_to_root_directory_/ATMcontroller`

* Compile `g++ -std=c++11 $_file_base_name_ -o $_file_`
		  `g++ -std=c++11 main.cpp -o main`

* Execute `./$+file_`
		  `./main.exe`



### Public Functions:
All examples below can be found in @file _main.cpp_

* Declare ATM session
	Each ATM object is defined as a separate ATM session/user;
	`ATM A;` 
	`ATM B(string num1, string num2);`
	`ATM* C = new ATM();`
	`ATM* D = new ATM(string num1, string num2);`

* Insert Card
	To insert card number, enter a string of 16-digits either as a paramter to the insertCC function or invoke insertCC() to enter the 16-digits via console.
	`A.insertCC("_string of digits_");`
	`C.insertCC();`   
	Note: ATM object B and D have already predeclared card number.

* Show Card
	To print out censored card number `**** **** **** _last_4_digit_`.
	`A.showCC();`

* Insert PIN
	`A.insertPIN("_string of digits_");`
	`C.insertPIN();`
	Note: ATM object B and D have already predeclared PIN passcode.

* Show Pin
	To print out censored PIN passcode `***_last_digit_`.
	`A.showPIN();`

* Check Pin
	To indicate whether valid card number and PIN passcode was entered.
	Must return true before user can access withdrawal, deposit, and balance transactions.
	`A.checkPIN();` & `B.checkPIN();` & `C.checkPIN();` & `D.checkPIN();`

* Withdraw
	Indicate whole dollar amount `num` to withdraw from ATM.
	Amount must be positive integer and not cause overdraft.
	`A.withdraw(int num);`

* Deposit
	Indicate whole dollar amount `num` to deposit into ATM.
	Amount must be positive integer.
	`A.deposit(int num);`

* Print Balance
	Access and print out present balance of bank account.
	To see updated balance after withdrawal or deposit, printBalance() must be called again.
	`A.printBalance();`

* LogOut
	To stop current session, and no longer have access to ATM transactions in regards to declared ATM object/user.
	`A.logOut();`



### Private Members

* Inserted card number
	* `CCnum` represented with `CC_size` length digit string

* Inserted PIN passcode
	* `PIN` represented with `PIN_size` length digit string

* Pin Validation
	* `pinApproved` is `true` if PIN accepted else `false` if incorrect, prevents invalid access to account without approved PIN

* LogOut Validation
	* `logOut` is `true` if called by user, prevents invalid access without re-entering card number

* Present balance (including ATM transactions)
	* `rollingBalance` retrieved dollar amount from selected user account and updated by user 

* Bank Info from API
	* `associatedBank` retrieved associated bank for selected user account 
	_Note: Bank Selection is simplified into enum struct where bank is predetermined by
	first digit of card number inputted._




### Private Functions:

* Retrieve validated card number
	* `getCC();` @return CCnum string of valid inserted card number

* Retrieve validated PIN passcode
	* `getPIN();` @return PIN string of valid inserted PIN passcode

* Retrieve associated Bank with card number
	* `getBank();` @return Bank enum member associated with first digit of card number

* Retrieve account balance reflected from API
	* `getBalance();` @return rollingBalance present account balance in whole dollars



### Protected Functions:

* User struct member to store API info
	Return API data, parse, and assign it to the User struct
	__Note this is artificial data, that would otherwise be produced via API call__
	```
	struct User{
		Bank bank;		 // Linked Bank
		int balance;	 // Checking balance reflected after ATM login
		bool pinisvalid; // PIN cross-checked with API, prevents unauthorized access
	};
	```
	

* Retrieve API info to store in user struct member
	* `getAPIinfo()` @return user
	
	Store returned API data into user members and ATM members
	```
	int b = CCnum[0]-'0';		// Taking the first digit of user input card number to assign associated Bank
	```

    __Note this is artificial data, that would otherwise be produced via API call__
    ```
    user.bank = Bank(b);		// Artificial Bank assignment through enum struct
    user.balance = 1000;		// Artificial dollar balance reflected from user account
    user.pinisvalid = true;		// Artificial approval of PIN inserted
    ```

    Assign API data to ATM class members
	```
	associatedBank=user.bank;
	rollingBalance=user.balance;
	pinApproved=user.pinisvalid; 
	```


* Return new updated balance to API after user finishes ATM transaction
	* `updateBalance()` 
	Updates account balance from ATM transactions (withdrawal & deposits) and sets new balance for API data 



## Examples:

1. Example A : Valid Account

	`printf("\nThis is preliminary transaction for user A.\n");`

	`ATM A;`	
	
	Directly input card number in main.cpp
	_Note: All non-digit characters inputted are ignored within `insertCC()`
	and only intakes first `CC_SIZE`(16) digits_
	`A.insertCC("6758-2943167nv1-043907"); A.showCC();` 
	
	Directly input PIN passcode in main.cpp
	_Note: All non-digit characters inputted are ignored within `insertPIN()`
	and only intakes first `PIN_SIZE`(4) digits_
	`A.insertPIN("12324"); A.showPIN();`
	
	Check if PIN passcode approved, if so, print account balance	
	`A.checkPIN(); A.printBalance();`
	
	Deposit $11,000 USD, print reflected balance
	`A.deposit(11000); A.printBalance();`

	Withdraw $2,000 USD, print reflected balance
	`A.withdraw(2000); A.printBalance();`

	Log out ATM object/user A and end session with this account
	`A.logout();`
	
	> __OUTPUT__

	> This is preliminary transaction for user A.
	
	> Please insert your debit card number followed by Enter:                                                               
	> This is your card number: **** **** **** 0439

	> Please insert your PIN followed by Enter:

	> This is your PIN: ****2

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  Welcome to Bank of F.

	> You have $1000.00 remaining in your account. 

	> You are attempting to deposit $11000

	> 		.

	>       . 

	>		.

	> << SUCCESS >> You have $12000.00 remaining in your account.

	> You are attempting to withdraw $2000

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  You have $10000.00 remaining in your account.

	> You have logged out. Have a nice day. :]

	> You have not entered a valid card number yet.

	> You have not entered a valid card number yet.

	> Invalid card number and/or PIN combination. Cannot access account balance.

	> You are attempting to withdraw $100

	> You have not entered a valid card number yet.

	> You are attempting to deposit $70

	> You have not entered a valid card number yet.



2. Example B : Invalid Account

	`printf("\n\nThis is preliminary transaction for user B.\n");`

	_Note: Since this ATM controller does not have access to a Banking API, artificial 
	banking data in `Bank` enum has pre-determined any account that begins with 0 is 
	invalid._
	`ATM B("09257902159702127","12342");`

	PIN passcode will be denied
	`B.checkPIN();`

	All transactions: withdrawal, deposit, and printBalance will be denied
	```
	B.deposit(999); B.printBalance();
	B.withdraw(9); B.printBalance();
	```	

	`B.logout();`
	
	> __OUTPUT__
	
	> This is preliminary transaction for user B.

	> Invalid card number and/or PIN combination. Cannot access account balance.

	> You are attempting to deposit $999

	> 		.

	>       . 

	>		.

	> You have not entered a valid card number yet.

	> Invalid card number and/or PIN combination. Cannot access account balance. 

	> You are attempting to withdraw $9

	> You have not entered a valid card number yet.

	> Invalid card number and/or PIN combination. Cannot access account balance.

	> You have logged out. Have a nice day. :]   



3. Example C : Valid Account
	
	```
	printf("\n\nThis is preliminary transaction for user C.\n");
	ATM C;
	```
	To insert card number via console, type in valid card number
	_Note: All non-digit characters inputted are ignored within `insertCC()`
	and only intakes first `CC_SIZE`(16) digits_
	`C.insertCC(); C.showCC();` 
	
	To insert PIN passcode via console, type in valid PIN passcode
	_Note: All non-digit characters inputted are ignored within `insertPIN()`
	and only intakes first `PIN_SIZE`(4) digits_
	`C.insertPIN(); C.showPIN();`

	PIN validated, then print account balance
	`C.checkPIN(); C.printBalance();`

	Withdraw $11,000 USD denied due to overdrawn balance
	```
	C.withdraw(11000); C.printBalance();
	C.deposit(100); C.printBalance();
	```

	Returns error cannot deposit negative amount, balance remains unchanged
	`C.deposit(-1); C.printBalance();`

	`C.logout();`
	
	> __OUTPUT__
	
	> This is preliminary transaction for user C.

	> Please insert your debit card number followed by Enter: 908963123479580697

	> This is your card number: **** **** **** 5806 

	> Please insert your PIN followed by Enter: 978439833456yhbvcer87

	> This is your PIN: xxx4

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  Welcome to Bank of I.

	> You have $1000.00 remaining in your account.

	> You are attempting to withdraw $11000

	> You do not have enough to withdraw desired amount. Please try another amount.

	> You have $1000.00 remaining in your account.

	> You are attempting to deposit $100

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  You have $1100.00 remaining in your account.

	> You are attempting to deposit $-1

	> You have attempted to withdraw/deposit a negative amount. Please input a positive amount.

	> You have $1100.00 remaining in your account.

	> You have logged out. Have a nice day. :] 



4. Example D : Valid Account
	
	`printf("\nThis is preliminary transaction for user D.\n");`
	
	Declare ATM object with pointer
	`ATM* D = new ATM(); 	//ATM D; `
	
	Directly input card number in main.cpp
	```
	D->insertCC("2943167043907098");  //D->insertCC(""); To insert via console, can also directly input in main.cpp
	D->showCC(); 
	```
	
	Directly input PIN passcode in main.cpp
	```
	D->insertPIN("9876"); 	//D->insertPIN(""); To insert via console
	D->showPIN();
	D->checkPIN(); D->printBalance();
	```

	Deposit $1,234 USD and withdraw $100 USD 
	```
	D->deposit(1234); D->printBalance(); //cout << "You are depositing.\n";
	D->withdraw(100); D->printBalance(); //cout << "You are withdrawing.\n";
	```
	
	`D->logout();` 

	Delete pointer object.
	`delete D; cout <<"Deleted user D\n";`
	
	Attempting to access card number after logOut() and deleting user object (access denied)
	```
	D->showCC(); D->showPIN(); 
	D->printBalance(); D->withdraw(100); D->deposit(70);
	```

	> __OUTPUT__

	> This is preliminary transaction for user D.

	> Please insert your debit card number followed by Enter:

	> This is your card number: **** **** **** 7098

	> Please insert your PIN followed by Enter:

	> This is your PIN: xxx6

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  Welcome to Bank of B.

	> You have $1000.00 remaining in your account.

	> You are attempting to deposit $1234

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  You have $2234.00 remaining in your account.

	> You are attempting to withdraw $100  

	> 		.

	>       . 

	>		.

	> << SUCCESS >>  You have $2134.00 remaining in your account.

	> You have logged out. Have a nice day. :] 

	> Deleted user D

	> You have not entered a valid card number yet.

	> You have not entered a valid card number yet.

	> Invalid card number and/or PIN combination. Cannot access account balance.

	> You are attempting to withdraw $100

	> You have not entered a valid card number yet.

	> You are attempting to deposit $70

	> You have not entered a valid card number yet.
