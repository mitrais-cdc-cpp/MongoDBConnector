#ifndef MONGODAOLIB_CONNECTOR_HPP_
#define MONGODAOLIB_CONNECTOR_HPP_

#include "PocoMongoIncludes.h"

using namespace Poco;
using namespace std;

namespace Mitrais {
namespace util {

struct Person{
	string firstName;
	string lastName;
	string address;
	DateTime createdDate;
	DateTime lastUpdated;
};

enum Opr{
	EQUALS,
	NOT_EQUALS,
	GREATER_THAN,
	GREATER_THAN_EQUALS,
	LESS_THAN,
	LESS_THAN_EQUALS,
	IN,
	NOT_IN
};

struct Filter{
	string field;
	string value;
	Opr op;
};

SharedPtr<InsertRequest> InsertEmployee(Database &db, Person &person);

SharedPtr<UpdateRequest> UpdateEmployee(Database &db,
		string whereColumn, string whereValue, string newValue);

SharedPtr<DeleteRequest> DeleteEmployee(Database &db,
		vector<Filter> &filters);

template <typename T>
vector<T> GetAll(ResponseMessage &response, vector<T> collection);

void showAll(ResponseMessage &response);
bool checkPerson(ResponseMessage &response, string employeeName);

Filter createFilter();


}} //namespace Mitrais::util

#endif /* MONGODAOLIB_CONNECTOR_HPP_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
