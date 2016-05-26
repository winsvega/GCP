#ifndef GCP_MathH
#define GCP_MathH

#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <cstdio>
#include <ctype.h>
#include "GCP_Vector.h"
#include "GCP_Delegate.h"
#include "GCP_IO.h"

#include "math\GCP_Math_Points.h"	//math structures and objects
using namespace std;

namespace gcp
{

const double GCP_RADTODEG = (double)180 / 3.14;
const double GCP_DEGTORAD = (double)3.14 / 180;
const int GCP_INT32MAX = 2147483647;

class GCP_Math
{
public:	
	#include "math\GCP_Math_Basics.h"		//standart math and normalization
	#include "math\GCP_Math_Collision.h"	//collisions and intersections
	#include "math\GCP_Math_Genetic.h"		//genetic algo
	#include "math\GCP_Math_Physics.h"		//refraction and reflection
	#include "math\GCP_Math_String.h"		//work with strings
};

inline std::string CP1251_TO_WCHAR(const char *str)
{
	return GCP_Math::RUSCP1251_TO_WCHAR(str);
}

struct GCP_UID
{
	unsigned int key_a; //64
	unsigned int key_b; //128
	unsigned int key_c; //192
	unsigned int key_d; //256
	GCP_UID(unsigned int a, unsigned int b, unsigned int c, unsigned int d) :
		key_a(a), key_b(b), key_c(c), key_d(d) {}

	GCP_UID()
	{
		key_a = GCP_Math::uniqueValue64();
		key_b = GCP_Math::uniqueValue64();
		key_c = GCP_Math::uniqueValue64();
		key_d = GCP_Math::uniqueValue64();
	}

	std::string toStr() const
	{
		int key_a1 = key_a - GCP_INT32MAX;
		int key_b1 = key_b - GCP_INT32MAX;
		int key_c1 = key_c - GCP_INT32MAX;
		int key_d1 = key_d - GCP_INT32MAX;
		return GCP_Math::intToString(key_a1) + GCP_Math::intToString(key_b1) + GCP_Math::intToString(key_c1) + GCP_Math::intToString(key_d1);
	}

	void readFromFile(GCP_IO *io)
	{
		io->readInt(&key_a);
		io->readInt(&key_b);
		io->readInt(&key_c);
		io->readInt(&key_d);
	}

	void writeToFile(GCP_IO *io) const
	{
		io->writeInt(key_a);
		io->writeInt(key_b);
		io->writeInt(key_c);
		io->writeInt(key_d);
	}

	inline friend bool operator == (const GCP_UID& lhs, const GCP_UID& rhs)
	{
		return (lhs.key_a == rhs.key_a && lhs.key_b == rhs.key_b && lhs.key_c == rhs.key_c && lhs.key_d == rhs.key_d);
	}
	bool operator == (const GCP_UID& rhs)
	{
		return (key_a == rhs.key_a && key_b == rhs.key_b && key_c == rhs.key_c && key_d == rhs.key_d);
	}
};

}
#endif
