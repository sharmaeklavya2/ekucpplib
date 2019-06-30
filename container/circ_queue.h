#ifndef _INC_EKU_CONTAINER_CIRC_QUEUE
#define _INC_EKU_CONTAINER_CIRC_QUEUE
//Circular queue class
//This class uses a static array to make a circular queue

#include<istream>
#include<ostream>

namespace eku
{

	template<class typ,int n>
	class circ_queue
	{
		typ a[n];
		int start,end;
		unsigned count;

	public:
		//constructors
		circ_queue():start(0),end(0),count(0){}
		circ_queue(typ t):start(0),end(1),count(1){a[0]=t;}
		
		//element access
		unsigned size()const
		{return count;}
		typ front()const
		{return a[start];}
		typ back()const
		{return a[(end==0?n:end)-1];}
		bool empty()const
		{return count==0;}
		bool full()const
		{return count==n;}
		void clear()
		{start=0;end=0;count=0;}
		
		//operations
		bool deq()
		{
			if(count==0)return false;
			++start;
			--count;
			if(start==n)start=0;
			return true;
		}
		
		bool enq(typ t)
		{
			if(count==n)return false;
			a[end]=t;
			++end;
			++count;
			if(end==n)end=0;
			return true;
		}
		
		template<class elem,class traits>
		void disp(std::basic_ostream<elem,traits>& os)const
		{
			int i;
			if(end>start)for(i=start;i<end;++i)os<<a[i]<<'\t';
			else if(count!=0)
			{
				for(i=start;i<n;i++)os<<a[i]<<'\t';
				for(i=0;i<end;++i)os<<a[i]<<'\t';
			}
		}

		template<class elem,class traits>
		void clear_n_get(std::basic_istream<elem,traits>& is,int noe)
		{
			if(noe>n)return;
			start=0;
			for(end=0;end<noe;++end)is>>a[end];
			count=end;
		}

	};

	template<class typ,int n,class elem,class traits>
	inline std::basic_ostream<elem,traits>& operator<<(std::basic_ostream<elem,traits>& os,const circ_queue<typ,n>& q)
	{q.disp(os);return os;}

}	//end of namespace eku

#endif	//_INC_EKU_CONTAINER_CIRC_QUEUE