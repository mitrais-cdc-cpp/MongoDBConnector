/*
 * MainProgram.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: developer
 */

#include "../inc/Connector.hpp"

using namespace CDC;

int main() {
	CPP::Connector connector;
	CPP::Person person;

	int mode;
	string response;
	string where, value, newValue;

	try {

		mainMenu: cout << "----------- Simple CRUD -----------" << endl;
		cout << "| 1. Insert                       |" << endl;
		cout << "| 2. Update                       |" << endl;
		cout << "| 3. Delete                       |" << endl;
		cout << "| 4. Show All                     |" << endl;
		cout << "| 5. Check Employee               |" << endl;
		cout << "| 0. Exit                         |" << endl;
		cout << "-----------------------------------" << endl;
		cout << "Select Mode: ";
		cin >> mode;

		switch (mode) {
			case 1: {
				// Insert Mode
				cout << "First Name? ";
				cin >> person.firstName;

				cout << "Last Name? ";
				cin >> person.lastName;

				cout << "Address? ";
				cin >> person.address;

				cout << "Inserting data to the database, please wait..." << endl;

				connector.Insert(person);

				cout << "Data has been inserted to the database." << endl;
			}
			break;
			case 2: {
				// Update Mode
				cout << "Update by (firstName/lastName)? ";
				cin >> where;

				cout << "Where " + where + " is ";
				cin >> value;

				cout << "Set new value ";
				cin >> newValue;

				cout << "Updating data, please wait..." << endl;
				// TODO
//				mongo.sendRequest(*UpdateEmployee(db, where, value, newValue));
				cout << "Data has been updated." << endl;
			}
			break;
			case 3: {
				// Delete Mode
				CPP::Filter filter = connector.createFilter();

				vector<CPP::Filter> filters;
				filters.push_back(filter);

				addFilter: cout << "Do you want to add criteria/filter (y/n)?";
				char answer;
				cin >> answer;

				if (answer == 'Y' || answer == 'y') {
					CPP::Filter moreFilter = connector.createFilter();
					filters.push_back(filter);
					goto addFilter;
				}

				cout << "Deleting data, please wait..." << endl;
				connector.Delete(filters);
				cout << "Data has been deleted." << endl;
			}
			break;
			case 4: {
				// Show all
				connector.showAll();
			}
			break;
			case 5: {
				// Check if Person exist
				string empName;
				cout << "Enter the Employee name you are looking for: ";
				cin >> empName;
//				connector.checkIsExist(empName);
			}
			break;
			case 0:{
				exit(0);
			}
			break;
		}

		cout << "Do you want to continue (Y/N)? ";
		cin >> response;

		if (response == "Y" || response == "y") {
			goto mainMenu;
		}
	}
	catch (Net::ConnectionRefusedException& e) {
		cout << "Couldn't connect to " << e.message() << ". " << endl;
	}

	return 0;
}
