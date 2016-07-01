#ifndef MONGODAOLIB_TESTSUITEMONGO_H_
#define MONGODAOLIB_TESTSUITEMONGO_H_


#include <iostream>
#include <string>

#include <MongoDaoLib/MongoDBConnector.h>

using namespace std;
using namespace Mitrais::util;


int main(int argc, char* argv[])
{
	enum StartParams
	{
		PARAM_FOUND,
		CONNECTION,
		HELP,
		PARAM_UNKNOWN,
		PARAM_NOTFOUND
	};

	StartParams eStartParam = PARAM_NOTFOUND;
	int iSelectedMode = 0;
	MongoDBConnector mongo;
	string conServer, conPort, conDB;

	cout << "count argc: " << argc << endl;

	if(argc > 1)
	{
		eStartParam = PARAM_FOUND;
		bool bFoundServer=false, bFoundPort=false, bFoundDB=false;

		for(int i=1; i>=argc; ++i)
		{
			cout << "param: " << argv[i] << " "  << argv[i+1] << endl;
			if(argv[i] == "-server")
			{
				string conServer = argv[i+1];
				bFoundServer = true;
			}
			else if(argv[i] == "-port")
			{
				string conPort = argv[i+1];
				bFoundPort = true;
			}
			else if(argv[i] == "-db")
			{
				string conDB = argv[i+1];
				bFoundDB =true;
			}
			else if(argv[i] == "-help")
			{
				eStartParam = HELP;
			}
		}

		if(bFoundDB && bFoundPort && bFoundServer)
			eStartParam = CONNECTION;
	}


	switch(eStartParam)
	{
	case CONNECTION:
	{
		try
		{
			int iPort = std::stoi(conPort, nullptr);

			mongo.setDatabaseName(conServer);
			mongo.setPort(iPort);
			mongo.setServerName(conDB);

			if(mongo.isInitialized())
				mongo.connect();
			else
			{
				cout << "Connection isnt initialized with " << conServer;
				cout << " with port " << conPort;
				cout << " to database " << conDB << endl;
			}
		}
		catch (Poco::Net::ConnectionRefusedException& e)
		{
			cout << "Error occurs, couldn't connect to host " << conServer;
			cout << " with port " << conPort;
			cout << " to database " << conDB << endl;
			cout << " Error message: " << e.message() << endl;
		}
		break;
	}
	case HELP:
	{
		cout << "usage:";
		cout << "[-server <server> -port <port> -db <database name>]";
		cout << endl;
		break;
	}
	case PARAM_NOTFOUND:
	{
		break;
	}
	case PARAM_FOUND:
	{
		break;
	}
	default:
	{
		cout << "parameter not recognized, type -help for help" << endl;;
		return -1;
	}
	}

//	cout << "----------- Simple CRUD -----------" << endl;
//	cout << "| 1. Insert                       |" << endl;
//	cout << "| 2. Update                       |" << endl;
//	cout << "| 3. Delete                       |" << endl;
//	cout << "| 4. Show All                     |" << endl;
//	cout << "| 5. Check Employee               |" << endl;
//	cout << "| 0. Exit                         |" << endl;
//	cout << "-----------------------------------" << endl;
//	cout << "Select Mode: ";
//	cin >> iSelectedMode;
//
//	switch(iSelectedMode)
//	{
//		case 1:
//		{
//		}
//		break;
//		case 2:
//		{
//		}
//		break;
//		case 3:
//		{
//		}
//		break;
//		case 4:
//		{
//		}
//		break;
//		case 5:
//		{
//		}
//		break;
//		case 0:
//		{
//			return 0;
//		}
//		break;
//	}


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
