#ifndef _INC_EKU_IO_GETLINE
#define _INC_EKU_IO_GETLINE

#include<iostream>
#include<string>

namespace eku
{
	template<class elem,class traits>
	inline std::basic_istream<elem,traits>& atleast_getline(std::basic_istream<elem,traits>& is,
		std::basic_string<elem,traits>& str,char delim='\n')
	//assures that something is entered. Function keeps asking for input till input is given.
	{
		str.clear();
		while(str.empty() && is)std::getline(is,str,delim);
		return is;
	}

	template<class elem,class traits>
	inline std::basic_istream<elem,traits>& safe_getline(std::basic_istream<elem,traits>& is,
		std::basic_string<elem,traits>& str,char delim='\n')
	//makes getline safe to use after operator>>
	{if(is.peek()=='\n')is.ignore();is.getline(is,str,delim);return is;}

	template<class elem,class traits>
	inline std::basic_istream<elem,traits>& ssafe_getline(std::basic_istream<elem,traits>& is,
		std::basic_string<elem,traits>& str,char delim='\n')
	//makes getline super safe to use after operator>>
	{while(is.peek()=='\n')is.ignore();is.getline(is,str,delim);return is;}

	template<class elem,class traits>
	inline std::basic_istream<elem,traits>& ssafe_atleast_getline(std::basic_istream<elem,traits>& is,
		std::basic_string<elem,traits>& str,char delim='\n')
	{
		str.clear();
		while(is.peek()=='\n')is.ignore();
		while(str.empty() && is)std::getline(is,str,delim);
		return is;
	}

}

#endif	//_INC_EKU_IO_GETLINE