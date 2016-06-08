#ifndef MONGODAOLIB_TESTSUITEMONGO_H_
#define MONGODAOLIB_TESTSUITEMONGO_H_

#include "MongoDBConnector.h"

using namespace std;
using namespace Mitrais::util;

int main()
{
	int mode;

	MongoDBConnector mongo;

	try
	{
		mongo.connect("localhost", 27017, "MitraisTestDB");

		mainMenu:
		cout << "----------- Simple CRUD -----------" << endl;
		cout << "| 1. Insert                       |" << endl;
		cout << "| 2. Update                       |" << endl;
		cout << "| 3. Delete                       |" << endl;
		cout << "| 4. Show All                     |" << endl;
		cout << "| 5. Check Employee               |" << endl;
		cout << "| 0. Exit                         |" << endl;
		cout << "-----------------------------------" << endl;
		cout << "Select Mode: ";
		cin >> mode;

		switch(mode)
		{
			case 1:
			{
			}
			break;
			case 2:
			{
			}
			break;
			case 3:
			{
			}
			break;
			case 4:
			{
			}
			break;
			case 5:
			{
			}
			break;
			case 0:
			{
				exit(0);
			}
			break;
		}
	}
	catch (Poco::Net::ConnectionRefusedException& e)
	{
		cout << "Couldn't connect to " << e.message() << ". " << endl;
	}

	return 0;
}

#endif /* MONGODAOLIB_TESTSUITEMONGO_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
