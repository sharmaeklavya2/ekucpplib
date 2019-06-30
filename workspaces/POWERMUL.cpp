#include<iostream>
#include<algorithm>
#include<map>
#include<ctime>

unsigned plist_size=68,plist[]=
{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,
101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,
211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,
307,311,313,317,331,337};

inline unsigned square(unsigned n)
{return n*n;}

/*class prpwr_pair
{
public:
	unsigned pr;
	int pwr;
	num_pwr_pair(unsigned prime,int power):pr(prime),pwr(power){}
	num_pwr_pair():pr(0),pwr(0){}
};*/

typedef std::map<unsigned,int>::iterator mapit;
typedef std::map<unsigned,int>::const_iterator mapcit;

class factored_num
{
public:
	std::map<unsigned,int> facs;
	factored_num(unsigned);
};

factored_num::factored_num(unsigned n)
{
	unsigned i,prime,pwr;
	mapit ins_pos=facs.begin();
	for(i=0;square(plist[i])<=n;++i)
	{
		prime=plist[i];
		pwr=0;
		while(n%prime==0)
		{n/=prime;++pwr;}
		if(pwr>0)ins_pos=facs.insert(ins_pos,std::make_pair(prime,pwr));
	}
	if(n!=1)facs.insert(ins_pos,std::make_pair(n,1));
}

void operator*=(factored_num& a,const factored_num& b)
{
	mapcit itb;
	std::pair<mapit,bool> itabool;
	for(itb=b.facs.begin();itb!=b.facs.end();++itb)
	{
		itabool=a.facs.insert(*itb);
		if(!itabool.second)itabool.first->second+=itb->second;
	}
}

void operator/=(factored_num& a,const factored_num& b)
{
	mapcit itb;
	std::pair<mapit,bool> itabool;
	unsigned prime;
	int pwr;
	for(itb=b.facs.begin();itb!=b.facs.end();++itb)
	{
		prime=itb->first;
		pwr=itb->second;
		itabool=a.facs.insert(std::make_pair(prime,-pwr));
		if(!itabool.second)itabool.first->second-=itb->second;
	}
}

void raise(factored_num& fn,int n)
{
	mapit it=fn.facs.begin();
	for(;it!=fn.facs.end();++it)it->second*=n;
}

std::ostream& operator<<(std::ostream& os,const factored_num& fn)
{
	if(fn.facs.empty())return os<<'1';
	mapcit it=fn.facs.begin();
	unsigned prime=it->first;int pwr=it->second;
	os<<prime;
	if(pwr!=1)os<<'^'<<pwr;
	++it;
	for(;it!=fn.facs.end();++it)
	{
		prime=it->first;
		pwr=it->second;
		os<<'*'<<prime;
		if(pwr!=1)os<<'^'<<pwr;
	}
	return os;
}

using namespace std;
int main()
{
	unsigned i,n,start,stop;
	cin>>n;
	factored_num prod(1),fpart(1);
	start=clock();
	for(i=1;i<=n;++i)
	{
		fpart=i;
		raise(fpart,i);
		prod*=fpart;
	}
	stop=clock();
	cout<<prod.facs.size()<<endl;
	cout<<"Time taken = "<<stop-start<<endl;
	return 0;
}