#ifndef _INC_EKU_CLASS_LUINT
#define _INC_EKU_CLASS_LUINT

/*
Luint - Large Unsigned int
This data type uses a std::vector to store ints which 
concatenate bitwise to make a large unsigned int.
The smallest bits are stored in a[0], larger bits in a[1]
and so on. The size of the luint is extensible.
*/

#include<vector>
#include<limits>
#include<cstring>
#include<string>
#include<cmath>
#include<eku\bytes.h>
#include<eku\numlex\hexconv.h>
#include<eku\numlex\eitoa.h>

namespace eku
{

class luint
{public:

//data-members-and-typedefs-------------------------------------------------------

		typedef unsigned int styp;
		typedef int sstyp;
		typedef unsigned __int64 btyp;
		typedef __int64 sbtyp;
		const static unsigned ssize=sizeof(styp);
		const static unsigned bsize=sizeof(btyp);
		const static unsigned sbits=ssize*CHAR_BIT;
		const static unsigned bbits=bsize*CHAR_BIT;

		std::vector<styp> a;
		bool sign;	//+ve sign is true and -ve sign is false.
			//As luint is unsigned, -ve sign means error
			//-ve sign can be encountered while using operator- or operator--
		static bool use_float_display;
		static unsigned float_display_prec;

		unsigned size()const{return a.size();}

		void shrink_to_fit()
		/*This function removes elements of	'a' where largest bits are all zero.
		It is similar to converting 0000 0101 to 0101
		Most functions in this class will already take care
		that such extra zeros are not added.
		This function will rarely need to be used*/
		{while(a.size()>0 && a.back()==0)a.pop_back();}

		void swap(luint& l)
		{std::swap(sign,l.sign);a.swap(l.a);}

		styp operator[](unsigned n)const{return a[n];}
		styp operator!()const
		{return a.empty();}

//Constructors--------------------------------------------------------------------

		luint():sign(true){}

		template<class typ>
		luint(typ n):sign(n>=0)
		//n is assumed to be unsigned
		{if(n>0)a.push_back(styp(n));}

		template<>
		luint(styp n):sign(true)
		//n is assumed to be unsigned
		{if(n!=0)a.push_back(n);}

		template<>
		luint(btyp n);
		//n is assumed to be unsigned

		template<class typ>
		luint(typ n,unsigned capacity):sign(n>=0)
		//n is assumed to be unsigned
		{if(n>0)a.push_back(styp(n));a.reserve(capacity);}

		template<>
		luint(styp n,unsigned capacity):sign(true)
		//n is assumed to be unsigned
		{if(n!=0)a.push_back(n);a.reserve(capacity);}

		template<>
		luint(btyp n,unsigned capacity);
		//n is assumed to be unsigned

		luint(const luint& l):sign(l.sign){if(sign)a=l.a;}

//Conversion-to-double------------------------------------------------------------

		unsigned exponent()const;
		//gets integral part of logarithm of *this to the base 2

		template<class dtyp>
		//dtyp can be double, float, long double, etc.
		dtyp signif(int prec=4)const;
		
		template<class dtyp>
		//dtyp can be double, float, long double, etc.
		dtyp as_double(int prec=4)const
		{return ldexp(signif<dtyp>(prec),exponent());}

		operator double()const
		{return as_double<double>();}

		operator long double()const
		{return as_double<long double>();}

//Conversion-to-integers----------------------------------------------------------
		
		operator styp()const
		//truncates and returns lowest dword
		{
			if(a.size()==0)return 0;
			else return a[0];
		}

		operator sstyp()const
		//truncates and returns lowest dword
		{
			if(a.size()==0)return 0;
			else return sstyp(a[0]);
		}

		operator btyp()const
		//truncates and returns lowest qword
		{
			if(a.size()==0)return 0;
			else if(a.size()==1)return btyp(a[0]);
			else return bytes<bsize>(a[1],a[0]);
		}

		operator bool()const
		{return (sign && !a.empty());}

//Conversion-to-strings-----------------------------------------------------------

		void to_hex_string(char* str)const
		//stores the luint's hexadecimal representation in str
		{
			int i,ssize2=ssize<<1;
			for(i=a.size()-1;i>=0;i--,str+=ssize2)
			{num_to_hex(a[i],str);}
			*str='\0';
		}

		void to_hex_string(std::string& str)const;
		//stores the luint's hexadecimal representation in str

		void to_string(std::string& str,styp base)const;
		//stores the luint's representation in str

		void to_string_float(std::string& str,styp base,unsigned maxprec=0,unsigned max_digits=4)const;
		//stores the luint's floating point representation in str

		void from_hex_string(const char* str);
		//Assigns the luint a value from its hexadecimal representation in str
		//No spaces or commas are allowed in str

