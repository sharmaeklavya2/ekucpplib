#ifndef _INC_EKU_CLASS_STRUINT
#define _INC_EKU_CLASS_STRUINT
//Header which stores a number in the form of a
//char array. Good to deal with digits.
//Example. 1468 is stored as "8641"

//incomplete

#include<string>
#include<eku\miscfunc.h>

namespace struint
{
	inline bool is_valid(char ch)
	{return ((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||(ch>='0' && ch<='9'));}
	
	inline bool is_valid(const std::string& str)
	{
		int i,n=str.size();
		for(i=0;i<n;i++)if(!is_valid(str[i]))return false;
		return true;
	}

	template<class typ>
	inline void uitostr(typ n,std::string& str,short base=10)
	{
		do{str.push_back(digit_to_char<typ>(n%base));n/=base;}
		while(n!=0);
	}
	
	inline void reverse(std::string& str)
	{int i,j=str.size()-1;char k;for(i=0;i<j;i++,j--){k=str[i];str[i]=str[j];str[j]=k;}}
	
	template<class typ>
	std::string add(const std::string& a,const std::string& b,short base=10)
	{
		int i,ha=a.size(),hb=b.size();
		typ temp,carry=0;
		std::string c;
		for(i=0;i<ha && i<hb;i++)
		{
			temp=char_to_digit<typ>(a[i])+char_to_digit<typ>(b[i])+carry;
			carry=temp/base;
			c.push_back(digit_to_char<typ>(temp%base));
		}
		for(;i<ha;i++)
		{
			temp=char_to_digit<typ>(a[i])+carry;
			carry=temp/base;
			c.push_back(digit_to_char<typ>(temp%base));
		}
		for(;i<hb;i++)
		{
			temp=char_to_digit<typ>(b[i])+carry;
			carry=temp/base;
			c.push_back(digit_to_char<typ>(temp%base));
		}
		if(carry>0)c.push_back(digit_to_char<typ>(carry));
		return c;
	}

#ifdef _IOSTREAM_
	inline void put_to(std::ostream& os,std::string str)
	{reverse(str);os<<str;}
	inline void get_from(std::istream& is,std::string& str)
	{is>>str;if(!is_valid(str)){str.clear();return;}reverse(str);}
#endif	//_IOSTREAM_

}
#endif	//_INC_EKU_CLASS_STRUINT