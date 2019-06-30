#ifndef _INC_EKU_CLASS_CMATRIX
#define _INC_EKU_CLASS_CMATRIX
//cmatrix class - container to store matrices of const order

#include<istream>
#include<ostream>

namespace eku
{
//cmatrix=class===============================================================================

	template<class typ,unsigned n>
	class sqcmatrix;

	template<typename typ,unsigned m,unsigned n>
	class cmatrix
	{
	public:
		const static unsigned _size=m*n;
	protected:
		typ a[_size];	//array for storing values
		static bool errflag;
	public:
		static void diverr(){errflag=true;}
		unsigned rows()const{return m;}
		unsigned clms()const{return n;}
//constructors and destructor
		cmatrix(){}
		cmatrix(typ* b)
		{unsigned i;for(i=0;i<_size;++i)a[i]=b[i];}
		cmatrix(const cmatrix& mat)
		{unsigned i;for(i=0;i<_size;i++)a[i]=mat[i];}

//essential operator overload
		void operator=(const cmatrix& mat)	//copies mat into *this elem by elem
		{unsigned i;for(i=0;i<_size;i++)a[i]=mat[i];}
		const typ& operator[](unsigned p)const{return a[p];}	//returns elem at pth pos assuming *this is 1D
		typ& operator[](unsigned p){return a[p];}	//returns elem at pth pos assuming *this is 1D
		const typ& operator()(unsigned p,unsigned q)const{return a[p*n+q];}	//returns elem at pth row and qth clm
		typ& operator()(unsigned p,unsigned q){return a[p*n+q];}	//returns elem at pth row and qth clm

//relational operator overload
		bool operator==(const cmatrix& mat)const	//checks equality elem by elem
		{
			unsigned i;
			for(i=0;i<_size;i++)if(a[i]!=mat[i])return false;
			return true;
		}
		bool operator!=(const cmatrix& mat)const{return !operator==(mat);}

//operator overload

		cmatrix& operator+()const{return *this;}
		cmatrix	operator-()const
		{cmatrix mat;unsigned i;for(i=0;i<_size;i++)mat[i]=-a[i];return mat;}
		cmatrix	operator*(const typ& k)const
		{cmatrix mat;unsigned i;for(i=0;i<_size;i++)mat[i]=k*a[i];return mat;}
		cmatrix	operator/(const typ& k)const
		{cmatrix mat;unsigned i;for(i=0;i<_size;i++)mat[i]=a[i]/k;return mat;}
		void operator*=(const typ& k)
		{unsigned i;for(i=0;i<_size;i++)a[i]*=k;}
		void operator/=(const typ& k)
		{unsigned i;for(i=0;i<_size;i++)a[i]/=k;}

		void operator+=(const cmatrix& m)
		{unsigned i;for(i=0;i<_size;i++)a[i]+=m[i];}
		void operator-=(const cmatrix& m)
		{unsigned i;for(i=0;i<_size;i++)a[i]-=m[i];}
		cmatrix	operator+(const cmatrix& m)const
		{
			cmatrix t;unsigned i;
			for(i=0;i<_size;i++)t[i]=a[i]+m[i];
			return t;
		}
		cmatrix	operator-(const cmatrix& m)const
		{
			cmatrix t;unsigned i;
			for(i=0;i<_size;i++)t[i]=a[i]-m[i];
			return t;
		}
		void fill(typ elem){unsigned i;for(i=0;i<_size;i++)a[i]=elem;}

	};

	template<class typ,unsigned m,unsigned n>
	bool cmatrix<typ,m,n>::errflag=false;

//sqcmatrix-class-----------------------------------------------------------------------------

	template<class typ,unsigned n>
	class sqcmatrix:public cmatrix<typ,n,n>
	{public:

		typedef cmatrix<typ,n,n> base;
		sqcmatrix(){}
		sqcmatrix(const typ& t)
		{unsigned i;for(i=0;i<_size;++i)a[i]=(i%(n+1)==0)?t:0;}
		sqcmatrix(const base& m):base(m){}
		sqcmatrix(const sqcmatrix& m):base(m){}
		operator const base&()const{return static_cast<cmatrix<typ,n,n> >(*this);}

