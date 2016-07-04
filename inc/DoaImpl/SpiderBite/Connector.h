/*
 * Connector.h
 *
 *  Created on: Jul 1, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef INC_CONNECTOR_H_
#define INC_CONNECTOR_H_

#include <ctime>

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

namespace Mitrais
{
	namespace util
	{
		// struct of Website
		struct Website{
			string 	content;
			string 	protocolType;
			time_t 	createdDate;
			time_t 	lastUpdated;
		};

		// enum of Operator
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

		// struct of Filter
		struct Filter
		{
			string field;
			string value;
			Opr op;
		};

		/**
		 * Class Connector is a DAO Layer using MongoDB
		 */
		class Connector
		{
		public:
			Connector() {};

			// Global static pointer used to ensure a single instance of the class.
			static Connector* Instance();

			/**
			 * Insert Website to MongoDB
			 *
			 * @param website a website data to insert
			 */
			void Insert(Website &website);

			/**
			 * Update MongoDB
			 *
			 * @param db a db name
			 * @param whereColumn a column
			 * @param whereValue a condition
			 * @param newValue a new value
			 */
			void Update(MongoDB::Database &db,
					string whereColumn, string whereValue, string newValue);

			/**
			 * Delete record on MongoDB
			 *
			 * @param filters a filter
			 */
			void Delete(vector<Filter> &filters);

			/**
			 * Show all records from MongoDB
			 */
			void showAll();

			/**
			 * Get all record from MongoDB
			 *
			 * @param response a response
			 * @return template a template
			 */
			template<typename T>
			vector<T> GetAll(MongoDB::ResponseMessage &response);

			/**
			 * Check the record is Database
			 *
			 * @param content a content to search
			 */
			bool checkIsExist(string content);

			/**
			 * Create filter used for delete method
			 *
			 * @return Filter
			 */
			Filter createFilter();

		private:
			Connector(Connector const&) {};
			Connector& operator=(Connector const&) {};
			static Connector* m_pInstance;
			const string _host = "localhost";
			const int _port = 27017;
			const string _dbName = "SpiderBite";
			const string _collectionName = "Website";
		};
	}
}


#endif /* INC_CONNECTOR_H_ */
