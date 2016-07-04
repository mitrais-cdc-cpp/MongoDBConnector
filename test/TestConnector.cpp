/*
 * TestConnector.cpp
 *
 *  Created on: Jul 1, 2016
 *      Author: Ari Suarkadipa
 */

#include "TestConnector.h"
#include "../inc/DoaImpl/SpiderBite/Connector.h"


void TestConnector::testInsertWebsite()
{
	Mitrais::util::Connector connector;
	Mitrais::util::Website website;
	string content = "<html><head>Hello</head><body>World</body></html>";

	website.content = content;
	website.protocolType = "http";
	connector.Insert(website);

	bool actual = true;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}

void TestConnector::testUpdateWebsite()
{
	MongoDB::Database db(_dbName);
	Mitrais::util::Connector connector;
	string whereColumn = "content";
	string whereValue = "<html><head>Hello</head><body>World</body></html>";
	string newValue = "<html><head>Hello</head><body>New World</body></html>";

	connector.Update(db, whereColumn, whereValue, newValue);
	bool actual = true;
	bool result = connector.checkIsExist(newValue);
	CPPUNIT_ASSERT(result == actual);
}

void TestConnector::testShowAllWebsite()
{
	Mitrais::util::Connector connector;
	string content = "<html><head>Hello</head><body>World</body></html>";

	connector.showAll();

	bool actual = true;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}

void TestConnector::testDeleteWebsite()
{
	Mitrais::util::Connector connector;
	string content = "http";

	Mitrais::util::Filter filter = connector.createFilter(2,1, content);

	vector<Mitrais::util::Filter> filters;
	filters.push_back(filter);

	connector.Delete(filters);

	bool actual = false;
	bool result = connector.checkIsExist(content);
	CPPUNIT_ASSERT(result == actual);
}
