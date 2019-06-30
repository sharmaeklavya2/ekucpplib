#ifndef _INC_EKU_WINDOWS_UICLASS_LISTBOX
#define _INC_EKU_WINDOWS_UICLASS_LISTBOX

/*This header file contains a listbox classes
The container uses the windows control 'listbox' as its underlying container
The functionality of the container is similar to std::vector<std::string>

The following features of vector will be implemented:
	constuctor
Non-modyfying:
	int size()						LB_GETCOUNT
	bool empty()					LB_GETCOUNT
	void reserve()					LB_INITSTORAGE
	void get_string(string&,int)	LB_GETTEXT
	void front(string&)				get_string
	void back(string&)				get_string
Modyfying:
	assign(HWND)
	push_back(string&)				LB_ADDSTRING
	pop_back()						LB_DELETESTRING
	insert(int pos,string&)			LB_INSERTSTRING
	insert(int pos,HWND)			
	insert(int pos,InputIterator first,InputIterator last)
	erase(int pos)					LB_DELETESTRING
	erase(int first,int beyond_last)	LB_DELETESTRING
	clear()							LB_RESETCONTENT

These extra features will also be implemented:
	int find()					LB_FINDSTRINGEXACT
	int find_same_starting()	LB_FINDSTRING
	bool is_selected()			LB_GETSEL
	int str_len(int)			LB_GETTEXTLEN		//gets length of string at given index
	int get_top_index()			LB_GETTOPINDEX
	int set_top_index()			LB_SETTOPINDEX
	bool get_from_file(const TCHAR* fname)const;
	bool put_to_file(const TCHAR* fname)const;

Features in single-selection list boxes only:
	int get_sel_index()				LB_GETCURSEL		//gets current index
	void set_sel_index(int)			LB_SETCURSEL

Features in multiple-selection list boxes only:
	int get_anchor_index()		LB_GETANCHORINDEX	//get index of first selected item
	int get_focus_index()		LB_GETCARETINDEX	//gets index of with a focus rectangle
	void set_focus_index()		LB_SETCARETINDEX
	int get_sel_count()			LB_GETSELCOUNT		//gets no. of selected items
	int* get_sel_indices()		LB_GETSELITEMS
	void set_index(int)			LB_SETSEL

*/

#include<eku\windows\no_windows_error.h>
#include<string>
#include<vector>
#include<iterator>
#include<fstream>
#include<eku\tchar\tstring.h>
#include<eku\tchar\tiostream.h>

namespace eku
{
	class clistbox
	//Common listbox class
	//Contains functions common to both single-selection and multiple-selection listboxs
	{
	protected:
		HWND hList;
	public:
		clistbox(HWND hlist=NULL):hList(hlist){}
		HWND get_handle()const{return hList;}
		void set_handle(HWND hlist){hList=hlist;}

		class const_iterator;
		class iterator;
		class dummy_element;
		inline const_iterator cbegin()const;
		inline const_iterator cend()const;

		int size()const
		{return SendMessage(hList,LB_GETCOUNT,0,0);}
		bool empty()const
		{return size()==0;}
		void reserve(int)const;
		//There is some ambigiguity regarding LB_INITSTORAGE's wParam and lParam
		//Hence there is no implementation of this function yet.
		void get_string(eku::tstring& str,int index)const;
		void front(eku::tstring& str)const
		{get_string(str,0);}
		void back(eku::tstring& str)const
		{get_string(str,size()-1);}

		void assign(HWND hlist)const;
		//Copies content from another listbox
		//NO implememtation
		void push_back(const TCHAR* str)const
		{SendMessage(hList,LB_ADDSTRING,0,(LPARAM)str);}
		void pop_back()const
		{SendMessage(hList,LB_DELETESTRING,size()-1,0);}
		void pop_front()const
		{SendMessage(hList,LB_DELETESTRING,0,0);}
		void insert(int pos,const TCHAR* str)const
		{SendMessage(hList,LB_INSERTSTRING,pos,(LPARAM)str);}
		void insert(int pos,HWND hlist)const;
		//NO implementation
		template<class InputIterator>
		void insert(int pos,InputIterator first,InputIterator last)const;
		//NO implementation
		void erase(int pos)const
		{SendMessage(hList,LB_DELETESTRING,pos,0);}
		void erase(int first,int beyond_last)const
		{for(int pos=first;pos!=beyond_last;pos++)erase(pos);}
		void clear()const
		{SendMessage(hList,LB_RESETCONTENT,0,0);}
		int find(const TCHAR* str)const
		{return SendMessage(hList,LB_FINDSTRINGEXACT,-1,(LPARAM)str);}
		int find_same_starting(const TCHAR* str)const
		{return SendMessage(hList,LB_FINDSTRING,-1,(LPARAM)str);}
		bool is_selected(int index)const
		{return bool(SendMessage(hList,LB_GETSEL,index,0));}
		int str_len(int index)const
		{return SendMessage(hList,LB_GETTEXTLEN,index,0);}
		int get_top_index()const
		{return SendMessage(hList,LB_GETTOPINDEX,0,0);}
		void set_top_index(int index)const
		{SendMessage(hList,LB_SETTOPINDEX,index,0);}

		bool get_from_file(const TCHAR* fname)const;
		bool put_to_file(const TCHAR* fname)const;
	};

