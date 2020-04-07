
#include "pch.h"
#include "Inventory.h"
#include "Admin.h"
#include <iostream>
#include <string>

using namespace std;

Admin::Admin() {
	username = "admin";
	password = "12345";
}

Admin::Admin(string newUsername, string newPassword) {
	username = newUsername;
	password = newPassword;
}

// This function verifies admin's identity and allows login

bool Admin::loginStatus(string nameChoice, string passwordChoice, LinkedList* &headRef, Inventory* todaysInventory) {

	bool condition = false;
	int adminChoice = 4;
	string userChoice;

	if (username == nameChoice && password == passwordChoice) {
		condition = true;
		cout << endl;
		cout << "Login successful!" << endl;
		cout << endl;
		cout << "To add a product, press 1. " << endl;
		cout << "To delete a product, press 2." << endl;
		cout << "To update the quantity of a product, press 3." << endl;
		cout << "To update the cost of a product, press 4: ";
		cin >> adminChoice;

		while (adminChoice != 1 && adminChoice != 2 && adminChoice != 3 && adminChoice !=4) {
			cout << endl;
			cout << "That is an invalid choice." << endl;
			cout << "To add a product, press 1. " << endl;
			cout << "To delete a product, press 2." << endl;
			cout << "To update the quantity of a product, press 3." << endl;
			cout << "To update the cost of a product, press 4: ";
			cin >> adminChoice;
		}

		// Add a product

		if (adminChoice == 1) {

			// Get new product information
			cout << "Enter the Item Number of your new product: ";
			cin >> headRef->TempStruct->itemNumber;
			cout << "Enter the name of your new product: ";
			cin >> headRef->TempStruct->itemName;
			cout << "Enter the Unit Price of your new product: ";
			cin >> headRef->TempStruct->cost;
			cout << "Enter the quantity of your new product you have in stock: ";
			cin >> headRef->TempStruct->Qty;

			// Add a new node to linked list containing new product's information

			*headRef += headRef->TempStruct;
		}

		// Delete a product

		else if (adminChoice == 2) {
			cout << "Enter the item name of the product to be deleted: ";
			cin >> userChoice;
			headRef->deleteNode(headRef, userChoice);
		}

		// Update Quantity

		else if (adminChoice == 3) {
			todaysInventory->updateQty();
		}

		else if (adminChoice == 4) {
			todaysInventory->updateCost();
		}
	}

	else {
		cout << endl;
		cout << "Incorrect name or password!" << endl;
	}

	return condition;
}

Admin::~Admin() {

}