#ifndef _INC_EKU_CONTAINER_STACK
#define _INC_EKU_CONTAINER_STACK
//constant sized stack
//last edited: 21-3-2013

#include<ostream>

namespace eku
{

	template<class typ,int n>
	class stack;

	template<class typ,int n,class elem,class traits>
	std::basic_ostream<elem,traits>& operator<<(std::basic_ostream<elem,traits>& os,const stack<typ,n>& s);

	template<class typ,int n>
	class stack
	{
		typ a[n];
		int _size;

	public:
		stack():_size(0){}
		stack(const stack& s):_size(s._size)
		{int i;for(i=0;i<_size;++i)a[i]=s.a[i];}

		bool push(const typ& t)
		{
			if(size==n)return false;
			a[_size++]=t;
			return true;
		}

		bool pop()
		{
			if(_size==0)return false;
			_size--;
			return false;
		}

		bool empty()const{return _size==0;}
		int size()const{return _size;}
		typ top()const{return a[_size-1];}
		void clear(){_size=0;}
		bool full(){return _size==n;}

		template<class elem,class traits>
		friend std::basic_ostream<elem,traits>& operator<<(std::basic_ostream<elem,traits>& os,const stack& s);
	};

	template<class typ,int n,class elem,class traits>
	std::basic_ostream<elem,traits>& operator<<(std::basic_ostream<elem,traits>& os,const stack<typ,n>& s)
	{
		int i;
		for(i=0;i<s._size;i++)os<<s.a[i]<<endl;
		return os;
	}

}

#endif	//_INC_EKU_CONTAINER_STACK