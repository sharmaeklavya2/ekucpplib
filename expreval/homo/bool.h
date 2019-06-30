#ifndef _INC_EKU_EXPREVAL_HOMO_BOOL
#define _INC_EKU_EXPREVAL_HOMO_BOOL

namespace eku_bool
{
	inline bool and(bool a,bool b){return a&&b;}
	inline bool or(bool a,bool b){return a||b;}
	inline bool xor(bool a,bool b){return a^b;}
	inline bool not(bool a){return !a;}
}
#endif	//_INC_EKU_EXPREVAL_HOMO_BOOL