		bool operator==(const typ& t)const;
		typ det()const{return eku::det(*this);}
		sqcmatrix adj()const{return eku::adj(*this);}
		sqcmatrix inv()const{return eku::inv(*this);}
		bool issymm()const;
		bool issksymm()const;
		bool isdiag()const;

		void operator*=(const base& m)
		{operator*=(base(*this),m);}

		sqcmatrix operator*(const base& m)
		{return sqcmatrix(eku::operator*(base(*this),m));}

	};

//IO=operations===============================================================================

	template<typename typ,unsigned _m,unsigned _n,class elem,class traits>
	std::basic_ostream<elem,traits>& operator<<(std::basic_ostream<elem,traits>& os,const cmatrix<typ,_m,_n>& mat)
	{
		unsigned i,j,p=0;
		for(i=0;i<_m;i++)
		{
			for(j=0;j<_n;j++)os<<mat[p++]<<'\t';
			os<<'\n';
		}
		return os;
	}

	template<typename typ,unsigned m,unsigned n,class elem,class traits>
	inline std::basic_istream<elem,traits>& operator>>(std::basic_istream<elem,traits>& is,cmatrix<typ,m,n>& mat)
	{unsigned i;for(i=0;i<cmatrix<typ,m,n>::_size;i++)is>>mat.operator[](i);return is;}

//operator==(const-typ&-t)--------------------------------------------------------------------

	template<typename typ,unsigned _n>
	bool sqcmatrix<typ,_n>::operator==(const typ& t)const
	{
		int i=0,j=0;
		for(;i<_size;i++,j++)
		{
			if(j==_n+1)j=0;
			if((j==0 && a[i]!=t) || (j!=0 && a[i]!=0))return false;
		}
		return true;
	}

//multiplication------------------------------------------------------------------------------

	template<typename typ,unsigned _m,unsigned _p,unsigned _n>
	cmatrix<typ,_m,_n> operator*(const cmatrix<typ,_m,_p>& a,const cmatrix<typ,_p,_n>& b)
	{
		cmatrix<typ,_m,_n> t;
		unsigned i,j,k;
		for(i=0;i<_m;i++)for(j=0;j<_n;j++)
		{
			t(i,j)=0;
			for(k=0;k<_p;k++)t(i,j)+=a(i,k)*b(k,j);
		}
		return t;
	}

	template<typename typ,unsigned _m,unsigned _n>
	inline cmatrix<typ,_m,_n> operator*(typ k,const cmatrix<typ,_m,_n>& m){return m*k;}

	template<typename typ,unsigned _m,unsigned _n>
	inline void operator*=(cmatrix<typ,_m,_n>& a,const cmatrix<typ,_n,_n>& b){a=a*b;}

//Submatrix-----------------------------------------------------------------------------------

	template<typename typ,unsigned _m,unsigned _n>
	cmatrix<typ,_m-1,_n-1> subm(const cmatrix<typ,_m,_n>& a,unsigned r,unsigned c)
	{
		cmatrix<typ,_m-1,_n-1> s;
		unsigned i,j;
		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)s(i,j)=a(i,j);
			for(;j<_n-1;j++)s(i,j)=a(i,j+1);
		}
		for(;i<_m-1;i++)
		{
			for(j=0;j<c;j++)s(i,j)=a(i+1,j);
			for(;j<_n-1;j++)s(i,j)=a(i+1,j+1);
		}
		return s;
	}

	template<typename typ,unsigned _m,unsigned _n>
	cmatrix<typ,_m-1,_n> remrow(const cmatrix<typ,_m,_n>& a,unsigned r)
	{
		cmatrix<typ,_m-1,_n> s;
		unsigned i,j;
		for(i=0;i<r;i++)for(j=0;j<_n;j++)s(i,j)=a(i,j);
		for(;i<_m-1;i++)for(j=0;j<_n;j++)s(i,j)=a(i+1,j);
		return s;
	}

	template<typename typ,unsigned _m,unsigned _n>
	cmatrix<typ,_m,_n-1> remclm(const cmatrix<typ,_m,_n>& a,unsigned c)
	{
		cmatrix<typ,_m,_n-1> s;
		unsigned i,j;
		for(i=0;i<_m;i++)
		{
			for(j=0;j<c;j++)s(i,j)=a(i,j);
			for(;j<_n-1;j++)s(i,j)=a(i,j+1);
		}
		return s;
	}

