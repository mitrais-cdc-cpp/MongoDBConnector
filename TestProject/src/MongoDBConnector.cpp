#include "../inc/MongoDBConnector.h"


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
		vector<Filter> &filters)
{
	SharedPtr<DeleteRequest> deleteRequest = db.createDeleteRequest("Person");

	if (!filters.empty())
	{
		Document& selector = deleteRequest->selector();

		for (vector<Filter>::iterator it = filters.begin(); it != filters.end(); ++it)
		{
			string field = it->field;
			string value = it->value;
			Opr op = it->op;

			selector.addNewDocument(field);

			switch (op)
			{
				case EQUALS:
				{
					selector.add("$eq", value);
				}
				break;
				case NOT_EQUALS:
				{
					selector.add("$ne", value);
				}
				break;
				case GREATER_THAN:
				{
					selector.add("$gt", value);
				}
				break;
				case GREATER_THAN_EQUALS:
				{
					selector.add("$gte", value);
				}
				break;
				case LESS_THAN:
				{
					selector.add("$lt", value);
				}
				break;
				case LESS_THAN_EQUALS:
				{
					selector.add("$lte", value);
				}
				break;
				case IN:
				{
					selector.add("$in", value);
				}
				break;
				case NOT_IN:
				{
					selector.add("$nin", value);
				}
				break;
			}
		}
	}

	return deleteRequest;
}


template <typename T>
vector<T> GetAll(ResponseMessage &response, vector<T> collection)
{
	int size = response.documents().size();
	for(int i = 0; i < size; i++)
	{
		T obj;
		Document::Ptr doc = response.documents()[i];

		obj.firstName = doc->get<string>("firstName");
		obj.lastName = doc->get<string>("lastName");
		obj.address = doc->get<string>("address");

		collection.push_back(obj);
	}

	return collection;
}

void showAll(ResponseMessage &response)
{
	try{
		cout << "------------------- Employee Data -------------------"<<endl;
		cout << "No.   |   First Name   |   LastName   |   Address   |" << endl;
		cout << "-----------------------------------------------------" << endl;

		vector<Person> employees = GetAll(response, employees);
		int size = employees.size();

		for(int i=0; i < size; i++)
		{
			Person obj = employees[i];
			cout << "  " << (i + 1) << "   |   "<< obj.firstName << "   |   "
					<< obj.lastName << "   |   "<< obj.address << endl ;
		}
	}
	catch(NotFoundException& nfe){
		cout << nfe.message() + " not found."<< endl;
	}
}

Filter createFilter()
{
	Filter filter;

	cout << "What column to be filtered (1-3): " << endl;
	cout << "1. First Name" << endl;
	cout << "2. Last Name" << endl;
	cout << "3. Address" << endl;
	cout << "Please enter your choice (1-3) : ";
	int selectedColumn;
	cin >> selectedColumn;

	switch (selectedColumn)
	{
		case 1:
		{
			filter.field = "firstName";
		}
		break;
		case 2:
		{
			filter.field = "lastName";
		}
		break;
		case 3:
		{
			filter.field = "address";
		}
	}

//	do
//	{
//		cout << "Invalid Column : " << selectedColumn << endl;
//		cout << "Pleas enter valid column (1-3) : " ;
//		cin >> selectedColumn;
//	}while (selectedColumn < 0 || selectedColumn > 3);

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

	switch (selectedOpr)
	{
		case 1:
		{
			filter.op = EQUALS;
		}
		break;
		case 2:
		{
			filter.op = NOT_EQUALS;
		}
		break;
		case 3:
		{
			filter.op = GREATER_THAN;
		}
		break;
		case 4:
		{
			filter.op = GREATER_THAN_EQUALS;
		}
		break;
		case 5:
		{
			filter.op = LESS_THAN;
		}
		break;
		case 6:
		{
			filter.op = LESS_THAN_EQUALS;
		}
		break;
		case 7:
		{
			filter.op = IN;
		}
		break;
		case 8:
		{
			filter.op = NOT_IN;
		}
	}

//	do
//	{
//		cout << "Invalid Operator : " << selectedOpr << endl;
//		cout << "Pleas enter valid operator (1-8) : " ;
//		cin >> selectedOpr;
//	}while (selectedOpr < 0 || selectedOpr > 8);

	cout << "Filter value : " << endl;
	cin.ignore();
	getline(cin, filter.value);

	return filter;
}

bool checkPerson(ResponseMessage &response, string employeeName)
{
	bool result;
	if ( response.documents().size() > 0 )
		{
			for (int i = 0 ; i < response.documents().size() ; i++)
			{
				Poco::MongoDB::Document::Ptr doc = response.documents()[i];

				try
				{
					string empName = doc->get<string>("firstName");

					if (empName == employeeName)
					{
						cout << employeeName << " is exist on our database."<<endl;
						return true;
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
			result = false;
		}

	return result;
}
