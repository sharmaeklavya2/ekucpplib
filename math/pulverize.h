#ifndef _INC_EKU_MATH_PULVERIZE
#define _INC_EKU_MATH_PULVERIZE

#include<utility>

typedef int typ;

std::pair<typ,typ> lin_int_eqn(typ a,typ b,typ c,char m_type)
/*
Solves the equation am+bn=c for m and n and returns std::pair(m,n)
a should be >= b. a and b should not be 0.
typ should be a signed type.
returns std::pair(0,0) if no solution exists
value of m depends on m_type:
if m_type is 'p', m will take the smallest non-negative value
if m_type is 'n', m will take the smallest non-positive value
if m_type is 's', m will take the smallest absolute value
if m_type is 't', m will take the value between -b and b which takes the least time to compute.
*/
{
	typ divident=a,divisor=b,rem,quot;
	std::pair<typ,typ> divident_p(1,0),divisor_p(0,1),rem_p(0,0);
	if(c%divident==0)
	{divisor=divident;divisor_p=divident_p;}
	else while(c%divisor!=0)
	{
		//Do the arithmetic
		quot=divident/divisor;
		rem=divident%divisor;	//divident-quot*divisor
		if(rem==0)return std::pair<typ,typ>(0,0);
		rem_p.first=divident_p.first-quot*divisor_p.first;
		rem_p.second=divident_p.second-quot*divisor_p.second;
		//Shift
		divident=divisor;
		divisor=rem;
		divident_p=divisor_p;
		divisor_p=rem_p;
	}
	if(c!=divisor)
	{
		quot=c/divisor;
		divisor_p.first*=quot;
		divisor_p.second*=quot;
	}
	quot=divisor_p.first/b;
	divisor_p.first-=quot*b;
	divisor_p.second+=quot*a;
	if(m_type!='t')
	{
		if(m_type=='p')
		{
			if(divisor_p.first<0)
			{divisor_p.first+=b;divisor_p.second-=a;}
		}
		else if(m_type=='n')
		{
			if(divisor_p.first>0)
			{divisor_p.first-=b;divisor_p.second+=a;}
		}
		else if(m_type=='s')
		{
			if(divisor_p.first>b/2)
			{divisor_p.first-=b;divisor_p.second+=a;}
			else if(divisor_p.first<-(b/2))
			{divisor_p.first+=b;divisor_p.second-=a;}
		}
	}
	return divisor_p;
}

typ inverse(typ a,typ m)
//computes inverse of a mod b
{return lin_int_eqn(m,a%m,1,'n').second;}

typ chinese_rem(typ a1,typ m1,typ a2,typ m2)
/*if x=a1(mod m1) and x=a2(mod m2) implies x=r(mod m1*m2),
then this function returns r*/
{
	//m1 should be greater
	if(m1<m2){std::swap(m1,m2);std::swap(a1,a2);}
	return a1+m1*lin_int_eqn(m1,m2,a2-a1,'p').first;
}

#endif	/*_INC_EKU_MATH_PULVERIZE*/