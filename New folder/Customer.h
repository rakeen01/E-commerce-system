#pragma once

#include "pch.h"
#include "Linked List.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Customer : public LinkedList {

private:
	LinkedList* cartList;
	LinkedList* inventoryList;
	string invoiceFileName;
	string firstName;
	string lastName;
	string userAddress;
	string userCity;
	string userState;
	int userZIP;

public:
	Customer();
	Customer(LinkedList* &headRef, string firstNameInput, string lastNameInput, string address, string city, string state, int ZIP);
	void showCart();
	fstream createInvoiceFile();
	void updateInvoiceFile(fstream &invoiceFile, LinkedList* headRef);
	void addItem(string userChoice);
	void setInventoryList(LinkedList* invList);
	~Customer();
};