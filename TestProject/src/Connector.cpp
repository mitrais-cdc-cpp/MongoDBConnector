//============================================================================
// Name        : Connector.cpp
// Author      : mitrais-cdc-cpp
// Version     :
// Copyright   : Copyleft
// Description : Connector for MongoDB
//============================================================================

#include "../inc/Connector.hpp"

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
				cout << "Delete by (firstName/lastName)? ";
				cin >> where;

				cout << "Where " << where << " is ";
				cin >> value;

				cout << "Deleting data, please wait..."<<endl;
				mongo.sendRequest(*DeleteEmployee(db, where, value));
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


SharedPtr<InsertRequest> InsertEmployee(Database &db, Person &person)
{
	DateTime now;
	Document::Ptr personPtr = new Document();

	personPtr->add("firstName", person.firstName);
	personPtr->add("lastName", person.lastName);
	personPtr->add("address", person.address);
	personPtr->add("createdDate", now.timestamp());
	personPtr->add("lastUpdated", NullValue());

	SharedPtr<InsertRequest> insertRequest = db.createInsertRequest("Person");
	insertRequest->documents().push_back(personPtr);

	return insertRequest;
}


SharedPtr<UpdateRequest> UpdateEmployee(Database &db,
		string whereColumn, string whereValue, string newValue)
{
	SharedPtr<UpdateRequest> updateRequest = db.createUpdateRequest("Person");

	Document& selector = updateRequest->selector();
	Document& update = updateRequest->update();

	selector.add(whereColumn, whereValue);
	update.addNewDocument("$set").add(whereColumn, newValue);

	return updateRequest;
}


SharedPtr<DeleteRequest> DeleteEmployee(Database &db,
		string whereColumn, string whereValue)
{
	SharedPtr<DeleteRequest> deleteRequest = db.createDeleteRequest("Person");

	Document& selector = deleteRequest->selector();
	selector.add(whereColumn, whereValue);

	return deleteRequest;
}


void showAll(ResponseMessage &response)
{
	int numOfDoc = response.documents().size();

	if(numOfDoc > 0)
	{
		try{
			cout << "------------------- Employee Data -------------------"<<endl;
			cout << "No.   |   First Name   |   LastName   |   Address   |" << endl;
			cout << "-----------------------------------------------------" << endl;

			for(int i=0; i < numOfDoc; i++)
			{
				Person obj;
				Document::Ptr doc = response.documents()[i];

				obj.firstName = doc->get<string>("firstName");
				obj.lastName = doc->get<string>("lastName");
				obj.address = doc->get<string>("address");

				cout << "  " << (i + 1) << "   |   "<< obj.firstName << "   |   " << obj.lastName << "   |   "<< obj.address<< endl ;
			}
		}
		catch(NotFoundException& nfe){
			cout << nfe.message() + " not found."<< endl;
		}
	}
	else
	{
		cout << "There are no employee data on database now."<<endl;
	}
}
