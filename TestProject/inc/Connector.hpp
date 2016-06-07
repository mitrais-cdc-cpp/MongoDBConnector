/*
 * Connector.hpp
 *
 *  Created on: Jun 7, 2016
 *      Author: developer
 */

#ifndef CONNECTOR_HPP_
#define CONNECTOR_HPP_

#include "Poco/MongoDB/Connection.h"
#include "Poco/MongoDB/Database.h"
#include "Poco/MongoDB/InsertRequest.h"
#include "Poco/MongoDB/UpdateRequest.h"
#include "Poco/MongoDB/DeleteRequest.h"
#include "Poco/MongoDB/QueryRequest.h"
#include "Poco/MongoDB/MongoDB.h"
#include "Poco/Net/NetException.h"
#include "Poco/SharedPtr.h"

using namespace Poco;
using namespace Poco::MongoDB;
using namespace Poco::Net;
using namespace std;

struct Person{
	string firstName;
	string lastName;
	string address;
	DateTime createdDate;
	DateTime lastUpdated;
};

SharedPtr<InsertRequest> InsertEmployee(Database &db, Person &person);

SharedPtr<UpdateRequest> UpdateEmployee(Database &db,
		string whereColumn, string whereValue, string newValue);

SharedPtr<DeleteRequest> DeleteEmployee(Database &db,
		string whereColumn, string whereValue);

void showAll(ResponseMessage &response);

#endif /* CONNECTOR_HPP_ */
