#ifndef _INC_EKU_IO__IO
#define _INC_EKU_IO__IO 1
//<conio.h> extension

#ifndef _NO_CONIO
#include<conio.h>
#endif	//_NO_CONIO

//============================================================================================

void _passin(char* a,int n=30,char ch=char(249))
//inputs a password in a
//n - size of a
//ch- hiding character
{
	char t;
	int i=0;
	while(i<n)
	{
		t=_getch();
		if(t==char(13))break;
		else if(t==char(8)){_cputs("\b \b");i--;}
		else {_putch(ch);a[i++]=t;}
	}
	if(i<n)a[i]='\0';
}

char _get_restrict_che(const char* a)
//Inputs only those characters which are part of the string
{
	char ch;unsigned i;
	while(true)
	{
		ch=_getch();
		for(i=0;a[i]!='\0';i++)if(ch==a[i])
		{_putch(ch);return ch;}
	}
}

bool _cont(const char* a="Run again? (y/n) ")
//Asks the user a 'yes/no' question, accepts a suitable response
//and returns true if the user says 'yes'
{
#ifndef NO_CONT_PROMPT
	char yn;
	_cputs(a);
	while(true)
	{
		yn=_getch();
		if(yn=='y' || yn=='Y')
		{_putch(yn);_cputs("\n\n");return true;}
		else if(yn=='n' || yn=='N')
		{_putch(yn);_cputs("\n\n");return false;}
	}
#else	//NO_CONT_PROMPT
	_putch('\n');
	return true;
#endif	//NO_CONT_PROMPT
}

#endif //_INC_EKU_IO
