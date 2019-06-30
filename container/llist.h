#ifndef _INC_EKU_CONTAINER_LLIST
#define _INC_EKU_CONTAINER_LLIST
//Linked list class
//Use std::list instead
//needs review

#include<eku\miscdef.h>

template<class typ>
class node
{public:
	typ data;
	node* next;
	node* prev;
	node(node* nxt=NULL,node* prv=NULL):next(nxt),prev(prv){}
	node(const typ& obj,node* nxt=NULL,node* prv=NULL):next(nxt),prev(prv),data(obj){}
	void removeall()
	{
		if(next!=NULL){next->prev=NULL;delete next;next=NULL;}
		if(prev!=NULL){prev->next=NULL;delete prev;prev=NULL;}
	}
	~node(){removeall();}

	void addnextnode(){next=new node<typ>;next->prev=this;}
	void addprevnode(){prev=new node<typ>;prev->next=this;}
	void addnextnode(const typ& obj){next=new node<typ>;next->prev=this;next->data=obj;}
	void addprevnode(const typ& obj){prev=new node<typ>;prev->next=this;prev->data=obj;}
	void addnextnode(const node& nd){next=&nd;next->prev=this;}
	void addprevnode(const node& nd){prev=&nd;prev->next=this;}

	void erase()
	{
		if(prev!=NULL)prev->next=next;
		if(next!=NULL)next->prev=prev;
		next=NULL;prev=NULL;
		delete this;
	}

	void insaft(node* np)
	{np->next=next;np->prev=this;if(next!=NULL)next->prev=np;next=np;}
	void insaft(const typ& obj)
	{node* np=new node;np->data=obj;insaft(np);}
	void insbef(node* np)
	{np->prev=prev;np->next=this;if(prev!=NULL)prev->next=np;prev=np;}
	void insbef(const typ& obj)
	{node* np=new node;np->data=obj;insbef(np);}
};

//--------------------------------------------------------------------------------------

template<class typ>
inline void join(const node<typ>& n1,const node<typ>& n2)
{n1.next=&n2;n2.back=&n1;}

template<class typ>
void erase(node<typ>& n1,node<typ>& n2)
{
	if(n1.prev!=NULL)n1.prev->next=n2.next;
	if(n2.next!=NULL)n2.next->prev=n1.prev;
	n1.prev=NULL;n2.next=NULL;
	n1.removeall();
}

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
	bool noprev(){return (ptr->prev==NULL);}
	
	void gotoend(){while(!nonext())operator++();}
	void gotobeg(){while(!noprev())operator--();}

//node addition
	void addnextnode(){ptr->addnextnode();}
	void addprevnode(){ptr->addprevnode();}
	void addnextnode(const typ& obj){ptr->addnextnode(obj);}
	void addprevnode(const typ& obj){ptr->addnextnode(obj);}
	void addnextnode(const node<typ>& nd){ptr->addnextnode(nd);}
	void addprevnode(const node<typ>& nd){ptr->addnextnode(nd);}

//Input
	void get(typ* a,int n);

//increment-decrement
	liter operator++(){ptr=ptr->next;++pos;return *this;}
	liter operator++(int){liter l(ptr,pos);ptr=ptr->next;++pos;return l;}
	liter operator--(){ptr=ptr->prev;--pos;return *this;}
	liter operator--(int){liter l(ptr,pos);--pos;ptr=ptr->prev;return l;}

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
		else return operator-(-n).ptr->data;
	}
//increment/decrement
	liter operator+(int n)
	{liter p(ptr,pos);int i;for(i=0;i<n;i++)++p;return p;}
	void operator+=(int n)
	{int i;for(i=0;i<n;i++)operator++();}
	liter operator-(int n)
	{liter p(ptr,pos);int i;for(i=0;i<n;i++)--p;return p;}
	void operator-=(int n)
	{
		int i;
		for(i=0;i<n;i++)
		{operator--();}
	}
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
	void eraseprev(){ptr->prev->erase();}
	void erase(){ptr=ptr->next;eraseprev();}

//insertion
	void insaft(node<typ>* np){ptr->insaft(np);}
	void insaft(const typ& obj){ptr->insaft(obj);}
	void insbef(node<typ>* np){ptr->insbef(np);}
	void insbef(const typ& obj){ptr->insbef(obj);}
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

#endif	//_INC_EKU_CONTAINER_LLIST