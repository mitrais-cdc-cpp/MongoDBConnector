#ifndef TEST_TESTSUITEMONGO_H_
#define TEST_TESTSUITEMONGO_H_

int main()
{
	int mode;
	Person person;
	string response;
	Connection mongo;
	string where,value,newValue;

	try
	{
		mongo.connect("localhost", 27017);
		Database db("MitraisTestDB");

		mainMenu:
		cout << "----------- Simple CRUD -----------" << endl;
		cout << "| 1. Insert                       |" << endl;
		cout << "| 2. Update                       |" << endl;
		cout << "| 3. Delete                       |" << endl;
		cout << "| 4. Show All                     |" << endl;
		cout << "| 5. Check Employee               |" << endl;
		cout << "| 0. Exit                         |" << endl;
		cout << "-----------------------------------" << endl;
		cout << "Select Mode: ";
		cin >> mode;

		switch(mode)
		{
			case 1:
			{
				// Insert Mode
				cout << "First Name? ";
				cin >> person.firstName;

				cout << "Last Name? ";
				cin >> person.lastName;

				cout << "Address? ";
				cin >> person.address;

				cout << "Inserting data to the database, please wait..."<<endl;
				mongo.sendRequest(*InsertEmployee(db, person));
				cout << "Data has been inserted to the database."<<endl;
			}
			break;
			case 2:
			{
				// Update Mode
				cout << "Update by (firstName/lastName)? ";
				cin >> where;

				cout << "Where " + where + " is ";
				cin >> value;

				cout << "Set new value ";
				cin >> newValue;

				cout << "Updating data, please wait..."<<endl;
				mongo.sendRequest(*UpdateEmployee(db, where, value, newValue));
				cout << "Data has been updated."<<endl;
			}
			break;
			case 3:
			{
				// Delete Mode
				Filter filter = createFilter();

				vector<Filter> filters;
				filters.push_back(filter);

				addFilter:
				cout << "Do you want to add criteria/filter (y/n)?";
				char answer;
				cin >> answer;

				if (answer == 'Y' || answer == 'y')
				{
					Filter moreFilter = createFilter();
					filters.push_back(filter);
					goto addFilter;
				}

				cout << "Deleting data, please wait..."<<endl;
				mongo.sendRequest(*DeleteEmployee(db, filters));
				cout << "Data has been deleted."<<endl;
			}
			break;
			case 4:
			{
				// Show all
				QueryRequest request("MitraisTestDB.Person");
				ResponseMessage response;

				mongo.sendRequest(request,response);
				showAll(response);
			}
			break;
			case 5:
			{
				// Check if Person exist
				cout << "Enter the Employee name you are looking for: ";
				cin >> value;

				QueryRequest request("MitraisTestDB.Person");
				ResponseMessage response;

				mongo.sendRequest(request,response);
				checkPerson(response, value);
			}
			break;
			case 0:
			{
				exit(0);
			}
			break;
		}

		cout << "Do you want to continue (Y/N)? ";
		cin >> response;
		if(response == "Y" || response == "y")
		{
			goto mainMenu;
		}
	}
	catch (ConnectionRefusedException& e)
	{
		cout << "Couldn't connect to " << e.message() << ". " << endl;
	}

	return 0;
}

#endif /* TEST_TESTSUITEMONGO_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
