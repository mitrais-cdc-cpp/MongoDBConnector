#include "../inc/MongoDBConnector.h"


MongoDBConnector::MongoDBConnector(const string& host_, const int port_, const string& dbname_)
: _host(host_)
, _port(port_)
, _dbname(dbname_)
, _connected(false)
{
	if (!_connected)
	{
		try
		{
			_mongoDBConn.connect(host_, port_);
			_connected = true;
		}
		catch (Poco::Net::ConnectionRefusedException& e)
		{
			//TODO: logger!
			std::cout << "Couldn't connect to " << e.message() << ". " << std::endl;
		}
	}
}


MongoDBConnector::~MongoDBConnector()
{
	if (_connected)
	{
		_mongoDBConn.disconnect();
		_connected = false;
	}
}

void MongoDBConnector::setDatabaseName(const string& dbname_)
{
	_dbname = dbname_;
}


string MongoDBConnector::getDatabaseName() const
{
	return _dbname;
}


bool MongoDBConnector::connect(const string& host_, const int port_, const string& dbname_)
{
	_host = host_;
	_port = port_;
	_dbname = dbname_;
	return connect();
}


bool MongoDBConnector::connect()
{
	//TODO: check if connected
	bool result = false;

	if (!_connected)
	{
		try
		{
			_mongoDBConn.connect(_host, _port);
			_connected = true;
			result = true;
		}
		catch (Poco::Net::ConnectionRefusedException& e)
		{
			//TODO: logger!
			std::cout << "Couldn't connect to " << e.message() << ". " << std::endl;
		}
	}
	return result;
}


template<typename T>
void MongoDBConnector::Update(const string& dbName_,
		const string& column_, const T& old_, const T& new_)
{
	if(_connected)
	{
		try
		{
			MongoDB::Database db(dbName_);
			SharedPtr<MongoDB::UpdateRequest> updateRequest = Update(db, column_, old_, new_);

			_mongoDBConn.sendRequest(*updateRequest);
		}
		catch(...)
		{

		}
	}
}

template<typename T>
void MongoDBConnector::UpdateAll(const string& dbName_,
		const vector<T>& columns_, const vector<T>& old_, const vector<T>& new_)
{
	if(columns_.size() == old_.size() && columns_.size() == new_.size())
	{
		if(_connected)
		{
			try
			{
				MongoDB::Database db(dbName_);

				for(unsigned int i = 0; i != columns_.size(); ++i)
				{
					SharedPtr<MongoDB::UpdateRequest> updateRequest = Update(db, columns_[i], old_[i], new_[i]);
					_mongoDBConn.sendRequest(*updateRequest);
				}
			}
			catch(...)
			{

			}
		}

	}
	else
	{
		//TODO:
	}
}




SharedPtr<MongoDB::InsertRequest> MongoDBConnector::InsertEmployee(MongoDB::Database &db, Person &person)
{
	DateTime now;
	MongoDB::Document::Ptr personPtr = new MongoDB::Document();

	personPtr->add("firstName", person.firstName);
	personPtr->add("lastName", person.lastName);
	personPtr->add("address", person.address);
	personPtr->add("createdDate", now.timestamp());
	personPtr->add("lastUpdated", NULL);

	SharedPtr<MongoDB::InsertRequest> insertRequest = db.createInsertRequest("Person");
	insertRequest->documents().push_back(personPtr);

	return insertRequest;
}



SharedPtr<MongoDB::DeleteRequest> MongoDBConnector::DeleteEmployee(MongoDB::Database &db,
		vector<Filter> &filters)
{
	SharedPtr<MongoDB::DeleteRequest> deleteRequest = db.createDeleteRequest("Person");

	if (!filters.empty())
	{
		MongoDB::Document& selector = deleteRequest->selector();

		for (vector<Filter>::iterator it = filters.begin(); it != filters.end(); ++it)
		{
			string field = it->field;
			string value = it->value;
			Operator op = it->op;

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
vector<T> MongoDBConnector::GetAll(MongoDB::ResponseMessage &response, vector<T> collection)
{
	int size = response.documents().size();
	for(int i = 0; i < size; i++)
	{
		T obj;
		MongoDB::Document::Ptr doc = response.documents()[i];

		obj.firstName = doc->get<string>("firstName");
		obj.lastName = doc->get<string>("lastName");
		obj.address = doc->get<string>("address");

		collection.push_back(obj);
	}

	return collection;
}



bool checkPerson(MongoDB::ResponseMessage &response, string employeeName)
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
