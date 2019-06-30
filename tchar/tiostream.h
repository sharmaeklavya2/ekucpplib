#ifndef _INC_EKU_TCHAR_TIOSTREAM
#define _INC_EKU_TCHAR_TIOSTREAM

#include<tchar.h>
#include<iostream>
#include<fstream>
#include<sstream>

namespace eku
{
#ifdef UNICODE
	typedef std::wostream	tostream;
	typedef std::wstreambuf	tstreambuf;
	typedef std::wfilebuf	tfilebuf;
	typedef std::wistream	tistream;
	typedef std::wiostream	tiostream;
	typedef std::wfstream	tfstream;
	typedef std::wifstream	tifstream;
	typedef std::wios	tios;
	typedef std::wistringstream	tistringstream;
	typedef std::wofstream	tofstream;
	typedef std::wostringstream tostringstream;
	typedef std::wstringstream tstringstream;
	std::wostream& tcout=std::wcout;
	std::wostream& tcerr=std::wcerr;
	std::wostream& tclog=std::wclog;
	std::wistream& tcin=std::wcin;
#else	//UNICODE
	typedef std::ostream	tostream;
	typedef std::wstreambuf	tstreambuf;
	typedef std::wfilebuf	tfilebuf;
	typedef std::istream	tistream;
	typedef std::iostream	tiostream;
	typedef std::fstream	tfstream;
	typedef std::ifstream	tifstream;
	typedef std::ios	tios;
	typedef std::istringstream	tistringstream;
	typedef std::ofstream	tofstream;
	typedef std::ostringstream tostringstream;
	typedef std::stringstream tstringstream;
	std::ostream& tcout=std::cout;
	std::ostream& tcerr=std::cerr;
	std::ostream& tclog=std::clog;
	std::istream& tcin=std::cin;
#endif	//UNICODE
	
}

#endif	//_INC_EKU_TCHR_TIOSTREAM