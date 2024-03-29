#ifndef _INC_EKU_MATH_COMBI_PARTITION
#define _INC_EKU_MATH_COMBI_PARTITION

#include<vector>

namespace eku
{
	template<class typ>
	typ partition(typ n,typ k)
	//number of ways of partitioning n identical elements
	//such that there are minimum of k elements in a partitions
	//p(k,n) = p(k+1,n) + p(k,n−k)
	{
		if(k>n)return 0;
		if(k==1 || k==n ||k==n-1)return 1;
		if(k==n-2)return 2;
		if(k==2)return n/2;
		if(n<=k+k){typ t=n-k;return partition(t+t-1,t-1)+1;}
		return partition(n-1,k-1)+partition(n-k,k);
	}

	template<class typ>
	typ partition(typ n)
	//optimized implementation of partition(n,n)
	//p(k) = p(k − 1) + p(k − 2) − p(k − 5) − p(k − 7) + p(k − 12) + p(k − 15) − p(k − 22) − ...
	{
		if(n<=3)return n;
		if(n==4)return 5;
		typ i,s=5;
		for(i=2;i<n-2;i++)s+=partition(n,i);
		return s;
	}
}

#endif	//_INC_EKU_MATH_COMBI_PARTITION