		void from_string(const char* str,styp base);

//Bitwise-Operators---------------------------------------------------------------

		template<class typ>
		//bitwise right shift operator
		//n can't be negative
		void operator>>=(const typ& n);
		
		template<class typ>
		//bitwise left shift operator
		//n can't be negative
		void operator<<=(const typ& n);

		template<class typ>
		luint operator>>(const typ& n)const
		{luint big(*this);big>>=n;return big;}

		template<class typ>
		luint operator<<(const typ& n)const
		{luint big(*this);big<<=n;return big;}

		void operator&=(styp n)
		{
			if(!a.empty())
			{a.resize(1);a[0]&=n;shrink_to_fit();}
		}

		void operator&=(btyp n)
		{
			bytes<bsize> b(n);
			if(a.size()==1)a[0]&=b.lo();
			else if(a.size()>=2)
			{a.resize(2);a[0]&=b.lo();a[0]&=b.hi();}
			shrink_to_fit();
		}

		void operator&=(const luint& l)
		{
			if(a.size()>l.a.size())
			{a.erase(a.begin()+a.size(),a.begin()+l.a.size());}
			int i;for(i=a.size()-1;i>=0;i--){a[i]&=l.a[i];}
			shrink_to_fit();
		}

		styp operator&(styp n)const
		{return (a.empty())?0:a[0]&n;}

		sstyp operator&(sstyp n)const
		{return (a.empty())?0:a[0]&n;}

		btyp operator&(btyp n)const
		{
			if(a.empty())return 0;
			else if(a.size()==1)return n&btyp(a[0]);
			else return n&(bytes<bsize>(a[1],a[0]));
		}

		luint operator&(const luint& l)const
		{
			unsigned i,new_size=std::min(a.size(),l.a.size());
			luint big;
			big.a.resize(new_size,0);
			for(i=0;i<new_size;++i)big.a[i]=a[i]&l.a[i];
			big.shrink_to_fit();
			return big;
		}

		void operator|=(const luint& l)
		{
			int i;
			if(l.a.size()>a.size()){a.resize(l.a.size(),0);}
			for(i=a.size();i>=0;i--){a[i]|=l.a[i];}
		}

		void operator|=(styp n)
		{
			if(a.empty())a.push_back(n);
			else a[0]|=n;
		}
		
		void operator|=(sstyp n)
		{operator|=(styp(n));}

		void operator|=(btyp n)
		{
			eku::bytes<bsize> mybytes(n);
			if(a.size()<=1)a.resize(2,0);
			a[0]|=mybytes.lo();
			a[1]|=mybytes.hi();
			shrink_to_fit();
		}

		template<class typ>
		luint operator|(const typ& n)const
		{luint big(*this);big|=n;return big;}

		template<>
		luint operator|<luint>(const luint& l)const
		{
			unsigned i,new_size=std::max(a.size(),l.a.size());
			luint big;
			big.a.resize(new_size,0);
			for(i=0;i<new_size;++i){big.a[i]=a[i]|l.a[i];}
			big.shrink_to_fit();
			return big;
		}

		void operator^=(const luint& l)
		{
			unsigned i;
			if(l.a.size()>a.size()){a.resize(l.a.size(),0);}
			for(i=0;i<a.size();++i){a[i]^=l.a[i];}
			shrink_to_fit();
		}

		void operator^=(styp n)
		{
			if(a.empty())a.push_back(n);
			else a[0]^=n;
		}

		void operator^=(sstyp n)
		{operator^=(styp(n));}

		luint operator^(const luint& l)const
		{
			unsigned i,new_size=std::max(a.size(),l.a.size());
			luint big;
			big.a.resize(new_size,0);
			for(i=0;i<new_size;++i){big.a[i]=a[i]^l.a[i];}
			big.shrink_to_fit();
			return big;
		}

//Assignment----------------------------------------------------------------------
		
		template<class typ>
		void operator=(typ n)
		{a.clear();sign=(n>=0);if(n!=0)a.push_back(styp(n));}
		template<>
		void operator=(btyp n);

		void operator=(const luint& l)
		{sign=l.sign;if(l.sign){a=l.a;}}

//Addition-Operators--------------------------------------------------------------

		void plusme_l(const luint& l);
		void plusme_s(styp n);
		void plusme_b(btyp n);
		void incme()
		{
			unsigned i;
			for(i=0;i<a.size() && a[i]==styp(~0);i++)a[i]=0;
			if(i==a.size())a.push_back(1);else ++a[i];
		}
		
		template<class typ>
		void operator+=(const typ& n)
		{if(n<0)minusme_s(styp(n));else plusme_s(styp(n));}
		template<>
		void operator+=(const styp& n)
		{plusme_s(n);}
		template<>
		void operator+=(const btyp& n)
		{plusme_b(n);}
		template<>
		void operator+=(const sbtyp& n)
		{if(n<0)minusme_b(btyp(n));else plusme_b(btyp(n));}
		template<>
		void operator+=(const luint& l)
		{plusme_l(l);}

