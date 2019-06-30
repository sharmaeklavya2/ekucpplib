#ifndef _INC_EKU_CLASS_MATRIX
#define _INC_EKU_CLASS_MATRIX
//Matrix class

//Header needs a bit of refinement

#include<eku\miscdef.h>
#include<exception>

bool materr=false;

//To see a visual message when a constructor,destructor or operator=()
//is called,#define EKUDEBUG

namespace eku
{

	class bad_eku_mat_dim:public std::exception
	{
		virtual const char* what()const throw()
		{return "Incorrect matrix dimensions";}
	}badmatdim;

	class bad_eku_mat_alloc:public std::exception
	{
		virtual const char* what()const throw()
		{return "Memory not allocated to matrix";}
	}badmatalloc;

//============================================================================================

	template<typename typ>class matrix;

	template<class typ>
	std::ostream& operator<<(std::ostream&,const matrix<typ>&);

	template<class typ>
	std::istream& operator>>(std::istream&,matrix<typ>&);

	template<class typ>
	matrix<typ> tomat(typ t,unsigned n);

	template<typename typ>
	class matrix
	{
		static inline void dimerr(){materr=true;if(throw_except)throw badmatdim;}
		static inline void allocerr(){materr=true;if(throw_except)throw badmatalloc;}
//data members
		typ* a;		//array for storing values
		bool alloc;	//is memory allocated to the array
		unsigned _m,_n;	//dimensions of matrix
	public:
		static bool throw_except,ask_dim;
		typ delim;	//default value for an elem. It isn't copied by operator=(mat&)
		unsigned rows()const{return _m;}
		unsigned clms()const{return _n;}

//constructors and destructor
		matrix():_m(0),_n(0),alloc(false){}	//no mem alloc, rows amd columns are 0 each
		~matrix(){if(alloc)delete[] a;alloc=false;}	//delete[] a;alloc=false;
//		operator typ(){return a[0];}
		matrix(typ el):_m(1),_n(1),alloc(true){a=new typ[1];*a=el;}
		matrix(unsigned p,unsigned q):_m(p),_n(q),alloc(true){a=new typ[_m*_n];}
		matrix(unsigned p,unsigned q,typ del):_m(p),_n(q),alloc(true),delim(del)
		{unsigned i,n=_m*_n;a=new typ[n];for(i=0;i<n;i++)a[i]=delim;}
		matrix(unsigned p,unsigned q,typ* b):_m(p),_n(q),alloc(true)
		{unsigned i,n=_m*_n;a=new typ[n];for(i=0;i<n;i++)a[i]=b[i];}
		matrix(const matrix& mat):_m(mat._m),_n(mat._n)
		{
			if(mat.alloc)
			{unsigned i,n=_m*_n;alloc=true;a=new typ[n];for(i=0;i<n;i++)a[i]=mat.a[i];}
			else alloc=false;
		}
#ifdef _INC_EKU_MATRIX_CMATRIX
		template<unsigned _p,unsigned _q>
		explicit matrix(const cmatrix<typ,_p,_q>& cmat):_m(_p),_n(_q),alloc(true)
		{unsigned i,n=_m*_n;a=new typ[n];for(i=0;i<n;i++)a[i]=cmat.a[i];}
#endif	//_INC_EKU_MATRIX_CMATRIX

		void swap(matrix& mat)
		{
			std::swap(mat._m,_m);
			std::swap(mat._n,_n);
			std::swap(mat.alloc,alloc);
			std::swap(mat.a,a);
		}

//essential operator overload
		void operator=(const matrix&);	//copies matrix into *this elem by elem
		void operator=(typ);		//makes *this a scalar matrix
		typ& operator[](unsigned p)const{return (typ&)(a[p]);}	//returns elem at pth pos assuming *this is 1D
		typ& operator()(unsigned p,unsigned q)const{return (typ&)(a[p*_n+q]);}	//returns elem at pth row and qth clm

//relational operator overload
		bool operator==(const matrix& mat)const	//checks equality elem by elem
		{
			if(_m!=mat._m || _n!=mat._n)return false;
			unsigned i,n=_m*_n;
			for(i=0;i<n;i++)if(a[i]!=mat.a[i])return false;
			return true;
		}
		bool operator==(const typ& t)const;
		bool operator!=(const typ& t)const{return !operator==(t);}
		bool operator!=(const matrix& mat)const{return !operator==(mat);}

//math operator overload

