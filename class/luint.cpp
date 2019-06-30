#include"eku\class\luint.h"

namespace eku
{
	bool luint::use_float_display=false;
	unsigned luint::float_display_prec=0;

	void luint::from_hex_string(const char* str)
	{
		const unsigned ssize2=ssize+ssize;
		char str2[ssize2+1];
		int i,j;
		a.clear();
		sign=true;
		for(i=0;str[i]!='\0';i++);
		for(i-=ssize2;i>=0;i-=ssize2)
		{
			for(j=0;j<ssize2;j++)str2[j]=str[i+j];
			str2[j]='\0';
			a.push_back(hex_to_num<int>(str2));
		}
		if(i!=-int(ssize2))
		{
			i+=ssize2;
			str2[i--]='\0';
			for(;i>=0;i--)str2[i]=str[i];
			a.push_back(hex_to_num<int>(str2));
		}
	}

	void luint::plusme_l(const luint& l)
	{
		if(a.empty()){a=l.a;sign=l.sign;return;}
		unsigned i,m=std::min(a.size(),l.a.size());
		btyp carry=0;
		for(i=0;i<m;i++)
		{
			carry+=btyp(l.a[i])+btyp(a[i]);
			a[i]=styp(carry);
			carry>>=sbits;
		}
		for(;i<a.size() && carry!=0;i++)
		{
			carry+=btyp(a[i]);
			a[i]=styp(carry);
			carry>>=sbits;
		}
		for(;i<l.a.size() && carry!=0;i++)
		{
			carry+=btyp(l.a[i]);
			a.push_back(styp(carry));
			carry>>=sbits;
		}
		for(;i<l.a.size();i++)a.push_back(l.a[i]);
		if(carry!=0)a.push_back(styp(carry));
	}

	void luint::plusme_s(styp n)
	{
		unsigned i;
		if(a.empty()){operator=(n);return;}
		btyp carry=btyp(n)+btyp(a[0]);
		a[0]=styp(carry);
		carry>>=sbits;
		for(i=1;i<a.size();i++)if(carry!=0)
		{
			carry+=btyp(a[i]);
			a[i]=styp(carry);
			carry>>=sbits;
		}
	}

	int luint::compare(const luint& l)const
	//-1 if a<b, 0 if a==b, 1 if a>b
	{
		if(sign && !l.sign)return 1;
		else if(!sign)return -1;
		if(a.size()<l.a.size())return -1;
		if(a.size()>l.a.size())return 1;
		int i;
		for(i=a.size()-1;i>=0;--i)
		{
			if(a[i]<l.a[i])return -1;
			if(a[i]>l.a[i])return 1;
		}
		return 0;
	}

	int luint::compare(styp n)const
	//-1 if a<b, 0 if a==b, 1 if a>b
	{
		if(!sign)return -1;
		if(a.size()>1)return 1;
		else if(a.empty()){return (n==0u)?0:-1;}
		else if(a[0]<n)return -1;
		else if(a[0]>n)return 1;
		else return 0;
	}

	int luint::compare(sstyp n)const
	//-1 if a<b, 0 if a==b, 1 if a>b
	{
		if(sign && n<0)return 1;
		if(!sign)return -1;
		if(a.size()>1)return 1;
		else if(a.empty()){return (n==0)?0:-1;}
		else if(a[0]<styp(n))return -1;
		else if(a[0]>styp(n))return 1;
		else return 0;
	}

	void luint::minusme_s(styp n)
	{
		int i;
		if(a.empty() || (a.size()==1 && a[0]<n)){sign=false;return;}
		if(a[0]>=n){a[0]-=n;return;}
		else a[0]=styp(bytes<bsize>(1,a[0])-n);
		for(i=1;a[i]==0;i++)a[i]=styp(~0);
		a[i]--;
		if(a.back()==0)a.pop_back();
	}

	void luint::minusme_b(btyp n)
	{
		int i;bool carry=false;
		bytes<bsize> bn(n),ba(a[1],a[0]);
		styp nhi=bn.hi(),nlo=bytes<bsize>(n).lo(),tominus=0;
		if(a.empty() || (a.size()==1 && btyp(a[0])<n) || (a.size()==2 && ba<n))
		{sign=false;return;}
		if(a[0]>=nlo){a[0]-=nlo;}
		else {a[0]=styp(bytes<bsize>(1,a[0])-btyp(nlo));carry=true;}
		tominus=carry?nhi+1:nhi;
		if(a[1]>=tominus)
		{a[1]-=tominus;return;}
		else {a[1]=styp(bytes<bsize>(1,a[1])-btyp(tominus));carry=true;}
		for(i=2;a[i]==0;i++)a[i]=~0;
		a[i]--;
		if(a.back()==0)a.pop_back();
	}

