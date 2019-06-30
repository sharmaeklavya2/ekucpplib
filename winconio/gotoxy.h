#ifndef _INC_EKU_WINCONIO_GOTOXY
#define _INC_EKU_WINCONIO_GOTOXY
//Set cursor position at a specific point
namespace eku
{
	inline void gotoxy(int x,int y)
	{
		COORD coord={x,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	}
}
#endif	//_INC_EKU_WINCONIO_GOTOXY