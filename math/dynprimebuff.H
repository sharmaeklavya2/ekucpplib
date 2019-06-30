#ifndef _INC_EKU_MATH_DYNPRIMEBUFF
#define _INC_EKU_MATH_DYNPRIMEBUFF

#include<string.h>
#include<eku\array.h>
#include<eku\miscfunc.h>
#include<eku\numlex\eitoa.h>
#include<eku\miscdef.h>
#include<eku\math\uipow.h>

//E:\\Eklavya\\Prime number database
#ifdef DATABASE
#include<fstream>
#endif

#ifdef USE_SQRT
#include<math.h>
#endif	//USE_SQRT

#if defined(EKUDEBUG) && !defined(_INC_OSTREAM) && !defined(_IOSTREAM_)
#undef EKUDEBUG
#endif

#ifdef EKUDEBUG
#define TIMELAG 300000
#endif

//============================================================================================

namespace eku
{

	template<typename typ>
	class primebuff
	{
		typ *a;
	public:
		int size,cap;
		typ lgen;
		primebuff(int capacity):size(8),lgen(21),cap(capacity)
		{
			a=new typ[cap];
			a[0]=2;a[1]=3;a[2]=5;a[3]=7;
			a[4]=11;a[5]=13;a[6]=17;a[7]=19;
		}
		~primebuff(){delete[] a;}
		const typ& operator[](const int n)const{return a[n];}
		typ& operator[](const int n){return a[n];}
		typ& last()const{return a[size-1];}

		void gen_till_n(typ n);
		//generates prime no. till last no. is less than n

		void gen_till_nth(int n);
		//generates prime no.s such that there are n prime nos

		typ& prime(int n){gen_till_nth(n);return a[n-1];}	//returns the nth prime
		inline int prime_inv(typ);			//inverse of prime(int)
		bool isprime(typ n){return (prime_inv(n)!=0);}	//checks if number is prime

		typ primeaft(typ n){return a[primeaft_pos(n)];}	//prime after n
		typ primebef(typ n){return a[primebef_pos(n)];}	//prime before n
		int primeaft_pos(typ n);
		int primebef_pos(typ n);	//position of (prime before n)
		
		inline int primes_bet_exc(typ a,typ b);	//primes in (a,b)
		int primes_bet_inc(typ a,typ b)	//primes in [a,b]
		{if(a>b){typ c=a;a=b;b=c;};return primes_bet_exc(a-1,b+1);}
		
		inline typ primorial(int n);		//product of 1st n primes
		inline typ primorial_till(typ n);	//product of all primes <= n

		int pfactorize(typ n,typ* store,int skip=10);
		//prime factorize, returns no. of distinct prime factors
		typ eulerphi(typ n,int skip=10);	//euler's phi function or totient function
	//	template<typename chtyp>
		void pfactorize(typ n,char* store,unsigned base=10,int skip=10);
		typ no_of_divisors(typ n);
		typ sum_of_divisors(typ n);
		typ sum_of_prop_divisors(typ n){return sum_of_divisors(n)-n;}
		bool is_amicable(typ n)
		{typ m=sum_of_prop_divisors(n);return (m!=n && n==sum_of_prop_divisors(m));}

		bool save(const char* path,int s)const;
		bool load(const char* path,int s);
		bool save(const char* path)const{return save(path,size);}
		bool load(const char* path){return load(path,cap-1);}
	};

	//============================================================================================

	template<typename typ>
	void primebuff<typ>::gen_till_n(typ n)
	{
		if(n%2==0)n++;
		int i;bool isp;//isp=isprime
	#ifdef EKUDEBUG
		clock_t timer=clock(),init=timer;
		int olsize=size;typ olgen=lgen;
		cout<<"gen_till_n:"<<endl;
	#endif	//EKUDEBUG
	#ifdef USE_SQRT
		typ uplim;
	#endif	//USE_SQRT
		for(;lgen<=n;lgen+=2)
		{
			isp=true;
	#ifndef USE_SQRT
			for(i=1;i<size;i++){if(lgen%a[i]==0){isp=false;break;}}
	#else	//USE_SQRT
			uplim=typ(sqrt(double(lgen)));
			for(i=0;a[i]<=uplim;i++){if(lgen%a[i]==0){isp=false;break;}}
	#endif	//USE_SQRT
			if(isp)a[size++]=lgen;
	#ifdef EKUDEBUG
			if(clock()-timer>TIMELAG)
			{
				cout<<"size:"<<size;
				cout<<"\tlgen:"<<lgen;
				cout<<"\tsize_inc:"<<size-olsize;
				cout<<"\tlgen_inc:"<<lgen-olgen<<endl;
				timer+=TIMELAG;olsize=size;olgen=lgen;
			}
	#endif	//EKUDEBUG
		}
	#ifdef EKUDEBUG
		cout<<"Time taken = "<<(clock()-init)/1000<<"s"<<endl;
	#ifdef _INC_WINDOWS
		Beep(512,5000);
	#endif	//_INC_WINDOWS
	#endif	//EKUDEBUG
	}

	template<typename typ>
	void primebuff<typ>::gen_till_nth(int n)
	{
		int i;bool isp;//isp means isprime
	#ifdef USE_SQRT
		typ uplim;
	#endif	//USE_SQRT
		for(;size<n;lgen+=2)
		{
			isp=true;
	#ifndef USE_SQRT
			for(i=1;i<size;i++){if(lgen%a[i]==0){isp=false;break;}}
	#else	//USE_SQRT
			uplim=typ(sqrt(double(lgen)));
			for(i=0;a[i]<=uplim;i++){if(lgen%a[i]==0){isp=false;break;}}
	#endif	//USE_SQRT
			if(isp)a[size++]=lgen;
		}
	}

