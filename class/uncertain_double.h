#ifndef _INC_EKU_CLASS_UNCERTAIN_DOUBLE
#define _INC_EKU_CLASS_UNCERTAIN_DOUBLE

#include<cmath>
#include<ostream>

namespace eku
{
	class undouble
	{
	public:
		typedef double typ;
	private:
		typ err;
	public:
		typ val;
		undouble(typ value,typ error=0):val(value),err(error){}
		void set(typ value,typ error)
		{val=value;err=error;}
		typ abserr()const{return err;}
		typ relerr()const{return err/val;}
		operator double()const{return val;}
	};

	undouble operator+(const undouble& d1,const undouble& d2)
	{return undouble(d1.val+d2.val,d1.abserr()+d2.abserr());}

	undouble operator-(const undouble& d1,const undouble& d2)
	{return undouble(d1.val-d2.val,d1.abserr()+d2.abserr());}

	undouble operator*(const undouble& d1,const undouble& d2)
	{return undouble(d1.val*d2.val,abs(d2.val*d1.abserr())+abs(d1.val*d2.abserr()));}

	undouble operator/(const undouble& d1,const undouble& d2)
	{return undouble(d1.val*d2.val,(abs(d2.val*d1.abserr())+abs(d1.val*d2.abserr()))/d2.val/d2.val);}

	undouble pow(const undouble& d,undouble::typ n)
	{
		undouble::typ v=std::pow(d.val,n-1);
		return undouble(d.val*v,n*v*d.abserr());
	}

	std::ostream& operator<<(std::ostream& os,const undouble& d)
	{return os<<d.val<<char(241)<<d.abserr();}
}

#endif	//_INC_EKU_CLASS_UNCERTAIN_DOUBLE