		matrix&	operator+()const{return *this;}
		matrix	operator-()const
		{matrix mat(_m,_n);unsigned i,n=_m*_n;for(i=0;i<n;i++)mat.a[i]=-a[i];return mat;}
		matrix	operator+(const matrix& m)const;
		matrix	operator-(const matrix& m)const;
		matrix	operator*(typ k)const
		{matrix mat(_m,_n);unsigned i,n=_m*_n;for(i=0;i<n;i++)mat.a[i]=k*a[i];return mat;}
		matrix	operator*(const matrix& m)const;
		matrix	operator/(typ k)const
		{matrix mat(_m,_n);unsigned i,n=_m*_n;for(i=0;i<n;i++)mat.a[i]=a[i]/k;return mat;}
		inline	void	operator+=(const matrix& m);
		inline	void	operator-=(const matrix& m);
		void	operator*=(typ k)
		{unsigned i,n=_m*_n;for(i=0;i<n;i++)a[i]*=k;}
		void	operator/=(typ k)
		{unsigned i,n=_m*_n;for(i=0;i<n;i++)a[i]/=k;}
		void	operator*=(const matrix& m){operator=(operator*(m));}

//non-math member functions
		void allocate(unsigned m,unsigned n)
		{
			if(!alloc){a=new typ[m*n];alloc=true;}
			else if(_m*_n!=m*n){delete[] a;a=new typ[m*n];}
			_m=m;_n=n;
		}
		bool alloced()const{return alloc;}
		void fill(typ elem){unsigned i,n=_m*_n;for(i=0;i<n;i++)a[i]=elem;}
		void fill(){unsigned i,n=_m*_n;for(i=0;i<n;i++)a[i]=delim;}

//math member functions
		inline	matrix	trn()const;	//transpose
		matrix	subm(unsigned r,unsigned c)const;	//return a matrix without row 'r' and column 'c'
		matrix	minor(unsigned r,unsigned c)const{return subm(unsigned r,unsigned c);}	//same as subm(unsigned,unsigned)
		matrix	remrow(unsigned r)const;	//remove row 'r' from *this
		matrix	remclm(unsigned c)const;	//remove column 'c' from *this
		
		void replace_clm(unsigned to_index,const matrix& mat,unsigned from_index)
		{
			if(rows()!=mat.rows())dimerr();
			if(to_index>clms() || from_index>mat.clms())dimerr();
			unsigned i;
			for(i=0;i<rows();++i)operator()(i,to_index)=mat(i,from_index);
		}

		void replace_row(unsigned to_index,const matrix& mat,unsigned from_index)
		{
			if(clms()!=mat.clms())dimerr();
			if(to_index()>rows() || from_index()>mat.rows())dimerr();
			int i;
			for(i=0;i<clms();++i)operator()(to_index,i)=mat(from_index,i);
		}

		typ	det()const;	//determinant
		matrix	adj()const;	//adjoint
		matrix	inv()const;	//inverse
		typ	cramer(typ* x,bool ret_if_base_det_zero=false)const;
		//calculates denominators of cramer's rule and stores them in array of order _m
		bool eqsolve(typ* x)const
		//solves an equation matrix (_m by _m+1) and stores results in array x of order _m
		{
			typ base_det=cramer(x,true);
			if(base_det==0)return false;
			for(i=0;i<rows();++i)x/=base_det;
			return true;
		}

		bool    issymm()const;		//checks if *this is symmetric
		bool	issksymm()const;	//checks if *this is skew-symmetric
		bool	issame()const		//checks if all elems are the same
		{unsigned i,n=_m*_n;for(i=1;i<n;i++){if(a[i]!=a[0])return false;}return true;}
		bool	iszero()const{return (issame() && a[0]==typ(0));}	//checks if *this is a 0 matrix
		bool	isdiag()const;		//checks if *this is a diagonal matrix

		bool	isscalar()const;		//checks if *this is a scalar matrix
		bool	isid()const{return ((a[0]==typ(1))?isscalar():false);}
		//checks if *this is an identity matrix


//friends
		friend std::ostream& operator<< <typ>(std::ostream&,const matrix<typ>&);
		friend std::istream& operator>><typ>(std::istream&,matrix<typ>&);
		friend matrix tomat<typ>(typ,unsigned);
	};

	template<typename typ>
	bool matrix<typ>::throw_except=true;
	template<typename typ>
	bool matrix<typ>::ask_dim=false;

	typedef matrix<double> dmat;
	typedef matrix<int> imat;

//============================================================================================

	template<typename typ>
	std::ostream& operator<<(std::ostream& os,const matrix<typ>& mat)
	{
		if(mat.alloc)
		{
			unsigned i,j,p=0;
			for(i=0;i<mat._m;i++)
			{
				for(j=0;j<mat._n;j++)os<<mat.a[p++]<<'\t';
				os<<'\n';
			}
		}
		else os<<"No contents"<<std::endl;
		return os;
	}

