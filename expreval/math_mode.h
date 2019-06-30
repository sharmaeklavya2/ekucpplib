#ifndef _INC_EKU_EXPREVAL_MATH_MODE
#define _INC_EKU_EXPREVAL_MATH_MODE

template<class dtyp>
class math_mode
{public:
	static bool func_loaded;
	static bool glob_var_loaded;
	static void setall(bool b){};
};

#include<eku\expreval\math_mode\double.h>
#include<eku\expreval\math_mode\int.h>
#ifdef _COMPLEX_
#include<eku\expreval\math_mode\complexdouble.h>
#endif

template<class dtyp>
bool math_mode<dtyp>::func_loaded=false;
template<class dtyp>
bool math_mode<dtyp>::glob_var_loaded=false;

#endif	//_INC_EKU_EXPREVAL_MATH_MODE