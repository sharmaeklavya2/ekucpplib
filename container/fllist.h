#ifndef _INC_EKU_CONTAINER_FLLIST
#define _INC_EKU_CONTAINER_FLLIST
//Forward-only Linked list class
//Use std::forward_list if C++11 is available
//needs review

#include<eku\miscdef.h>

template<class typ>
class node
{public:
	typ data;
	node* next;
	node(node* nxt=NULL):next(nxt){}
	node(const typ& obj,node* nxt=NULL):next(nxt),data(obj){}
	void removeall()
	{if(next!=NULL){delete next;next=NULL;}}
	~node(){removeall();}

	void addnextnode(){next=new node<typ>;}
	void addnextnode(const typ& obj){next=new node<typ>;next->data=obj;}
	void addnextnode(const node& nd){next=&nd;}

	void insaft(node* np)
	{np->next=next;next=np;}
	void insaft(const typ& obj)
	{node* np=new node;np->data=obj;insaft(np);}
};

//--------------------------------------------------------------------------------------

template<class typ>
inline void join(const node<typ>& n1,const node<typ>& n2)
{n1.next=&n2;}

//======================================================================================

template<class typ>
class liter
{
public:
	node<typ>* ptr;
	int pos;
	liter(node<typ>* nd,int initpos=0):ptr(nd),pos(initpos){}
	liter(int initpos=0):ptr(new node<typ>),pos(initpos){}

	bool nonext(){return (ptr->next==NULL);}
	
	void gotoend(){while(!nonext())operator++();}

//node addition
	void addnextnode(){ptr->addnextnode();}
	void addnextnode(const typ& obj){ptr->addnextnode(obj);}
	void addnextnode(const node<typ>& nd){ptr->addnextnode(nd);}

//Input
	void get(typ* a,int n);

//increment-decrement
	liter operator++(){ptr=ptr->next;++pos;return *this;}
	liter operator++(int){liter l(ptr,pos);ptr=ptr->next;++pos;return l;}

//assignment
	void operator=(int a){pos=a;}
	void operator=(const node<typ>& nd){ptr=&nd;}
	void operator=(node<typ>* pnd){ptr=pnd;}
	void operator=(liter lit){pos=lit.pos;ptr=lit.ptr;}

//dereference
	typ& operator*(){return ptr->data;}
	typ& operator[](int n)
	{
		if(n>=0)return operator+(n).ptr->data;
	}

//increment/decrement
	liter operator+(int n)
	{liter p(ptr,pos);int i;for(i=0;i<n;i++)++p;return p;}
	void operator+=(int n)
	{int i;for(i=0;i<n;i++)operator++();}
	int operator-(const liter& it){return pos-it.pos;}

//comparison
	bool operator==(liter& a){return (ptr==a.ptr && pos==a.pos);}
	bool operator!=(liter& a){return !operator==(a);}

	bool operator<(liter& it){return pos<it.pos;}
	bool operator<=(liter& it){return pos<=it.pos;}
	bool operator>(liter& it){return pos>it.pos;}
	bool operator>=(liter& it){return pos>=it.pos;}
	
//deletion
	void erasenext(){ptr->next->erase();}
	
//insertion
	void insaft(node<typ>* np){ptr->insaft(np);}
	void insaft(const typ& obj){ptr->insaft(obj);}
};

//--------------------------------------------------------------------------------------

template<class typ>
void liter<typ>::get(typ* a,int n)
{
	int i;
	liter p(ptr,pos);
	*p=a[0];
	for(i=1;i<n;i++)
	{
		if(p.nonext())p.addnextnode();
		*++p=a[i];
	}
}

template<class typ>
STD(ostream&) operator<<(STD(ostream&) os,liter<typ>& lt)
{
	liter<typ> p(lt.ptr,lt.pos);
	while(!p.nonext())os<<(*p++)<<'\n';
	os<<(*p)<<'\n';
	return os;
}

template<class typ>
STD(istream&) operator>>(STD(istream&) is,liter<typ>& lt)
{
	liter<typ> p(lt);
	int i,n;
	cout<<"Enter no. of values ";
	is>>n;
	cout<<"Enter 1st value ";
	is>>(*p);
	for(i=1;i<n;i++)
	{
		if(p.nonext()){p.addnextnode();}
		cout<<"Enter "<<i+1<<"th value ";
		is>>(*++p);
	}
	return is;
}

template<class typ>
inline void erase(liter<typ>& l1,liter<typ>& l2)
{erase(*(l1.ptr),*(l2.ptr));}

template<class typ>
node<typ>* reverse(node<typ>* pbegnd)
{
	node<typ> *p0,*p1=NULL,*p2=pbegnd;
	while(p2!=NULL)
	{
		p0=p1;
		p1=p2;
		p2=p2->next;
		p1->next=p0;
	}
	return p1;
}
	

#endif	//_INC_EKU_CONTAINER_FLLIST