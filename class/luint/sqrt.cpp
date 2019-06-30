#include<eku\math\sqrt_uint.h>
#include<eku\class\luint.h>

namespace eku
{
	template<>
	std::pair<luint,luint> sqrt_uint<luint,luint>(const luint& n)
	//returns pair of squareroot and remainder
	//Eg. sqrt_int(10) returns std::pair(3,1) beacuse 3*3+1 is 10
	{
		std::pair<luint,luint> pr(0,0);
		if(n.size()==0)return pr;
		if(n.size()==1)
		{
			std::pair<luint::styp,luint::styp> pr2;
			pr2=sqrt_uint<luint::styp>(n[0]);
			pr.first=pr2.first;pr.second=pr2.second;
			return pr;
		}
		else if(n.size()==2)
		{
			std::pair<luint::btyp,luint::btyp> pr2;
			pr2=sqrt_uint<luint::btyp>(luint::btyp(bytes<sizeof(luint::btyp)>(n[1],n[0])));
			pr.first=pr2.first;pr.second=pr2.second;
			return pr;
		}
		unsigned tot_steps=(sizeof(unsigned)<<2u)*n.size();
		unsigned step,index_quot,index_rem,index_divident;
		luint divisor(0u),rem(0u),quot(0),divident;
		for(step=1;step<=tot_steps;++step)
		{
			index_divident=(tot_steps-step)<<1;
			index_quot=index_divident/luint::sbits;
			index_rem=index_divident%luint::sbits;
			divident=(n[index_quot]>>index_rem)&3u;
			divident+=rem<<2u;
			quot<<=1u;
			divisor+=divisor&1u;
			divisor<<=1u;divisor|=1u;
			if(divisor<=divident)
			{quot|=1u;rem=divident-divisor;}
			else
			{rem=divident;--divisor;}
		}
		std::swap(pr.first,quot);
		std::swap(pr.second,rem);
		return pr;
	}
}
