#ifndef _INC_EKU_NUMLEX_HEXCONV
#define _INC_EKU_NUMLEX_HEXCONV

#include<eku/numlex/digit_to_char.h>
#include<string>

namespace eku
{

	template<class typ>
	//converts number to hexadecimal
	void num_to_hex(typ n,char* a)
	{
		unsigned i,j;
		const unsigned size=8*sizeof(n),b=15;
		for(i=0,j=(size>>2)-1;i<size;i+=4,j--)
		{a[j]=digit_to_char((n>>i)&b);}
		a[size>>2]='\0';
	}

	template<class typ>
	//small bug
	void num_to_oct(typ n,char* a)
	{
		int i,j;
		const unsigned size=8*sizeof(n),b=7;
		for(i=0,j=size/3-1;j>=0;i+=3,j--)
		{a[j]='0'+char((n>>i)&b);}
		a[size/3]='\0';
	}

	template<class typ>
	typ hex_to_num(const char* a)
	{
		int i,j;
		typ n=0;
		for(i=0;a[i]!='\0';i++);i--;
		for(j=0;i>=0;i--,j+=4)
		{n|=char_to_digit<typ>(a[i])<<j;}
		return n;
	}

	template<class typ>
	void num_to_bin(typ n,char* a)
	//eg. converts 14 to "1110"
	{
		int i,j;
		typ t;
		for(i=0;n!=0;++i,n>>=1)
			a[i]=n&1?'1':'0';
		a[i--]='\0';
		for(j=0;i>j;--i,++j)
		{t=a[i];a[i]=a[j];a[j]=t;}
	}

	template<class typ>
	void num_to_bin_comp(typ n,char* a)
	//eg. converts 14 to "00001110" if typ is char
	{
		unsigned b=1,i,j;
		const unsigned size=8*sizeof(n);
		for(i=0,j=size-1;i<size;i++,j--,b<<=1)
		{a[j]=((n&b)==0)?'0':'1';}
		a[i]='\0';
	}

	template<class typ>
	typ bin_to_num(const char* str)
	{
		typ t(0);
		unsigned i;
		for(i=0;str[i]!='\0';++i)
		{t<<=1;if(str[i]!='0')t|=1;}
		return t;
	}

	template<class typ>
	typ bin_to_num(const std::string& str)
	{
		typ t(0);
		unsigned i;
		for(i=0;i<str.size();++i)
		{t<<=1;if(str[i]!='0')t|=1;}
		return t;
	}

}	//end of namespace eku

#endif	//_INC_EKU_HEXCONV
