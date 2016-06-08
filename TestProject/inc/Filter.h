#ifndef MONGODAOLIB__FILTER_H_
#define MONGODAOLIB__FILTER_H_

#include "Operator.h"

namespace Mitrais {
namespace util {

struct Filter{
	std::string field;
	std::string value;
	Operator op;
};

}} //namespace Mitrais::util

#endif /* MONGODAOLIB__FILTER_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
