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
using namespace std;

namespace CDC
{
	namespace CPP
	{
		struct Person
		{
			string firstName;
			string lastName;
			string address;
			DateTime createdDate;
			DateTime lastUpdated;
		};

		enum Opr
		{
			EQUALS,
			NOT_EQUALS,
			GREATER_THAN,
			GREATER_THAN_EQUALS,
			LESS_THAN,
			LESS_THAN_EQUALS,
			IN,
			NOT_IN
		};

		struct Filter
		{
			string field;
			string value;
			Opr op;
		};

		class Connector
		{
		public:
			Connector() {};
			static Connector* Instance();

			void Insert(Person &person);

			void Update(MongoDB::Database &db,
					string whereColumn, string whereValue, string newValue);

			void Delete(vector<Filter> &filters);

			void showAll();

			template<typename T>
			vector<T> GetAll(MongoDB::ResponseMessage &response, vector<T> collection);

			void checkIsExist(string employeeName);

			Filter createFilter();

		private:
			Connector(Connector const&) {};
			Connector& operator=(Connector const&) {};
			static Connector* m_pInstance;
		};
	}
}

#endif /* CONNECTOR_HPP_ */
