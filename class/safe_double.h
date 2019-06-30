#ifndef _INC_EKU_CLASS_SAFE_DOUBLE
#define _INC_EKU_CLASS_SAFE_DOUBLE

//Makes comparison in double safer by using an epsilon

#include<cmath>

namespace eku
{
	typedef double dtyp;

	class safe_double
	{
	protected:
		dtyp value,eps;
	public:
		safe_double(dtyp v=0,dtyp epsilon=1e-15)
		{value=v;eps=epsilon;}
		safe_double(const safe_double& d)
		{value=d.value;eps=d.eps;}
		bool iszero()const
		{
			int exp1;
			frexp(value,&exp1);
			return value<ldexp(eps,exp1-1);
		}
		int compare(const dtyp& d)const
		{
			int exp1,exp2;
			frexp(value,&exp1);
			frexp(value,&exp2);
			if(exp1<exp2)return -1;
			else if(exp1>exp2)return 1;
			else if(abs(value-d)<ldexp(eps,exp1-1))return 0;
			else if(value<d)return -1;
			else return 1;
		}
		int compare(const safe_double& d)const
		{
			int exp1,exp2;
			double maxeps=std::max(eps,d.eps);
			frexp(value,&exp1);
			frexp(value,&exp2);
			if(exp1<exp2)return -1;
			else if(exp1>exp2)return 1;
			else if(abs(value-d.value)<ldexp(maxeps,exp1-1))return 0;
			else if(value<d.value)return -1;
			else return 1;
		}
		bool operator<(const dtyp& d)const
		{return compare(d)==-1;}
		bool operator>(const dtyp& d)const
		{return compare(d)==1;}
		bool operator<(const safe_double& d)const
		{return compare(d)==-1;}
		bool operator>(const safe_double& d)const
		{return compare(d)==1;}
		bool operator==(const dtyp& d)const
		{
			int exp1,exp2;
			frexp(value,&exp1);
			frexp(value,&exp2);
			if(exp1<exp2 || exp1>exp2)return false;
			else if(abs(value-d)<ldexp(eps,exp1-1))return true;
			else return false;
		}
		bool operator==(const safe_double& d)const
		{
			int exp1,exp2;
			dtyp maxeps=std::max(eps,d.eps);
			frexp(value,&exp1);
			frexp(value,&exp2);
			if(exp1<exp2 || exp1>exp2)return false;
			else if(abs(value-d.value)<ldexp(maxeps,exp1-1))return true;
			else return false;
		}
		bool operator<=(const dtyp& d)const
		{return compare(d)!=1;}
		bool operator>=(const dtyp& d)const
		{return compare(d)!=-1;}
		bool operator<=(const safe_double& d)const
		{return compare(d)!=1;}
		bool operator>=(const safe_double& d)const
		{return compare(d)!=-1;}
		operator dtyp()const{return value;}
		operator dtyp&(){return value;}
		
	};
}	//end of namespace eku

#endif	//_INC_EKU_CLASS_SAFE_DOUBLE