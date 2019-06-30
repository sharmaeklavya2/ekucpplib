#ifndef _INC_EKU_CLASS_LUINT_SQRT
#define _INC_EKU_CLASS_LUINT_SQRT

namespace eku
{
	std::pair<luint,luint> sqrt_luint(const luint& n);
	//returns pair of squareroot and remainder
	//Eg. sqrt_int(10) returns std::pair(3,1) beacuse 3*3+1 is 10
}

#endif	//_INC_EKU_CLASS_LUINT_SQRT