	template<typename typ>
	std::istream& operator>>(std::istream& is,matrix<typ>& mat)
	{
		std::ostream& os=std::cout;
		if(matrix<typ>::ask_dim==true)
		{
			unsigned m,n;
			os<<"Enter no. of rows ";
			cin>>m;
			os<<"Enter no. of columns ";
			cin>>n;
			mat.allocate(m,n);
			os<<"Enter matrix:\n";
		}
		else if(!mat.alloc){mat.allocerr();return is;}
		unsigned i,n=mat._m*mat._n;for(i=0;i<n;i++)is>>mat.a[i];
		return is;
	}

//--------------------------------------------------------------------------------------------

	template<typename typ>
	void matrix<typ>::operator=(const matrix<typ>& mat)
	{
		if(!mat.alloc)	//if mat has no memory, *this should also delete its memory
		{
			if(alloc)delete[] a;
			alloc=false;
			_m=mat._m;
			_n=mat._n;
		}
		else if(_m*_n != mat._m*mat._n)
		//if no. of elems in mat and *this are different, *this should reallocate memory
		{
			if(alloc)delete[] a;
			alloc=true;
			_m=mat._m;
			_n=mat._n;
			a=new typ[_m*_n];
		}
		else {_m=mat._m;_n=mat._n;}
		unsigned i,n=_m*_n;
		for(i=0;i<n;i++)a[i]=mat.a[i];
	}

	template<typename typ>
	void matrix<typ>::operator=(typ t)
	{
		if(_m!=_n)dimerr();
		//if *this is not square, fail
		unsigned i,n=_m*_n,k;
		for(i=0;i<n;i++)
		{
			k=i%(_m+1);
			if(k==0)a[i]=t;
			else a[i]=typ(0);
		}
	}

	template<typename typ>
	bool matrix<typ>::operator==(const typ& t)const
	{
		if(_m!=_n)return false;
		int i=0,j=0,n=_m*_n;
		for(;i<n;i++,j++)
		{
			if(j==_n+1)j=0;
			if((j==0 && a[i]!=t) || (j!=0 && a[i]!=0))return false;
		}
		return true;
	}

//--------------------------------------------------------------------------------------------

	template<typename typ>
	matrix<typ> matrix<typ>::operator+(const matrix<typ>& m)const
	{
		if(!alloc && !m.alloc)allocerr();
		else if(_m!=m._m && _n!=m._n)dimerr();
		matrix<typ> t(_m,_n);
		unsigned i,n=_m*_n;
		for(i=0;i<n;i++)t[i]=a[i]+m[i];
		return t;
	}

	template<typename typ>
	matrix<typ> matrix<typ>::operator-(const matrix<typ>& m)const
	{
		if(!alloc && !m.alloc)allocerr();
		else if(_m!=m._m && _n!=m._n)dimerr();
		matrix<typ> t(_m,_n);
		unsigned i,n=_m*_n;
		for(i=0;i<n;i++)t.a[i]=a[i]-m.a[i];
		return t;
	}

	template<typename typ>
	matrix<typ> matrix<typ>::operator*(const matrix<typ>& m)const
	{
		if(!alloc && !m.alloc)allocerr();
		else if(m._m==1 && m._n==1)return operator*(m[0]);
		else if(_m==1 && _n==1)return m.operator*(a[0]);
		else if(_n!=m._m)dimerr();
		matrix<typ> t(_m,m._n);
		unsigned i,j,k;
		for(i=0;i<_m;i++)for(j=0;j<m._n;j++)
		{
			t(i,j)=0;
			for(k=0;k<_n;k++)t(i,j)+=operator()(i,k)*m(k,j);
		}
		return t;
	}

//--------------------------------------------------------------------------------------------

	template<typename typ>
	inline void matrix<typ>::operator+=(const matrix<typ>& m)
	{
		if(!alloc && !m.alloc)allocerr();
		else if(_m!=m._m && _n!=m._n)dimerr();
		unsigned i,n=_m*_n;

		for(i=0;i<n;i++)a[i]+=m.a[i];
	}

	template<typename typ>
	inline void matrix<typ>::operator-=(const matrix<typ>& m)
	{
		if(!alloc && !m.alloc)allocerr();
		else if(_m!=m._m && _n!=m._n)dimerr();
		unsigned i,n=_m*_n;
		for(i=0;i<n;i++)a[i]-=m.a[i];
	}

	template<typename typ>
	inline matrix<typ> operator/(typ k,const matrix<typ>& m){return m.inv()*m;}

	template<typename typ>
	inline matrix<typ> operator*(typ k,const matrix<typ>& m){return m*k;}

//--------------------------------------------------------------------------------------------

