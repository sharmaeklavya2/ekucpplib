#ifndef _INC_EKU_DOUBLE_TO_FRAC
#define _INC_EKU_DOUBLE_TO_FRAC

#include<cmath>
#include<utility>

namespace eku
{
	template<class ityp,class dtyp>
	std::pair<ityp,ityp> double_to_frac(dtyp frac,dtyp epsilon,ityp denom_limit)
	//Converts a double to a fraction. Keep def_prec at about 0.0001 and denom_limit at about 4000.
	{
		ityp den,inum,inumf,inumc;
		dtyp dnum,epsf,epsc,eps;
		for(den=1;den<=denom_limit;++den)
		{
			dnum=frac*den;
			inumf=ityp(std::floor(dnum));
			inumc=ityp(std::ceil(dnum));

			epsf=dtyp(inumf)-dnum;
			if(epsf<0)epsf=-epsf;
			epsc=dtyp(inumc)-dnum;
			if(epsc<0)epsc=-epsc;
			
			if(epsf<epsc){eps=epsf;inum=inumf;}
			else{eps=epsc;inum=inumc;}
			if(eps<=epsilon)return std::pair<ityp,ityp>(inum,den);
		}
		return std::pair<ityp,ityp>(0,0);
	}
}

#endif	//_INC_EKU_DOUBLE_TO_FRAC