#ifndef _INC_EKU_EXPREVAL_MATH_MODE_COMPLEXDOUBLE

template<>
class math_mode<std::complex<dbl> >
{public:
	static bool trig;
	static bool itrig;
	static bool htrig;
	static bool ihtrig;
	static bool func_loaded;
	static bool glob_var_loaded;
	static void setall(bool b)
	{trig=b;itrig=b;htrig=b;ihtrig=b;}
};

bool math_mode<std::complex<dbl> >::trig=true;
bool math_mode<std::complex<dbl> >::itrig=true;
bool math_mode<std::complex<dbl> >::htrig=false;
bool math_mode<std::complex<dbl> >::ihtrig=false;
bool math_mode<std::complex<dbl> >::func_loaded=false;
bool math_mode<std::complex<dbl> >::glob_var_loaded=false;

#endif	//_INC_EKU_EXPREVAL_MATH_MODE_COMPLEXDOUBLE
