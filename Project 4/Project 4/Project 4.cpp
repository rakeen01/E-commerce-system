/*

Name of Programmer: Md Rakeen Murtaza
Project 4
CS 1337.012

Description of the program:

The following program demonstrates a fully-functional e-commerce system.

The program first reads in available product information from a file named "ProductData.csv" and stores it in a 
dynamically allocated linked list called inventoryList, where the nodes are actually instances of the Inventory class. 
Then the program asks the user whether he/she is an admin or a customer.

For a customer: The program asks the user what products they would like to buy and adds each of those products
to the shopping cart.  The program first gets the user's information, gets the user's choice of products, and 
the quantity desired, using a Customer class object. The user's choice of products is validated with the
information in the inventoryList until the user is done. For each valid request by the user, the program updates 
information in the inventoryList and also the user's 'shopping cart' called cartList, which is another linked list 
where the nodes are instances of the Customer class object. After the customer is done shopping, the inventory in 
"ProductData.csv" is updated via the inventoryList for the next user.

For an admin: The admin class is an aggregate of the Inventory class object inventoryList. It also contains
the admin information. When the user selects the admin option, the user is asked to log in where the login details are validated 
with the information in the Admin class object. Once login is successful, the admin can add/delete a product, update quantity/cost 
of a product in the inventoryList. After the admin is done, the inventory in "ProductData.csv" is updated via the inventoryList 
for the next user.

*/

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	// Declare variables

	LinkedList* inventoryList = nullptr;
	LinkedList* cartList = nullptr;

	fstream dataFile;
	dataFile.open("ProductData.csv", ios::in | ios::out | ios::eofbit);

	// Test for file open errors

	if (dataFile.fail()) {

		cout << "The product information could not found." << endl;
		cout << "Please try again later." << endl;
	}

	else {

		// Declare variables

		string userChoice, userAddress, userCity, userState, userName, password;
		int userZIP;
		int userOption = 3;
		bool loginStatus = false;
		string firstName, lastName;
		int customerChoice = 4;

		Inventory* todaysInventory = new Inventory(inventoryList, dataFile);

		do {
			cout << "Choose an Option: " << endl;
			cout << "1. Type 1 for Admin" << endl;
			cout << "2. Type 2 for Customer" << endl;
			cout << "3. Type 3 for Exit" << endl;
			cout << "Your choice: ";
			cin >> userOption;

			// Validate input

			while (userOption < 1 || userOption > 3) {
				cout << "Value must be 1, 2 or 3!" << endl;
				cout << "Choose an Option: " << endl;
				cout << "1. Type 1 for Admin" << endl;
				cout << "2. Type 2 for Customer" << endl;
				cout << "3. Type 3 for Exit" << endl;
				cout << "Your choice: ";
				cin >> userOption;
			}

			// Admin mode

			if (userOption == 1) {
				Admin Rakeen("rakeen01", "82aaBB11");
				cout << "Enter your username: ";
				cin >> userName;
				cout << "Enter your password: ";
				cin >> password;
				loginStatus = Rakeen.loginStatus(userName, password, inventoryList, todaysInventory);

				if (loginStatus) {
					cout << "Inventory updated!" << endl;
				}
			}

			// Customer mode

			else if (userOption == 2) {
				cout << "Enter your first name: ";
				cin >> firstName;
				cout << "Enter your last name: ";
				cin >> lastName;
				cout << "Please enter your street address: ";
				cin.ignore();
				getline(cin, userAddress);
				cout << "Please enter your city: ";
				getline(cin, userCity);
				cout << "Please enter your state: ";
				getline(cin, userState);
				cout << "Please enter your ZIP code: ";
				cin >> userZIP;

				Customer* todaysCustomer = new Customer(cartList, firstName, lastName, userAddress, userCity, userState, userZIP);

				fstream invoiceFile = todaysCustomer->createInvoiceFile();

				if (invoiceFile.fail()) {
					cout << "Unfortunately the invoice could not be created. ";
					cout << "Please try again later." << endl;
				}

				else {
					
					todaysCustomer->setInventoryList(inventoryList);

					do {
						cout << "Do you want to: " << endl;
						cout << "1. Add an item to the shopping cart?" << endl;
						cout << "2. Delete an item from the shopping cart?" << endl;
						cout << "3. Display the shopping cart?" << endl;
						cout << "4. Finish shopping?" << endl;
						cout << "Enter your choice: ";
						cin >> customerChoice;

						// Validate input

						while (customerChoice != 1 && customerChoice != 2 && customerChoice != 3 && customerChoice != 4) {
							cout << "That is an invalid choice" << endl;
							cout << "Do you want to: " << endl;
							cout << "1. Add an item to the shopping cart?" << endl;
							cout << "2. Delete an item from the shopping cart?" << endl;
							cout << "3. Display the shopping cart?" << endl;
							cout << "4. Finish shopping?" << endl;
							cout << "Enter your choice: ";
							cin >> customerChoice;
						}

						// Add item

						if (customerChoice == 1) {
							cout << "Enter the name of the product you would like to buy: ";
							cin >> userChoice;
							todaysCustomer->addItem(userChoice);
						}

						// Delete item

						else if (customerChoice == 2) {
							cout << "Enter the name of the product you would like to remove: ";
							cin >> userChoice;
							cartList->deleteNode(cartList, userChoice);
						}

						// show cart

						else if (customerChoice == 3) {
							todaysCustomer->showCart();
						}

					} while (customerChoice != 4);
				}
				todaysCustomer->updateInvoiceFile(invoiceFile, cartList);
				cartList->deleteList(cartList);
				delete todaysCustomer;
			}

			inventoryList->editProductData(inventoryList, dataFile);

		} while (userOption != 3);

		inventoryList->deleteList(inventoryList);
		delete todaysInventory;
	}

	return 0;
}