		template<class typ>
		luint operator+(const typ& n)const
		{luint big(*this);big+=n;return big;}

		luint operator++()
		{incme();return *this;}
		luint operator++(int)
		{luint big(*this);incme();return big;}

//Subtraction---------------------------------------------------------------------
		
		void minusme_s(styp n);
		void minusme_b(btyp n);
		void minusme_l(const luint& l);
		void decme()
		{
			unsigned i;
			if(a.empty()){sign=false;return;}
			for(i=0;i<a.size() && a[i]==0;i++)a[i]=styp(~0);
			--a[i];
			if(a.back()==0)a.pop_back();
		}
		
		template<class typ>
		void operator-=(const typ& n)
		{if(n<0)plusme_s(styp(-n));else minusme_s(styp(n));}
		template<>
		void operator-=(const styp& n)
		{minusme_s(n);}
		template<>
		void operator-=(const btyp& n)
		{minusme_b(n);}
		template<>
		void operator-=(const sbtyp& n)
		{if(n<0)plusme_b(btyp(-n));else return minusme_b(btyp(n));}
		template<>
		void operator-=(const luint& l)
		{minusme_l(l);}

		template<class typ>
		luint operator-(const typ& n)const
		{
			luint big(*this);
			big-=n;
			return big;
		}

		luint operator-()const
		{luint big;big.sign=false;return big;}

		luint operator--()
		{decme();return *this;}
		luint operator--(int)
		{luint big(*this);decme();return big;}

//Multiplication------------------------------------------------------------------

		void operator*=(styp n);
		luint operator*(styp n)const
		{luint big(*this);big*=n;return big;}

		void multiply(const luint& big,luint& result)const;
		//multiplies *this with big and stores the result in result
		void operator*=(const luint& l)
		{luint big;multiply(l,big);operator=(big);}
		luint operator*(const luint& l)const
		{luint big;multiply(l,big);return big;}

//Division------------------------------------------------------------------------
		
		styp divide(styp n);
		//divides *this with n and returns the remainder
		void divide(const luint& divisor,luint& quotient,bool leaverem=true);
		//divides *this with divisor, leaves remainder in *this if leaverem is true

		void operator/=(styp n){divide(n);}
		luint operator/(styp n)const
		{luint big(*this);big.divide(n);return big;}
		luint operator/(sstyp n)const
		{
			luint big;
			if(n<0){big.sign=false;}
			else {big=*this;big.divide(n);}
			return big;
		}
		void operator/=(const luint& divisor)
		{luint quot;divide(divisor,quot,false);operator=(quot);}
		luint operator/(const luint& divisor)const
		{luint quot,big(*this);big.divide(divisor,quot,false);return quot;}

		styp operator%(styp n)const;
		styp operator%(sstyp n)const
		{
			if(n<0)n=-n;
			return operator%(static_cast<styp>(n));
		}
		void operator%=(styp n)
		{operator=(operator%(n));}
		void operator%=(sstyp n)
		{operator=(operator%(n));}

		void operator%=(const luint& divisor);
		luint operator%(const luint& divisor)const
		{luint big(*this);big%=divisor;return big;}

//Comparison----------------------------------------------------------------------

		bool issame_s(styp n)const
		{return(sign && ((a.size()==1 && a[0]==n) || (a.empty() && n==0)));}
		
		bool issame_b(btyp n)const
		{return(sign && ((a.size()==1 && btyp(a[0])==n)
			|| (a.size()==2 && a[0]==styp(n)
			&& a[1]==bytes<bsize>(n).hi()) || (a.empty() && n==0)));}

		template<class typ>
		bool operator==(const typ& n)const
		{return n>=0 && issame_s(styp(n));}

		template<>
		bool operator==(const luint& l)const
		{return sign==l.sign && a==l.a;}

		template<>
		bool operator==(const btyp& n)const
		{return issame_b(n);}

		template<>
		bool operator==(const sbtyp& n)const
		{return issame_b(n) && n>=0;}

		template<>
		bool operator==(const styp& n)const
		{return issame_s(n);}

		template<class typ>
		bool operator!=(const typ& n)const
		{return !operator==(n);}

		int compare(const luint& l)const;
		//-1 if a<b, 0 if a==b, 1 if a>b
		
		int compare(styp n)const;
		//-1 if a<b, 0 if a==b, 1 if a>b

		int compare(sstyp n)const;
		//-1 if a<b, 0 if a==b, 1 if a>b

