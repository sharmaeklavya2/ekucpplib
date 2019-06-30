#ifndef _INC_EKU_MATH_UIPOW
#define _INC_EKU_MATH_UIPOW
//Integer Power

namespace eku
{
	template<class rtyp,class btyp,class etyp>
	inline rtyp uipow(btyp base,etyp expn)
	//returns base raised to the power expn where expn is unsigned
	{
		rtyp res(1);etyp i(0);
		for(;i<expn;i++)res*=base;
		return res;
	}

	template<typename rtyp,typename btyp,typename etyp>
	rtyp bin_uipow(btyp base,etyp exp)
	/*binary version of uipow
	This function is faster than uipow but binary shift
	operator should be defined for exp for this function to work*/ 
	{
		rtyp final((exp&1)?base:1),bin_power(base);
		exp>>=1;
		while(exp!=0)
		{
			bin_power*=bin_power;
			if(exp&1)final*=bin_power;
			exp>>=1;
		}
		return final;
	}
}

#endif	//_INC_EKU_MATH_UIPOW