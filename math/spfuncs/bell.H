#ifndef _INC_EKU_MATH_NUMBER_BELL
#define _INC_EKU_MATH_NUMBER_BELL 1

int bell(int n)
{
	if(n==0 || n==1)return 1;
	int **a=new int*[n],i,j;
	a[0]=new int[1];
	a[0][0]=1;
	for(i=1;i<n;i++)
	{
		a[i]=new int[i+1];
		a[i][0]=a[i-1][i-1];
		for(j=0;j<i;j++)a[i][j+1]=a[i][j]+a[i-1][j];
	}
	i=a[n-1][n-1];
	for(i=0;i<n;++i)delete[] a[i];
	delete[] a;
	return i;
}

#endif //_INC_EKU_MATH_NUMBER_BELL