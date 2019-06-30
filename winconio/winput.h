#ifndef _INC_EKU_WINCONIO_WINPUT
#define _INC_EKU_WINCONIO_WINPUT
//Windows put

#include<windows.h>

namespace eku
{
	inline void winputch(char a)
	{
		unsigned long j;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),&a,1,&j,NULL);
	}
	
	inline void wincputs(const char* a)
	{
		int i;
		unsigned long j;
		for(i=0;a[i]!='\0';i++);
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),a,i,&j,NULL);
	}
}

#endif	//_INC_EKU_WINCONIO_WINPUT