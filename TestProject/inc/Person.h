#ifndef MONGODAOLIB__PERSON_H_
#define MONGODAOLIB__PERSON_H_

#include <ctime>

namespace Mitrais {
namespace util {

struct Person{
	std::string 	firstName;
	std::string 	lastName;
	std::string 	address;
	time_t 			createdDate;
	time_t 			lastUpdated;
};

}} //namespace Mitrais::util



#endif /* MONGODAOLIB__PERSON_H_ */

/**
 * ---------------------------------------------------------------------------
 *                         MITRAIS – CONTINUOUS COMMITMENT
 *         Jl Bypass Ngurah Rai, gg. Mina Utama No. 1, Suwung 80223 Bali
 *                          Phone: +62 / (0)807 / 1222-222
 *            OBSERVE COPYRIGHT AS PER ISO 16016 / COPYRIGHT RESERVED
 ******************************************************************************/
