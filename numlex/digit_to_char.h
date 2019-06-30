#ifndef _INC_EKU_NUMLEX_DIGIT_TO_CHAR
#define _INC_EKU_NUMLEX_DIGIT_TO_CHAR

//convert 3 to '3' and vice-versa
//useful in hexadecimal: 12 to 'C'

namespace eku
{

	template<class typ>
	inline char digit_to_char(typ n)
	{
		if(n<=9)return '0'+char(n);
		else if(n<=36)return 'A'+char(n-10);
		else return '\0';
	}

	template<class typ>
	inline typ char_to_digit(char a)
	{
		if(a>='0' && a<='9')return typ(a-'0');
		else if(a>='A' && a<='Z')return typ(a-'A'+10);
		else if(a>='a' && a<='z')return typ(a-'a'+10);
		else return 40;
	}

}	//end of namespace eku;

#endif	//_INC_EKU_NUMLEX_DIGIT_TO_CHAR