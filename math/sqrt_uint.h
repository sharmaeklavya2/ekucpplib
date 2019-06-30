#ifndef _INC_EKU_MATH_SQRT_UINT
#define _INC_EKU_MATH_SQRT_UINT

#include<utility>

namespace eku
{
	template<class typq,class typ>
	std::pair<typq,typ> sqrt_uint(const typ& number)
	//returns pair of squareroot and remainder
	//Eg. sqrt_int(10) returns std::pair(3,1) beacuse 3*3+1 is 10
	{
		const unsigned tot_steps=sizeof(typ)<<2u;
		unsigned step,bits_to_shift;
		typ n(number),divisor(0u),rem(0u),divident;
		typq quot(0u);
		for(step=1;step<=tot_steps;++step)
		{
			bits_to_shift=(tot_steps-step)<<1;
			divident=((n>>bits_to_shift)&3u)+(rem<<2u);
			quot<<=1u;
			divisor+=divisor&1u;
			divisor<<=1u;++divisor;
			if(divisor<=divident)
			{quot+=1u;rem=divident-divisor;}
			else
			{rem=divident;--divisor;}
		}
		return std::pair<typq,typ>(quot,rem);
	}
}	//end of namespace eku

#endif	//_INC_EKU_MATH_SQRT_UINT