		bool operator<(styp n)const{return compare(n)<0;}
		bool operator>(styp n)const{return compare(n)>0;}
		bool operator<=(styp n)const{return compare(n)<=0;}
		bool operator>=(styp n)const{return compare(n)>=0;}
		bool operator<(sstyp n)const{return compare(n)<0;}
		bool operator>(sstyp n)const{return compare(n)>0;}
		bool operator<=(sstyp n)const{return compare(n)<=0;}
		bool operator>=(sstyp n)const{return compare(n)>=0;}
		bool operator<(const luint& l)const{return compare(l)<0;}
		bool operator>(const luint& l)const{return compare(l)>0;}
		bool operator<=(const luint& l)const{return compare(l)<=0;}
		bool operator>=(const luint& l)const{return compare(l)>=0;}

	};

//================================================================================

	template<class elem,class traits>
	std::basic_ostream<elem,traits>& operator<<
		(std::basic_ostream<elem,traits>& os,const luint& big)
	{
		std::basic_string<elem,traits> str;
		unsigned base=10;
		if(os.flags() & std::ios::hex)base=16;
		if(luint::use_float_display)big.to_string_float(str,base,luint::float_display_prec);
		else big.to_string(str,base);
		return os<<str;
	}

	template<class elem,class traits>
	std::basic_istream<elem,traits>& operator>>
		(std::basic_istream<elem,traits>& is,luint& big)
	{
		std::basic_string<elem,traits> str;
		is>>str;
		if(is.flags() & std::ios::hex)big.from_hex_string(str.c_str());
		else big.from_string(str.c_str(),10);
		return is;
	}

	template<class typ>
	void luint::operator>>=(const typ& num)
	{
		if(a.empty())return;
#pragma warning(disable:4146)
		if(num<0){operator<<=(-num);return;}
#pragma warning(default:4146)
		typ quot=num/sbits;
		if(quot>=sstyp(a.size())){a.clear();return;}
		if(num>=sbits)a.erase(a.begin(),a.begin()+styp(quot));
		styp n=num%sbits;
		if(n==0)
		{shrink_to_fit();return;}
		unsigned i;
		for(i=0;i<a.size()-1;i++)
		{a[i]>>=n;a[i]|=a[i+1]>>(sbits-n);}
		a.back()>>=n;
		if(a.back()==0)a.pop_back();
	}

	template<class typ>
	void luint::operator<<=(const typ& num)
	{
		if(a.empty())return;
#pragma warning(disable:4146)
		if(num<0){operator>>=(-num);return;}
#pragma warning(default:4146)
		if(num>=sbits)a.insert(a.begin(),styp(num/sbits),0);
		styp n=num%sbits;
		if(n==0)return;
		int i;
		a.push_back(0);
		for(i=a.size()-2;i>=0;i--)
		{a[i+1]|=a[i]>>(sbits-n);a[i]<<=n;}
		if(a.back()==0)a.pop_back();
	}


	template<class dtyp>
	//dtyp can be double, float, long double, etc.
	dtyp luint::signif(int prec/*=4*/)const
	{
		int i,j;dtyp d=0;
		if(a.empty())return 0;
		for(i=int(a.size())-1,j=0;i>=0 && j<prec;--i,++j)
		{d+=dtyp(a[i])*ldexp(dtyp(1),(-j)*sbits);}
		return frexp(d,&i);
	}

	template<>
	luint::luint(btyp n):sign(true)
	//n is assumed to be unsigned
	{
		bytes<bsize> b(n);
		if(b.lo()!=0)
		{
			a.push_back(styp(b.lo()));
			if(b.hi()!=0)a.push_back(styp(b.hi()));
		}
	}

	template<>
	luint::luint(btyp n,unsigned capacity):sign(true)
	//n is assumed to be unsigned
	{
		bytes<bsize> b(n);
		if(b.lo()!=0)
		{
			a.push_back(styp(b.lo()));
			if(b.hi()!=0)a.push_back(styp(b.hi()));
		}
		a.reserve(capacity);
	}

	template<>
	void luint::operator=(btyp n)
	{
		a.clear();
		sign=true;
		bytes<bsize> b(n);
		if(b.lo()!=0)
		{
			a.push_back(styp(b.lo()));
			if(b.hi()!=0)a.push_back(styp(b.hi()));
		}
	}

}	//end of namespace eku

namespace std
{
	template<>
	inline void swap<eku::luint>(eku::luint& a,eku::luint& b)
	{a.swap(b);}

	template<>
	class numeric_limits<eku::luint>
	{
	public:
		static const bool is_signed=false;
		static const bool is_specialized=true;
		static const bool is_integer=true;
		static const bool is_exact=true;
		static const bool is_bounded=false;
		static const bool is_modulo=false;

		static eku::luint min()
		{return 0u;}
	};
}

#endif	//_INC_EKU_CLASS_LUINT