	template<typename typ>
	inline int primebuff<typ>::prime_inv(typ n)
	{
		if(n>=lgen){gen_till_n(n);return ((a[size-1]==n)?size:0);}
		else return bsearch(a,size,n)+1;
	}

	template<typename typ>
	inline typ primebuff<typ>::primorial(int n)
	{
		if(n>size)gen_till_nth(n);
		int i;
		typ p=1;
		for(i=0;i<n;i++)p*=a[i];
		return p;
	}

	template<typename typ>
	inline typ primebuff<typ>::primorial_till(typ n)
	{
		if(n>size)gen_till_n(n);
		int i;
		typ p=1;
		for(i=0;a[i]<=n;i++)p*=a[i];
		return p;
	}

	template<typename typ>
	int primebuff<typ>::pfactorize(typ n,typ* store,int skip/*=10*/)
	{
		int i,pos=0;
		typ pwr;
		if(n==0){store[0]=0;return 0;}
		else if(n==1){store[0]=1;store[1]=1;store[2]=0;return 0;}
		for(i=0;a[i]<=n;i++)
		{
			for(pwr=0;n%a[i]==0;pwr++)n/=a[i];
			if(pwr>0){store[pos++]=a[i];store[pos++]=pwr;}
			if(i+1>=size)gen_till_nth(size+skip);
		}
		store[pos++]=0;
		return pos;
	}

	template<typename typ>
	typ primebuff<typ>::eulerphi(typ n,int skip/*=10*/)
	{
		int i,pwr;
		typ ans=1,a_i;
		if(n==1)return 1;
		if(isprime(n))return n-1;
		for(i=0;a[i]<=n;i++)
		{
			a_i=a[i];
			for(pwr=0;n%a_i==0;pwr++){n/=a_i;ans*=a_i;}
			if(pwr==0)continue;
			ans/=a_i;ans*=(a_i-1);
			if(i+1>=size)gen_till_nth(size+skip);
		}
		return ans;
	}

	template<class typ>
	typ primebuff<typ>::no_of_divisors(typ n)
	{
		typ a[60];
		int i;
		typ nod=1;
		pfactorize(n,a);
		for(i=0;a[i]!=0;i+=2)nod*=(a[i+1]+1);
		return nod-1;
	}

	template<class typ>
	typ primebuff<typ>::sum_of_divisors(typ n)
	{
		typ a[60];
		int i;
		typ sod=1;

		pfactorize(n,a);
		for(i=0;a[i]!=0;i+=2)sod*=((a[i]!=1)?((ipow<typ>(a[i],a[i+1]+1)-1)/(a[i]-1)):a[i+1]+1);
		return sod;
	}

	template<typename typ>
	inline int primebuff<typ>::primes_bet_exc(typ a,typ b)
	{
		if(a>b){typ c=a;a=b;b=c;}
		return primebef_pos(b)-primeaft_pos(a)+1;
	}

	template<typename typ>
	inline int primebuff<typ>::primebef_pos(typ n)
	{
		int p;
		if(a[size-3]<n)
		{
			gen_till_n(n);
			gen_till_nth(size+2);
		}
		p=binspos(a,size,n)-1;
		if(a[p]==n)p--;
		return p;
	}

	template<typename typ>
	inline int primebuff<typ>::primeaft_pos(typ n)
	{
		int p;
		if(a[size-3]<n)
		{
			gen_till_n(n);
			gen_till_nth(size+2);
		}
		p=binspos(a,size,n);
		if(a[p]==n)p++;
		return p;
	}

	template<typename typ>//,typename chtyp>
	void primebuff<typ>::pfactorize(typ n,char* store,unsigned base/*=10*/,int skip/*=10*/)
	{
		int i;
		typ pwr;
		char buff[68];
		store[0]='\0';
		if(n==0){store[0]='0';store[1]='\0';return;}
		else if(n<0){store[0]='-';store[1]='\0';n=-n;}
		if(n==1){strcat(store,"1");return;}
		for(i=0;a[i]<=n;i++)
		{
			for(pwr=0;n%a[i]==0;pwr++)n/=a[i];
			if(pwr>0)
			{
				eitoa(a[i],buff,base);strcat(store,buff);
				if(pwr>1){strcat(store,"^");eitoa(pwr,buff,base);strcat(store,buff);}
				strcat(store,"*");
			}
			if(i+1>=size)gen_till_nth(size+skip);
		}
		store[strlen(store)-1]='\0';
	}

	#if defined(_FSTREAM_) || defined(_INC_FSTREAM)

	template<typename typ>
	inline bool primebuff<typ>::save(const char* path,int s)const
	{
		STD(ofstream) ofile;
		if(s>size)gen_till_nth(s);

		ofile.open(path,STD(ios::binary));
		if(!ofile.is_open())return false;
		ofile.write((char*)a,s*sizeof(typ));
		ofile.close();
		return true;
	}

	template<typename typ>
	inline bool primebuff<typ>::load(const char* path,int s)
	{
		std::ifstream ifile;
		if(size>=s)return true;

		ifile.open(path,std::ios::binary);
		if(!ifile.is_open())return false;
		ifile.read((char*)a,s*sizeof(typ));
		size=ifile.gcount()/sizeof(typ);
		lgen=a[size-1];
		ifile.close();
		return true;
	}

}
#endif	//defined(_FSTREAM_) || defined(_INC_FSTREAM)

#endif //_INC_EKU_MATH_DYNPRIMEBUFF