	void clistbox::get_string(eku::tstring& str,int index)const
	{
		int size;
		TCHAR* buf;
		size=SendMessage(hList,LB_GETTEXTLEN,index,0)+1;
		if(size<=0)return;
		buf=new TCHAR[size];
		SendMessage(hList,LB_GETTEXT,index,(LPARAM)buf);
		str=buf;
		delete[] buf;
	}

	bool clistbox::get_from_file(const TCHAR* fname)const
	{
		eku::tifstream ifile(fname);
		eku::tstring str;
		if(!ifile.is_open())return false;
		while(std::getline(ifile,str))
		{push_back(str.c_str());}
		ifile.close();
		return true;
	}

	bool clistbox::put_to_file(const TCHAR* fname)const
	{
		eku::tofstream ofile(fname);
		eku::tstring str;
		int i,s=size();
		if(!ofile.is_open())return false;
		for(i=0;i<s;++i)
		{get_string(str,i);ofile<<str<<'\n';}
		ofile.close();
		return true;
	}

	class slistbox:public clistbox
	{
		slistbox(HWND hlist=NULL):clistbox(hlist){}
		int get_sel_index()const
		{return SendMessage(hList,LB_GETCURSEL,0,0);}
		void set_sel_index(int index)const
		{SendMessage(hList,LB_SETCURSEL,index,0);}
	};

	class mlistbox:public clistbox
	{
		mlistbox(HWND hlist=NULL):clistbox(hlist){}
		int get_anchor_index()const
		//get index of first selected item
		{return SendMessage(hList,LB_GETANCHORINDEX,0,0);}
		int get_focus_index()const
		{return SendMessage(hList,LB_GETCARETINDEX,0,0);}
		//gets index of string with a focus rectangle
		void set_focus_index(int index)const
		{SendMessage(hList,LB_SETCARETINDEX,index,0);}
		int get_sel_size()const
		{return SendMessage(hList,LB_GETSELCOUNT,0,0);}
		//gets no. of selected items
		int get_sel_indices(int* buffer,int buff_size)const
		//gets storage indices and stores them in buffer
		//buffer should be long enough to store
		//returns number of items stored in the buffer
		{return SendMessage(hList,LB_GETSELITEMS,buff_size,(LPARAM)buffer);}
		int get_sel_indices(int* buffer)const
		{return SendMessage(hList,LB_GETSELITEMS,get_sel_size(),(LPARAM)buffer);}
		int get_sel_indices(std::vector<int>& buffer,int buff_size)const;
		//gets storage indices and stores them in buffer
		int get_sel_indices(std::vector<int>& buffer)const
		{
			buffer.resize(get_sel_size());
			return SendMessage(hList,LB_GETSELITEMS,buffer.size(),(LPARAM)&buffer[0]);
		}
		void set_sel(int index,bool value)const
		{SendMessage(hList,LB_SETSEL,(WPARAM)value,(LPARAM)index);}
		void set_sel_all(bool value)const
		{SendMessage(hList,LB_SETSEL,(WPARAM)value,(LPARAM)(-1));}
		void invert_sel(int index)const
		{SendMessage(hList,LB_SETSEL,SendMessage(hList,LB_GETSEL,index,0),(LPARAM)index);}
		void invert_sel_all()const
		{
			int i,_size=get_sel_size();
			for(i=0;i<_size;i++)invert_sel(i);
		}
	};
	