	void luint::minusme_l(const luint& big)
	//not tested
	{
		bool carry=false;
		int i;
		styp tominus;

		i=compare(big);
		if(i<0){sign=false;return;}
		else if(i==0){a.clear();return;}
		for(i=0;i<int(big.a.size());i++)
		{
			tominus=big.a[i];
			if(carry)++tominus;
			if(a[i]>=tominus){a[i]-=tominus;carry=false;}
			else {a[i]=styp(bytes<bsize>(1,a[i])-btyp(tominus));carry=true;}
		}
		shrink_to_fit();
		if(!carry)return;
		for(;i<int(a.size()) && a[i]==0;i++)a[i]=~0;
		--a[i];
		shrink_to_fit();
	}

	void luint::plusme_b(btyp n)
	{
		bool carry=false;
		if(a.empty()){operator=(n);return;}

		bytes<bsize> bn(n),bsum(0);
		btyp nhi=btyp(bn.hi()),nlo=btyp(bn.lo()),sum=0;
		int i;

		sum=btyp(a[0])+nlo;
		carry=bytes<bsize>(sum).hi()>0;
		a[0]=styp(sum);

		if(a.size()==1)a.push_back(0);
		sum=btyp(a[1])+nhi;
		if(carry)++sum;
		carry=bytes<bsize>(sum).hi()>0;
		a[1]=styp(sum);

		if(carry)
		{
			for(i=2;i<int(a.size()) && a[i]==styp(~0);i++)a[i]=0;
			if(i==a.size())a.push_back(1);
			else a[i]++;
		}
	}

	void luint::operator*=(styp n)
	{
		unsigned i;
		btyp carry=0;
		if(n==0){a.clear();return;}
		for(i=0;i<a.size();i++)
		{
			carry+=btyp(a[i])*n;
			a[i]=styp(carry);
			carry>>=sbits;
		}
		if(carry!=0)a.push_back(styp(carry));
	}

	void luint::multiply(const luint& big,luint& result)const
	{
		unsigned i;
		luint inter;	//intermediate
		if(big.a.empty()){result.a.clear();return;}
		if(big.a.size()==1)
		{result=*this;result*=big.a[0];return;}
		for(i=0;i<big.a.size();i++)
		{
			inter.a=a;
			inter*=big.a[i];
			inter.a.insert(inter.a.begin(),i,styp(0));
			result.plusme_l(inter);
		}
	}

	luint::styp luint::divide(styp n)
	{
		int i;
		btyp divid,rem=0;
		for(i=int(a.size())-1;i>=0;i--)
		{
			divid=(rem<<sbits)+a[i];
			a[i]=styp(divid/n);
			rem=divid%n;
		}
		if(a.back()==0)a.pop_back();
		return styp(rem);
	}

	luint::styp luint::operator%(styp n)const
	{
		int i;
		btyp divid,rem=0;
		for(i=int(a.size())-1;i>=0;i--)
		{
			divid=(rem<<sbits)+a[i];
			rem=divid%n;
		}
		return styp(rem);
	}

	void luint::from_string(const char* str,styp base)
	{
		unsigned i;
		a.clear();
		sign=true;
		styp digit;
		for(i=0;str[i]!='\0';++i)
		{
			operator*=(base);
			digit=char_to_digit<styp>(str[i]);
			if(digit>=base)
			{a.clear();sign=false;break;}
			plusme_s(digit);
		}
	}

	unsigned luint::exponent()const
	//gets integral part of logarithm of *this to the base 2
	{
		if(a.empty())return 0;
		styp v=a.back();
		unsigned exp=0;
		while(v){exp++;v>>=1;}
		return exp+(a.size()-1)*sbits;
	}

