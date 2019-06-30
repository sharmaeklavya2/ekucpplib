#ifndef _INC_EKU_STR_CASE_INS_CMP
#define _INC_EKU_STR_CASE_INS_CMP
//Case insensitive string compare
#include<cctype>
#include<string>

namespace eku
{
	int stricmp(const std::string& a,const std::string& b)
	{
		unsigned i,ha=a.length(),hb=b.length();
		for(i=0;i<ha && i<hb;i++)
		{
			if(toupper(a[i])<toupper(b[i]))return -1;
			else if(toupper(a[i])>toupper(b[i]))return 1;
		}
		if(ha<hb)return -1;
		else if(ha>hb)return 1;
		else return 0;
	}

	bool isless(const std::string& a,const std::string& b)
	{
		unsigned i,ha=a.length(),hb=b.length(),hmin;
		hmin=ha<hb?ha:hb;
		for(i=0;i<hmin;i++)
		{
			if(toupper(a[i])<toupper(b[i]))return true;
			else if(toupper(a[i])>toupper(b[i]))return false;
		}
		return ha<hb;
	}
}

#endif	//_INC_EKU_STR_CASE_INS_CMP