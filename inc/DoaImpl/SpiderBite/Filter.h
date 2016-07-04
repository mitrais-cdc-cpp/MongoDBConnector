/*
 * Filter.h
 *
 *  Created on: Jul 4, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include "Operator.h"

using namespace std;

namespace Mitrais
{
	namespace util
	{
		// struct of Filter
		struct Filter{
			string field;
			string value;
			Opr op;
		};
	}
}


#endif /* INC_FILTER_H_ */
