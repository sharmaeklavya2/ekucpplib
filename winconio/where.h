#ifndef _INC_EKU_WINCONIO_WHERE
#define _INC_EKU_WINCONIO_WHERE
//Get coordinates of current cursor position
#include<utility>
#include<windows.h>

namespace eku
{
	inline int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.dwCursorPosition.X;
	}

	inline int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.dwCursorPosition.Y;
	}

	inline std::pair<SHORT,SHORT> wherexy()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return std::pair<SHORT,SHORT>(csbi.dwCursorPosition.X,csbi.dwCursorPosition.Y);
	}
}

#endif	//_INC_EKU_WINCONIO_WHERE