	int mlistbox::get_sel_indices(std::vector<int>& buffer,int buff_size)const
	{
		int actual_size,sel_count;
		sel_count=get_sel_size();
		actual_size=(buff_size<sel_count)?buff_size:sel_count;
		buffer.resize(actual_size);
		return SendMessage(hList,LB_GETSELITEMS,buff_size,(LPARAM)&buffer[0]);
	}

	class clistbox::dummy_element
	{
	protected:
		HWND hList;
		int index;
	public:
		dummy_element(HWND hlist=NULL,int pos=0):hList(hlist),index(pos){}
		dummy_element(const dummy_element& it):hList(it.hList),index(it.index){}

		template<class typ>
		void operator=(const typ& obj)
		{
			eku::tstring str;
			clistbox lb(hList);
			lb.erase(index);
			str=obj;
			lb.insert(index,str.c_str());
		}

		operator eku::tstring()
		{
			eku::tstring str;
			clistbox(hList).get_string(str,index);
			return str;
		}
	};

	class clistbox::const_iterator:public std::iterator<std::input_iterator_tag,int>
	{
		typedef const_iterator iter;
	protected:
		HWND hList;
		int index;
	public:
		iter(HWND hlist=NULL,int pos=0):hList(hlist),index(pos){}
		iter(const iter& it):hList(it.hList),index(it.index){}

		iter operator++(){++index;return *this;}
		iter operator--(){--index;return *this;}
		iter operator++(int){iter it(*this);++index;return it;}
		iter operator--(int){iter it(*this);--index;return it;}
		
		bool operator==(const iter& it)const{return (hList==it.hList && index==it.index);}
		bool operator!=(const iter& it)const{return !operator==(it);}

		clistbox operator->()const{return clistbox(hList);}
		eku::tstring operator*()const
		{
			eku::tstring str;
			clistbox(hList).get_string(str,index);
			return str;
		}

		bool operator<(const iter& it)const{return index<it.index;}
		bool operator<=(const iter& it)const{return index<=it.index;}
		bool operator>(const iter& it)const{return index>it.index;}
		bool operator>=(const iter& it)const{return index>=it.index;}

		iter operator+(int n){return iter(hList,index+n);}
		void operator+=(int n){index+=n;}
		iter operator-(int n){return iter(hList,index-n);}
		void operator-=(int n){index-=n;}
		int operator-(const iter& it){return index-it.index;}
	};

	class clistbox::iterator:public clistbox::const_iterator,
		public std::iterator<std::random_access_iterator_tag,int>
	{
	public:
		iterator(HWND hlist=NULL,int pos=0):clistbox::const_iterator(hlist,pos){}
		iterator(const clistbox::const_iterator& it):clistbox::const_iterator(it){}
		iterator(const iterator& it):clistbox::const_iterator(it.hList,it.index){}

		clistbox::dummy_element operator*();
	};

	inline clistbox::const_iterator clistbox::cbegin()const{return const_iterator(hList,0);}
	inline clistbox::const_iterator clistbox::cend()const{return const_iterator(hList,size());}

}

#endif	//_INC_EKU_WINDOWS_UICLASS_LISTBOX