	void luint::divide(const luint& divisor,luint& quotient,bool leaverem/*=true*/)
	//after this operation *this stores the remainder
	{
		int i,j=compare(divisor);double dquot;
		styp quot;quotient.a.clear();
		if(j<0)return;
		else if(j==0){quotient=1;a.clear();return;}
		if(divisor.a.size()==1)
		{
			styp rem=divide(divisor.a[0]);
			std::swap(quotient.a,a);
			if(leaverem)operator=(rem);
			return;
		}

		luint dvsor(divisor),subtractend;

		if(!leaverem)
		{
			for(i=0;dvsor.a[i]==0;++i);
			dvsor.a.erase(dvsor.a.begin(),dvsor.a.begin()+i);
			a.erase(a.begin(),a.begin()+i);
		}

		i=a.size()-dvsor.a.size();
		
		dvsor.a.insert(dvsor.a.begin(),i,0);
		for(;i>=0;--i)
		{
				dquot=as_double<double>()/dvsor.as_double<double>();
				//Confirmed bug: if number is too long, conversion to double fails
				quot=styp(dquot);
				//if dquot is 1+range_of_styp, quot becomes 0
				if(dquot>=100.0 && quot==0)quot=styp(~0);
				if(quot!=0)
				{
					subtractend=dvsor;subtractend*=quot;
					if(operator<(subtractend))
					{--quot;subtractend.minusme_l(dvsor);}
					minusme_l(subtractend);
				}
				quotient.a.push_back(quot);
				dvsor.a.erase(dvsor.a.begin());
		}
		for(i=0,j=int(quotient.a.size())-1;i<j;++i,--j)
		{quot=quotient.a[i];quotient.a[i]=quotient.a[j];quotient.a[j]=quot;}
		if(quotient.a.back()==0)quotient.a.pop_back();
	}

	void luint::operator%=(const luint& divisor)
	//after this 
	{
		int j=compare(divisor);
		if(j<0){;return;}
		else if(j==0){a.clear();return;}

		if(divisor.a.size()==1)
		{
			operator=(operator%(divisor.a[0]));
			return;
		}

		luint dvsor(divisor),subtractend;
		int i=a.size()-dvsor.a.size();
		styp quot;
		
		dvsor.a.insert(dvsor.a.begin(),i,0);
		for(;i>=0;--i)
		{
				quot=styp(as_double<double>()/dvsor.as_double<double>());
				if(quot!=0)
				{
					subtractend=dvsor;subtractend*=quot;
					if(operator<(subtractend))
					{--quot;subtractend.minusme_l(dvsor);}
					minusme_l(subtractend);
				}
				dvsor.a.erase(dvsor.a.begin());
		}
	}

	void luint::to_hex_string(std::string& str)const
	//stores the luint's hexadecimal representation in str
	{
		int i,j,ssize2=ssize<<1;
		char buff[18];
		str.clear();
		if(!sign){str="-e";return;}
		for(i=a.size()-1;i>=0;i--)
		{
			num_to_hex(a[i],buff);
			if(i==a.size()-1)
			{
				for(j=0;buff[j]=='0';++j);
				if(buff[j]=='\0')--j;
				std::strcpy(buff,buff+j);
			}
			str.append(buff);
		}
	}

	void luint::to_string(std::string& str,styp base)const
	//stores the luint's representation in str
	{
		int i,j;char ch;
		str.clear();
		if(base==16u)to_hex_string(str);
		else
		{
			if(!sign){str="-e";return;}
			if(a.empty()){str.push_back('0');return;}
			luint big(*this);
			for(i=0;big>0u;i++)str.push_back(digit_to_char(big.divide(base)));
			j=i-1;i=0;
			for(;i<j;i++,j--){ch=str[i];str[i]=str[j];str[j]=ch;}
		}
	}

	void luint::to_string_float(std::string& str,
		styp base,unsigned maxprec/*=0*/,unsigned max_digits/*=4*/)const
	//stores the luint's floating point like representation in str
	{
		char buff[40];
		unsigned exp;
		int i;
		to_string(str,base);
		if(str.size()==0){str="0";return;}
		if(str.size()<=max_digits)return;
		exp=str.size()-1;
		for(i=str.size()-1;str[i]=='0';--i);
		str.erase(i+1);
		if(maxprec!=0 && maxprec<str.size())str.resize(maxprec);
		if(str.size()>1)str.insert(1,1,'.');
		str.append("e+");
		euitoa(exp,buff,base);
		str.append(buff);
	}

}	//end of namespace eku