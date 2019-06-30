#ifndef _INC_EKU_TCHR_TSTRING
#define _INC_EKU_TCHR_TSTRING

#include<tchar.h>
#include<string>

namespace eku
{
#ifdef UNICODE
	typedef std::wstring tstring;
#else	//UNICODE
	typedef std::string tstring;
#endif	//UNICODE
}

#endif	//_INC_EKU_TCHR_TSTRING