#ifndef _INC_EKU_MATH_NUMBER_BERNOULLI
#define _INC_EKU_MATH_NUMBER_BERNOULLI 1

double bernoulli(int n)
{
	if(n==0)return 1;
	else if(n==1)return -0.5;
	else if(n%2)return 0;
	double b,*a=new double[n];
	int i,j;
	for(i=0;i<=n;i++)
	{
		a[i]=1/double(i+1);
		for(j=i;j>=1;j--)a[j-1]=j*(a[j-1]-a[j]);
	}
	b=a[0];
	delete[] a;
	return b;
}

#endif //_INC_EKU_MATH_NUMBER_BERNOULLI