	template<typename typ>
	inline matrix<typ> matrix<typ>::trn()const
	{
		if(!alloc)allocerr();
		matrix<typ> mat(_n,_m);
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<_n;j++)mat(j,i)=operator()(i,j);
		return mat;
	}

	template<typename typ>
	matrix<typ> matrix<typ>::subm(unsigned r,unsigned c)const
	{
		if(!alloc)allocerr();
		matrix<typ> s(_m-1,_n-1);
		unsigned i,j;
		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)s(i,j)=operator()(i,j);
			for(;j<s._n;j++)s(i,j)=operator()(i,j+1);
		}
		for(;i<s._m;i++)
		{
			for(j=0;j<c;j++)s(i,j)=operator()(i+1,j);
			for(;j<s._n;j++)s(i,j)=operator()(i+1,j+1);
		}
		return s;
	}

	template<typename typ>
	matrix<typ> matrix<typ>::remrow(unsigned r)const
	{
		if(!alloc)allocerr();
		matrix<typ> s(_m-1,_n);
		unsigned i,j;
		for(i=0;i<r;i++)for(j=0;j<_n;j++)s(i,j)=operator()(i,j);
		for(;i<s._m;i++)for(j=0;j<_n;j++)s(i,j)=operator()(i+1,j);
		return s;
	}

	template<typename typ>
	matrix<typ> matrix<typ>::remclm(unsigned c)const
	{
		if(!alloc)allocerr();
		matrix<typ> s(_m,_n-1);
		unsigned i,j;
		for(i=0;i<_m;i++)
		{
			for(j=0;j<c;j++)s(i,j)=operator()(i,j);
			for(;j<s._n;j++)s(i,j)=operator()(i,j+1);
		}
		return s;
	}

	template<typename typ>
	typ matrix<typ>::det()const
	{
		if(!alloc)allocerr();
		else if(_m!=_n)dimerr();
		if(_m==0)return 1;
		else if(_m==1)return a[0];
		else if(_m==2)return a[0]*a[3]-a[1]*a[2];
		else
		{
			unsigned i;typ d=0;
			for(i=0;i<_m;i++)
			{d+=typ((i%2==0)?1:-1)*a[i]*(subm(0,i).det());}
			return d;
		}
	}

	template<typename typ>
	matrix<typ> matrix<typ>::adj()const
	{
		if(!alloc)allocerr();
		else if(_m!=_n)dimerr();
		matrix<typ> ad(_m,_m);
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<_m;j++)
		{ad(i,j)=typ(((i+j)%2==0)?1:-1)*(subm(j,i).det());}
		return ad;
	}

	template<typename typ>
	inline matrix<typ> matrix<typ>::inv()const
	{
		matrix<typ> in(adj());
		typ x=det();
		return in/x;
	}

	template<typename typ>
	typ matrix<typ>::cramer(typ* x,bool ret_if_base_det_zero/*=false*/)const
	//if size of matrix is n by n+1, size of x is n
	{
		if(!alloc)allocerr();
		else if(_n!=_m+1)dimerr();
		unsigned i;
		typ base_det;
		matrix<typ> tmp(_m,_m);
		tmp=remclm(_m);
		base_det=tmp.det();
		if(ret_if_base_det_zero && base_det==0)return base_det;
		for(i=0;i<_m;i++)
		{
			tmp.replace_clm(i,*this,_m);
			x[i]=tmp.det();
			tmp.replace_clm(i,*this,i);
		}
		return base_det;
	}

	template<typename typ>
	bool matrix<typ>::issymm()const
	{
		if(!alloc)allocerr();
		else if(_m!=_n)dimerr();
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<=i;j++)
		{if(operator()(i,j)!=operator()(j,i))return false;}
		return true;
	}

	template<typename typ>
	bool matrix<typ>::issksymm()const
	{
		if(!alloc)allocerr();
		else if(_m!=_n)dimerr();
		unsigned i,j;
		for(i=0;i<_m;i++)for(j=0;j<=i;j++)
		{if(operator()(i,j)!=-operator()(j,i))return false;}
		return true;
	}

	template<typename typ>
	bool matrix<typ>::isdiag()const
	{
		if(!alloc)allocerr();
		else if(_m!=_n)dimerr();
		unsigned i,n=_m*_n,k;
		for(i=0;i<n;i++)
		{
			k=i%(_m+1);
			if(k!=0){if(a[k]!=typ(0))return false;}
		}
		return true;
	}


	template<typename typ>
	bool matrix<typ>::isscalar()const
	{
		if(!alloc)allocerr();
		else if(_m!=_n)dimerr();
		unsigned i,n=_m*_n,k;
		for(i=0;i<n;i++)
		{
			k=i%(_m+1);
			if(k!=0){if(a[k]!=typ(0))return false;}
			else {if(a[i]!=a[0])return false;}
		}
		return true;
	}


	template<typename typ>
	matrix<typ> tomat(typ t,unsigned n)
	{
		matrix<typ> mat(n,n);
		unsigned i,k,s=n*n;
		for(i=0;i<s;i++)
		{
			k=i%(n+1);
			if(k==0)mat[i]=t;
			else mat[i]=0;
		}
		return mat;
	}

}
#endif //_INC_EKU_CLASS_MATRIX