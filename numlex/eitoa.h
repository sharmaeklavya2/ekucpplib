#ifndef _INC_EKU_NUMLEX_EITOA
#define _INC_EKU_NUMLEX_EITOA

#include<eku/numlex/digit_to_char.h>

namespace eku
{

	template<typename typ>
	void eitoa(typ n,char* str,short base=10)
	{
		int i=0,j,m;
		char ch;
		if(n<0){str[i++]='-';n=-n;}
		for(;n>0;i++)
		{str[i]=digit_to_char(n%base);n/=base;}
		m=i;str[i]='\0';
		for(i=0,j=m-1;i<j;i++,j--)
		{ch=str[i];str[i]=str[j];str[j]=ch;}
	}

	template<typename typ>
	void euitoa(typ n,char* str,short base=10)
	{
		int i=0,j,m;
		char ch;
		for(;n>0;i++)
		{str[i]=digit_to_char(n%base);n/=base;}
		m=i;str[i]='\0';
		for(i=0,j=m-1;i<j;i++,j--)
		{ch=str[i];str[i]=str[j];str[j]=ch;}
	}

	inline bool string_fail(const char* str,unsigned base)
	//string is incorrect with respect to base
	//For eg. in base 2, 101011 is correct but 100201 is incorrect
	{
		unsigned i;
		for(i=0;str[i]!='\0';++i)
		{if(char_to_digit<unsigned>(str[i])>=base)return true;}
		return false;
	}

}	//end of namespace eku
#endif	//_INC_EKU_NUMLEX_EITOA
