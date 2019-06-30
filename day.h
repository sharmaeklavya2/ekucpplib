#ifndef _INC_EKU_DAY
#define _INC_EKU_DAY 1
//needs repair
//Header file to find day for a given date
//use boost::date_time instead
#include<eku\io\inpout.h>

int day(int d,int m,int y);	//returns day (as int) for a given date
char* day(int n);	//converts day as int to day as string
char* dayinwords(int d,int m,int y);	//returns day (as char*) for a given date

//--------------------------------------------------------------------------------------------

int day(int d,int m,int y)
{
	int r,i;
	if(d<1){output("Day should be positive\n");return -1;}
	else if(d>31){output("Date can't be more than 31\n");return -2;}
	if(m<1){output("Month should be positive\n");return -3;}
	else if(m>12){output("Month can't be more than 12\n");return -4;}
	else if(m==2 && d>=30){output("February has atmost 29 days\n");return -5;}
	else if((m==4 || m==6 || m==9 || m==11) && d>=31){output("Month no. ");output(m);output(" has only 30 days\n");return -6;}
	if(y%4!=0 && m==2 && d>=29){output("A non-leap year has only 28 days in February\n");return -7;}
	r=5*((y-1)/4)+(y-1)%4+d+6;
	for(i=1;i<m;i++)
	{
		if(i==1 || i==3 || i==5 || i==7 || i==8 || i==10){r+=3;}
		else if(i==2){if(y%4==0){r++;}}
		else{r+=2;}
	}
	i=r%7;
	return i;
}

char* day(int n)
{	switch(n)
	{
	case 1:return "Monday";
	case 2:return "Tuesday";
	case 3:return "Wednesday";
	case 4:return "Thursday";
	case 5:return "Friday";
	case 6:return "Saturday";
	case 0:return "Sunday";
	case 7:return "Sunday";
	default:return "NOday";
	}
}

char* dayinwords(int d,int m,int y)
{
	int k=day(d,m,y);
	if(k<0)
	{
		char a[12];
		a[0]='E';a[1]='r';a[2]='r';a[3]='o';a[4]='r';a[5]=' ';
		a[6]='n';a[7]='o';a[8]='.';a[9]=' ';a[10]=char(48-k);a[11]='\0';
		a[10]=char(48-k);
		return a;
	}
	else return day(k);
}

#endif	//_INC_EKU_DAY