#ifndef MONGODAOLIB_MONGODBCONNECTOR_H_
#define MONGODAOLIB_MONGODBCONNECTOR_H_

#include "PocoMongoIncludes.h"

using namespace Poco;
using namespace std;

namespace Mitrais {
namespace util {

class MongoDBConnector
{
public:

	MongoDBConnector(const string& host_, const int port_);
	~MongoDBConnector();

	bool connect();
	bool connect(const string& host_, const int port_);

	Filter createFilter();

	bool checkPerson(MongoDB::ResponseMessage &response, string employeeName);


private:

	std::string 			_host;
	int						_port;
	bool 					_connected;
	MongoDB::Connection 	_mongoDBConn;

	bool connect(MongoDB::Connection& mongoDBConn_);

	template<typename T>
	SharedPtr<MongoDB::UpdateRequest> Update(MongoDB::Database& db_,
				string tablename_,
				string column_,
				T old_,
				T new_);

	SharedPtr<MongoDB::InsertRequest> InsertEmployee(MongoDB::Database &db, Person &person);

	SharedPtr<MongoDB::DeleteRequest> DeleteEmployee(MongoDB::Database &db, vector<Filter> &filters);



	template <typename T>
	vector<T> GetAll(MongoDB::ResponseMessage &response, vector<T> collection);
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
