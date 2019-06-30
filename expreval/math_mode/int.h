#ifndef _INC_EKU_EXPREVAL_MATH_MODE_INT

template<>
class math_mode<itg>
{public:
	static bool piece_def;
	static bool factor;
	static bool bitwise;
	static bool func_loaded;
	static bool glob_var_loaded;
	static void setall(bool b)
	{piece_def=b;factor=b;bitwise=b;}
};

bool math_mode<itg>::piece_def=false;
bool math_mode<itg>::factor=true;
bool math_mode<itg>::bitwise=false;
bool math_mode<itg>::func_loaded=false;
bool math_mode<itg>::glob_var_loaded=false;

#endif	//_INC_EKU_EXPREVAL_MATH_MODE_INT
