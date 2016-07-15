/*
 * TestConnector.h
 *
 *  Created on: Jul 1, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef SPIDERBITE_TEST_TESTCONNECTOR_H_
#define SPIDERBITE_TEST_TESTCONNECTOR_H_


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../inc/DoaImpl/SpiderBite/Connector.h"

class TestConnector: public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(TestConnector);
	CPPUNIT_TEST(testInsertWebsite);
	CPPUNIT_TEST(testShowAllWebsite);
	CPPUNIT_TEST(testUpdateWebsite);
	CPPUNIT_TEST(testDeleteWebsite);
	CPPUNIT_TEST_SUITE_END();


private:
	const string _dbName = "SpiderBite";
	void testInsertWebsite();
	void testShowAllWebsite();
	void testUpdateWebsite();
	void testDeleteWebsite();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestConnector );

#endif /* SPIDERBITE_TEST_TESTCONNECTOR_H_ */
