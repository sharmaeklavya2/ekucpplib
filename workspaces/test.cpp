#include<iostream>
#include<eku\class\luint.cpp>
#include<eku\math\fact.h>

using namespace std;
using namespace eku;

int main()
{
	unsigned a=50;
	cout<<(fact<luint>(a))<<endl;
}
