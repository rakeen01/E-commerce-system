#pragma once

#include "pch.h"
#include "Inventory.h"
#include <iostream>
#include <string>

using namespace std;

class Admin {

private:
	string username;
	string password;

public:

	// Constructors

	Admin();
	Admin(string username, string password);
	bool loginStatus(string nameChoice, string passwordChoice, LinkedList* &headRef, Inventory* todaysInventory);
	Inventory* adminInv;

	// Destructor

	~Admin();
};