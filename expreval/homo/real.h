#ifndef _INC_EKU_EXPREVAL_HOMO_REAL
#define _INC_EKU_EXPREVAL_HOMO_REAL

namespace eku
{
	template<class typ>
	inline typ add(typ a,typ b){return a+b;}
	template<class typ>
	inline typ sub(typ a,typ b){return a-b;}
	template<class typ>
	inline typ mul(typ a,typ b){return a*b;}
	template<class typ>
	inline typ dvd(typ a,typ b){return a/b;}
	template<class typ>
	inline bool dvd_ckeck(typ a,typ b){return b!=0;}
	template<class typ>
	inline bool pow_ckeck(typ a,typ b){return (a!=0 || b!=0);}
	template<class typ>
	inline typ mod(typ a,typ b){return a%b;}
	template<>
	inline double mod<double>(double a,double b){return fmod(a,b);}
	template<class typ>
	inline typ minus(typ a){return -a;}
	template<class typ>
	inline typ plus(typ a){return a;}
	template<class typ>
	inline typ band(typ a,typ b){return a&b;}
	template<class typ>
	inline typ bor(typ a,typ b){return a|b;}
	template<class typ>
	inline typ bxor(typ a,typ b){return a^b;}
	template<>
	inline double band<double>(double a,double b)
	{return double(nearint<vlong>(a) & nearint<vlong>(b));}
	template<>
	inline double bor<double>(double a,double b)
	{return double(nearint<vlong>(a) | nearint<vlong>(b));}
	template<>
	inline double bxor<double>(double a,double b)
	{return double(nearint<vlong>(a) ^ nearint<vlong>(b));}
}

namespace eku_ref
{
	template<class typ>
	inline typ add(typ& a,typ& b){return a+b;}
	template<class typ>
	inline typ sub(typ& a,typ& b){return a-b;}
	template<class typ>
	inline typ mul(typ& a,typ& b){return a*b;}
	template<class typ>
	inline typ dvd(typ& a,typ& b){return a/b;}
	template<class typ>
	inline bool dvd_ckeck(typ& a,typ& b){return b!=0;}
	template<class typ>
	inline bool pow_ckeck(typ& a,typ& b){return (a!=0 || b!=0);}
	template<class typ>
	inline typ mod(typ& a,typ& b){return a%b;}
	template<class typ>
	inline typ minus(typ& a){return -a;}
	template<class typ>
	inline typ plus(typ& a){return a;}
	template<class typ>
	inline typ band(typ& a,typ& b){return a&b;}
	template<class typ>
	inline typ bor(typ& a,typ& b){return a|b;}
	template<class typ>
	inline typ bxor(typ& a,typ& b){return a^b;}
}

namespace eku_cref
{
	template<class typ>
	inline typ add(const typ& a,const typ& b){return a+b;}
	template<class typ>
	inline typ sub(const typ& a,const typ& b){return a-b;}
	template<class typ>
	inline typ mul(const typ& a,const typ& b){return a*b;}
	template<class typ>
	inline typ dvd(const typ& a,const typ& b){return a/b;}
	template<class typ>
	inline bool dvd_ckeck(const typ& a,const typ& b){return b!=0;}
	template<class typ>
	inline bool pow_ckeck(const typ& a,const typ& b){return (a!=0 || b!=0);}
	template<class typ>
	inline typ mod(const typ& a,const typ& b){return a%b;}
	template<class typ>
	inline typ minus(const typ& a){return -a;}
	template<class typ>
	inline typ plus(const typ& a){return a;}
	template<class typ>
	inline typ band(const typ& a,const typ& b){return a&b;}
	template<class typ>
	inline typ bor(const typ& a,const typ& b){return a|b;}
	template<class typ>
	inline typ bxor(const typ& a,const typ& b){return a^b;}
}

#endif	//_INC_EKU_EXPREVAL_HOMO_REAL