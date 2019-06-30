#ifndef _INC_EKU_MISCFUNC
#define _INC_EKU_MISCFUNC
//Miscellaneous functions

#pragma warning(disable:4996)
//This warning shows warnings on using deprecated functions
//like strcpy,strcmp,strcat

#include<algorithm>
#include<eku\numlex\hexconv.h>
typedef unsigned int uint;

inline char* ordinal(int a)//returns "st","nd","rd" or "th" according to input
{return (a>0)?((a%10==1 && a%100!=11)?"st":((a%10==2 && a%100!=12)?"nd":((a%10==3 && a%100!=13)?"rd":"th"))):"th";}

template<class typ>
typ nth_perm(typ n)
{
	typ fact[11],ans=0;
	int i,j;
	bool taken[10];
	fact[0] = 1;

	for (i=1;i<=10;++i)
	{
		fact[i]=fact[i-1]*i;
		taken[i-1]=false;
	}

	for(i=10;i>0;--i)
	{
		j=0;
		while(taken[j])++j;
		while(n>fact[i-1])
		{
			n-=fact[i-1];
			do{++j;}
			while(taken[j]);
		}
		taken[j]=true;
		ans*=10;ans+=j;
	}
	return ans;
}

template<class typ>
void nth_perm(typ n,const char* in,char* out)
{
	int i,j,p=0,m=strlen(in);
	typ *fact=new typ[m+1];
	bool *taken=new bool[m];
	fact[0]=1;

	for (i=1;i<=m;++i)
	{
		fact[i]=fact[i-1]*i;
		taken[i-1]=false;
	}

	for(i=m;i>0;--i)
	{
		j=0;
		while(taken[j])++j;
		while(n>fact[i-1])
		{
			n-=fact[i-1];
			do{++j;}
			while(taken[j]);
		}
		taken[j]=true;
		out[p++]=in[j];
	}
	out[p]='\0';
	delete[] fact;
	delete[] taken;
}

#ifdef _IOSTREAM_

template<class elem,class traits>
void disp_all_perm(const char* in1,const char* in2,std::basic_ostream<elem,traits>& os,int& count)
//error
{
	int i,n=strlen(in2),m=strlen(in1);
	if(n==1)
	{
		if(count!=-1)os<<count++<<'\t';
		os<<in1<<in2[0]<<std::endl;
		return;
	}
	else if(n==2)
	{
		if(count!=-1)os<<count++<<'\t';
		os<<in1<<in2[0]<<in2[1]<<std::endl;
		if(in2[0]!=in2[1])
		{
			if(count!=-1)os<<count++<<'\t';
			os<<in1<<in2[1]<<in2[0]<<std::endl;
		}
		return;
	}
	char t;
	char* a=new char[n+1];
	char* b=new char[m+2];
	strcpy(a,in2);
	strcpy(b,in1);b[m+1]='\0';
	b[m]=a[0];
	disp_all_perm(b,a+1,os,count);
	for(i=1;i<n;i++)
	{
		if(a[i]==a[i-1])continue;
		t=a[0];a[0]=a[i];a[i]=t;
		b[m]=a[0];
		disp_all_perm(b,a+1,os,count);
		t=a[0];a[0]=a[i];a[i]=t;
	}
	delete[] a;
	delete[] b;
}

void disp_all_perm(const char* in,std::ostream& os,bool count=true)
{
	int i=1,n=strlen(in);
	bool b=false;
	char* a=new char[n+1];
	strcpy(a,in);
	std::sort(a,a+n);
	do
	{
		if(count)os<<i++<<'\t';
		os<<a<<std::endl;
		b=std::next_permutation(a,a+n);
	}
	while(b);
	delete[] a;
}
#endif	//_IOSTREAM_

#ifndef NO_DEPR_WARN
#pragma warning(default:4996)
#endif	//NO_DEPR_WARN

#endif //_INC_EKU_MISCFUNC