//Determinant,-adjoint-and-inverse------------------------------------------------------------

	template<class typ>
	inline typ det(const cmatrix<typ,1,1>& mat)
	{return mat.a[0];}

	template<typename typ>
	inline typ det(const cmatrix<typ,2,2>& mat)
	{return mat[0]*mat[3]-mat[1]*mat[2];}

	template<typename typ,unsigned n>
	typ det(const cmatrix<typ,n,n>& a)
	{
		unsigned i;typ d=0,s;
		for(i=0;i<n;i++)
		{
			if(a[i]!=0)s=a[i]*(det(subm(a,0,i)));
			else continue;
			(i%2==0)?d+=s:d-=s;
		}
		return d;
	}

	template<typename typ>
	cmatrix<typ,1,1> adj(const cmatrix<typ,1,1>& a){}

	template<class typ>
	cmatrix<typ,2,2> adj(const cmatrix<typ,2,2>& m)
	{
		cmatrix<typ,2,2> a;
		a[0]=m.operator[](3);a[3]=m.operator[](0);
		a[1]=-m.operator[](1);a[2]=-m.operator[](2);
		return a;
	}

	template<typename typ,unsigned _m>
	cmatrix<typ,_m,_m> adj(const cmatrix<typ,_m,_m>& a)
	{
		cmatrix<typ,_m,_m> ad;
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<_m;j++)
		{
			ad(i,j)=typ(det(subm(a,j,i)));
			if((i+j)%2==1)ad(i,j)=-ad(i,j);
		}
		return ad;
	}

	template<typename typ>
	inline cmatrix<typ,1,1> inv(const cmatrix<typ,1,1>& a)
	{if(a[0]==0)cmatrix<typ,1,1>::diverr();else return 1/a[0];}

	template<typename typ,unsigned _m>
	inline cmatrix<typ,_m,_m> inv(const cmatrix<typ,_m,_m>& a)
	{
		cmatrix<typ,_m,_m> in(adj(a));
		typ x=det(a);
		if(x==typ(0)){cmatrix<typ,_m,_m>::diverr();return in;}
		else return in/x;
	}

//eqsolve-------------------------------------------------------------------------------------

	template<typename typ,unsigned _m>
	bool eqsolve(const cmatrix<typ,_m,_m+1>& a,typ* x)
	{
		int i,j,k;
		cmatrix<typ,_m,_m> tmp;
		for(i=0;i<=_m;i++)
		{
			for(j=0;j<_m;j++)for(k=0;k<_m;k++)tmp(j,k)=a(j,k);
			if(i<_m)for(j=0;j<_m;j++)tmp(j,i)=a(j,_m);
			x[i]=det(tmp);
		}
		if(x[_m]==0)return false;
		else for(i=0;i<_m;i++)x[i]/=x[_m];
		return true;
	}

//symmetry------------------------------------------------------------------------------------

	template<typename typ,unsigned _m>
	inline bool sqcmatrix<typ,_m>::issymm()const
	{
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<=i;j++)
		{if(operator()(i,j)!=operator()(j,i))return false;}
		return true;
	}

	template<typename typ,unsigned _m>
	inline bool sqcmatrix<typ,_m>::issksymm()const
	{
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<=i;j++)
		{if(operator()(i,j)!=-operator()(j,i))return false;}
		return true;
	}

	template<typename typ,unsigned _m>
	bool sqcmatrix<typ,_m>::isdiag()const
	{
		unsigned i,k;
		for(i=0;i<_size;i++)
		{
			k=i%(_m+1);
			if(k!=0){if(a[k]!=typ(0))return false;}
		}
		return true;
	}

	template<typename typ,unsigned _m,unsigned _n>
	inline cmatrix<typ,_n,_m> trn(const cmatrix<typ,_m,_n>& a)
	{
		cmatrix<typ,_n,_m> mat;
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<_n;j++)mat(j,i)=a(i,j);
		return mat;
	}
}

#endif //_INC_EKU_CLASS_CMATRIX