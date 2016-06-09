#ifndef MONGODAOLIB_MONGODBCONNECTOR_H_
#define MONGODAOLIB_MONGODBCONNECTOR_H_

#include <string>

#include "PocoMongoIncludes.h"
#include "Person.h"
#include "Operator.h"
#include "Filter.h"



using namespace std;
using namespace Poco;
using namespace Mitrais::util;

namespace Mitrais {
namespace util {

class MongoDBConnector
{
public:

	MongoDBConnector(const string& host_, const int port_, const string& dbname_);
	~MongoDBConnector();

	bool connect();
	bool connect(const string& host_, const int port_, const string& dbname_);
	void setDatabaseName(const string& dbname_);
	string getDatabaseName() const;

	bool checkPerson(MongoDB::ResponseMessage &response, string employeeName);

private:

	std::string _host;
	std::string _dbname;
	int _port;
	bool _connected;
	MongoDB::Connection _mongoDBConn;

	bool connect(MongoDB::Connection& mongoDBConn_);

	template<typename T>
	SharedPtr<MongoDB::UpdateRequest> Update(MongoDB::Database& db_,
				string tablename_, string column_, T old_,T new_);

	template <typename T>
	vector<T> GetAll(MongoDB::ResponseMessage &response, vector<T> collection);

	//TODO: need more abstraction
	SharedPtr<MongoDB::InsertRequest> InsertEmployee(MongoDB::Database &db, Person &person);

	//TODO: need more abstraction
	SharedPtr<MongoDB::DeleteRequest> DeleteEmployee(MongoDB::Database &db, vector<Filter> &filters);

	template<typename T>
	void Update(const string& dbName_, const string& column_, const T& old_, const T& new_);

	template<typename T>
	void UpdateAll(const string& dbName_, const vector<T>& columns_, const vector<T>& old_, const vector<T>& new_);

};

}} //namespace Mitrais::util

#endif /* MONGODAOLIB_MONGODBCONNECTOR_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
