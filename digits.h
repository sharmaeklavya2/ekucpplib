#ifndef _INC_EKU_DIGITS
#define _INC_EKU_DIGITS
//Deals with digits of an integer
//number of digits, sum of digits, etc.

namespace eku
{
	template<class rtyp,class ityp>
	inline rtyp no_of_digits(const ityp& a,short base=10)//loop-1
	{
		ityp x(a);
		rtyp nod(0);
		while(x!=0){nod++;x/=base;}
		return nod;
	}

	template<class rtyp,class ityp>
	inline rtyp sum_of_digits(const ityp& a,short base=10)//loop-1
	{
		ityp x=a;
		rtyp s=0;
		while(x!=0){s+=x%base;x/=base;}
		return s;
	}

	template<class ityp>
	inline ityp reverse(ityp n,short base=10)
	{
		ityp out(0);
		while(n!=0){out*=base;out+=n%base;n/=base;}
		return out;
	}

	template<class typ>
	bool ispandigital(const typ& n,short base=10)
	{
		char a[30];
		int i,j;
		typ x=n;
		for(i=0;x!=0;i++)
		{a[i]='0'+char(x%base);x/=base;}
		a[i]='\0';
		x=strlen(a);
		for(i=1;i<x;i++)for(j=0;j<i;j++)if(a[i]==a[j])return false;
		return true;
	}
}	//end of namespace eku

#endif	//_INC_EKU_DIGITS