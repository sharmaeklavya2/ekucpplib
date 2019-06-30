#ifndef _INC_EKU_EXPREVAL_MATH_MODE_DOUBLE

template<>
class math_mode<dbl>
{public:
	static bool trig;
	static bool dtrig;
	static bool itrig;
	static bool ditrig;
	static bool htrig;
	static bool ihtrig;
	static bool piece_def;
	static bool factor;
	static bool bitwise;
	static bool func_loaded;
	static bool glob_var_loaded;
	static void setall(bool b)
	{trig=b;dtrig=b;itrig=b;ditrig=b;htrig=b;ihtrig=b;piece_def=b;factor=b;bitwise=b;}
};

bool math_mode<dbl>::trig=true;
bool math_mode<dbl>::dtrig=false;
bool math_mode<dbl>::itrig=true;
bool math_mode<dbl>::ditrig=false;
bool math_mode<dbl>::htrig=false;
bool math_mode<dbl>::ihtrig=false;
bool math_mode<dbl>::piece_def=false;
bool math_mode<dbl>::factor=true;
bool math_mode<dbl>::bitwise=false;
bool math_mode<dbl>::func_loaded=false;
bool math_mode<dbl>::glob_var_loaded=false;

#endif	//_INC_EKU_EXPREVAL_MATH_MODE_DOUBLE
