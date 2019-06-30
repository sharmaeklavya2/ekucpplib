#ifndef _INC_EKU_MATH_COMBI_COMBI
#define _INC_EKU_MATH_COMBI_COMBI

/*
The Combination function
This function gives the no. of ways of selecting r objects out of n distinct objects
It is denoted by nCr. 'Selection' means that order of selected objects isn't considered.
*/
namespace eku
{
	template<class rtyp,class typ,class ityp>
	inline rtyp combi(typ n,ityp r)
	{
		if(r<0)return 0;
		typ i;
		ityp j;
		rtyp p(1);
		for(i=n,j=1;j<=r;++j,--i){p*=i;p/=j;}
		return p;
	}
}

#endif	//_INC_EKU_MATH_COMBI_COMBI