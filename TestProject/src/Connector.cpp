//============================================================================
// Name        : Connector.cpp
// Author      : mitrais-cdc-cpp
// Version     :
// Copyright   : Copyleft
// Description : Connector for MongoDB
//============================================================================

#include "../inc/Connector.hpp"

using namespace CDC;

// Global static pointer used to ensure a single instance of the class.
CPP::Connector* CPP::Connector::m_pInstance = NULL;

/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/
CPP::Connector* CPP::Connector::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Connector;
	}

	return m_pInstance;
}

void CPP::Connector::Insert(Person &person) {
	DateTime now;
	MongoDB::Document::Ptr personPtr = new MongoDB::Document();

	personPtr->add("firstName", person.firstName);
	personPtr->add("lastName", person.lastName);
	personPtr->add("address", person.address);
	personPtr->add("createdDate", now.timestamp());
	personPtr->add("lastUpdated", MongoDB::NullValue());

	MongoDB::Database db("MitraisTestDB");
	SharedPtr<MongoDB::InsertRequest> insertRequest = db.createInsertRequest(
			"Person");
	insertRequest->documents().push_back(personPtr);

	MongoDB::Connection mongo;
	mongo.connect("localhost", 27017);

	mongo.sendRequest(*insertRequest);
}

void CPP::Connector::Update(MongoDB::Database &db,
		string whereColumn, string whereValue, string newValue) {
	SharedPtr<MongoDB::UpdateRequest> updateRequest = db.createUpdateRequest(
			"Person");

	MongoDB::Document& selector = updateRequest->selector();
	MongoDB::Document& update = updateRequest->update();

	selector.add(whereColumn, whereValue);
	update.addNewDocument("$set").add(whereColumn, newValue);

	MongoDB::Connection mongo;
	mongo.connect("localhost", 27017);

	mongo.sendRequest(*updateRequest);
}

void CPP::Connector::Delete(vector<Filter> &filters) {
	MongoDB::Database db("MitraisTestDB");
	SharedPtr<MongoDB::DeleteRequest> deleteRequest = db.createDeleteRequest("Person");

	if (!filters.empty()) {
		MongoDB::Document& selector = deleteRequest->selector();

		for (vector<Filter>::iterator it = filters.begin(); it != filters.end();
				++it) {
			string field = it->field;
			string value = it->value;
			Opr op = it->op;

			selector.addNewDocument(field);

			switch (op) {
			case EQUALS: {
				selector.add("$eq", value);
			}
				break;
			case NOT_EQUALS: {
				selector.add("$ne", value);
			}
				break;
			case GREATER_THAN: {
				selector.add("$gt", value);
			}
				break;
			case GREATER_THAN_EQUALS: {
				selector.add("$gte", value);
			}
				break;
			case LESS_THAN: {
				selector.add("$lt", value);
			}
				break;
			case LESS_THAN_EQUALS: {
				selector.add("$lte", value);
			}
				break;
			case IN: {
				selector.add("$in", value);
			}
				break;
			case NOT_IN: {
				selector.add("$nin", value);
			}
				break;
			}
		}
	}

	MongoDB::Connection mongo;
	mongo.connect("localhost", 27017);

	mongo.sendRequest(*deleteRequest);
}

template<typename T>
vector<T> CPP::Connector::GetAll(MongoDB::ResponseMessage &response) {
	vector<T> collection;
	try{
		int size = response.documents().size();
		for (int i = 0; i < size; i++) {
			T obj;
			MongoDB::Document::Ptr doc = response.documents()[i];

			obj.firstName = doc->get<string>("firstName");
			obj.lastName = doc->get<string>("lastName");
			obj.address = doc->get<string>("address");

			collection.push_back(obj);
		}
	}
	catch (const std::bad_alloc& e) {
		std::cout << "Allocation failed: " << e.what() << '\n';
	}

	return collection;
}

void CPP::Connector::showAll() {
	cout << "------------------- Employee Data -------------------" << endl;
	cout << "No.   |   First Name   |   LastName   |   Address   |" << endl;
	cout << "-----------------------------------------------------" << endl;

	try {
		MongoDB::QueryRequest request("MitraisTestDB.Person");
		MongoDB::ResponseMessage response;

		MongoDB::Connection mongo;
		mongo.connect("localhost", 27017);

		mongo.sendRequest(request, response);

		vector<Person> employees = GetAll<Person>(response);
		int size = employees.size();

		for (int i = 0; i < size; i++) {
			Person obj = employees[i];
			cout << "  " << (i + 1) << "   |   " << obj.firstName << "   |   "
					<< obj.lastName << "   |   " << obj.address << endl;
		}
	}
	catch (NotFoundException& nfe) {
		cout << nfe.message() + " not found." << endl;
	}
	catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << '\n';
    }
}

CPP::Filter CPP::Connector::createFilter() {
	CPP::Filter filter;

	cout << "What column to be filtered (1-3): " << endl;
	cout << "1. First Name" << endl;
	cout << "2. Last Name" << endl;
	cout << "3. Address" << endl;
	cout << "Please enter your choice (1-3) : ";
	int selectedColumn;
	cin >> selectedColumn;

	switch (selectedColumn) {
	case 1: {
		filter.field = "firstName";
	}
		break;
	case 2: {
		filter.field = "lastName";
	}
		break;
	case 3: {
		filter.field = "address";
	}
	}

	cout << "Operator : " << endl;
	cout << "1. Equal" << endl;
	cout << "2. Not Equal" << endl;
	cout << "3. Greater" << endl;
	cout << "4. Greater Than Equals" << endl;
	cout << "5. Less Than" << endl;
	cout << "6. Less Than Equal" << endl;
	cout << "7. In" << endl;
	cout << "8. Not In" << endl;
	cout << "Please enter the operator (1-8) : ";
	int selectedOpr;
	cin >> selectedOpr;

	switch (selectedOpr) {
	case 1: {
		filter.op = EQUALS;
	}
		break;
	case 2: {
		filter.op = NOT_EQUALS;
	}
		break;
	case 3: {
		filter.op = GREATER_THAN;
	}
		break;
	case 4: {
		filter.op = GREATER_THAN_EQUALS;
	}
		break;
	case 5: {
		filter.op = LESS_THAN;
	}
		break;
	case 6: {
		filter.op = LESS_THAN_EQUALS;
	}
		break;
	case 7: {
		filter.op = IN;
	}
		break;
	case 8: {
		filter.op = NOT_IN;
	}
	}

	cout << "Filter value : " << endl;
	cin.ignore();
	getline(cin, filter.value);

	return filter;
}

void checkIsExist(string employeeName)
{
	MongoDB::Connection mongo;
	MongoDB::QueryRequest request("MitraisTestDB.Person");
	MongoDB::ResponseMessage response;

	mongo.connect("localhost", 27017);
	mongo.sendRequest(request, response);

	if ( response.documents().size() > 0 )
	{
		int size = response.documents().size();
		for (int i = 0 ; i < size ; i++)
		{
			Poco::MongoDB::Document::Ptr doc = response.documents()[i];

			try
			{
				string empName = doc->get<string>("firstName");

				if (empName == employeeName)
				{
					cout << employeeName << " is exist on our database."<<endl;
				}
			}
			catch(Poco::Exception& ex)
			{
				cout << ex.message();
			}
		}
	}
	else
	{
		cout << "There are no employee data " << employeeName << " on our database."<<endl;
	}
}
