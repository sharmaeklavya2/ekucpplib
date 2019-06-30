#ifndef _INC_EKU_WINDOWS_UICLASS_TREE
#define _INC_EKU_WINDOWS_UICLASS_TREE

#ifndef _INC_COMMCTRL
#error "commctrl.h not included"
#else	//_INC_COMMCTRL
#pragma comment(lib,"comctl32.lib")
#endif	//_INC_COMMCTRL

#include<cstring>
#include<string>
#include<stack>
#include<fstream>

namespace eku
{
	HTREEITEM insert_into_tree(HWND tvwnd,HTREEITEM hparent,char* str,int size,HTREEITEM hinsaft=TVI_LAST)
	{
		TVINSERTSTRUCT tvinsstr;
		TVITEM item;
		ZeroMemory(&tvinsstr,sizeof(tvinsstr));

		item.mask=TVIF_TEXT;
		item.cchTextMax=size;
		item.pszText=str;
		
		tvinsstr.hInsertAfter=hinsaft;
		tvinsstr.hParent=hparent;
		tvinsstr.item=item;

		return (HTREEITEM)SendMessageA(tvwnd,TVM_INSERTITEM,0,(LPARAM)(&tvinsstr));
	}

	class node
	{
		HWND hwnd;
		HTREEITEM hitem;
	public:
		node(HWND hWnd,HTREEITEM hTreeItem):hwnd(hWnd),hitem(hTreeItem){}
		HWND get_wnd_ptr()const{return hwnd;}
		HTREEITEM get_node_ptr()const{return hitem;}
		void clear(){SendMessage(hwnd,TVM_DELETEITEM,0,(LPARAM)hitem);}
		node get_first_child()const
		{return node(hwnd,(HTREEITEM)SendMessage(hwnd,TVM_GETNEXTITEM,TVGN_CHILD,(LPARAM)hitem));}
		node get_next_sibling()const
		{return node(hwnd,(HTREEITEM)SendMessage(hwnd,TVM_GETNEXTITEM,TVGN_NEXT,(LPARAM)hitem));}
		node get_parent()const
		{return node(hwnd,(HTREEITEM)SendMessage(hwnd,TVM_GETNEXTITEM,TVGN_PARENT,(LPARAM)hitem));}
		node insert(char* str)const
		{node(hwnd,insert_into_tree(hwnd,hitem,str,strlen(str)));}
		void get_str(std::string& str)const
		{
			TVITEM tvitem;
			tvitem.hItem=hitem;
			TreeView_GetItem(hwnd,&tvitem);
			str=tvitem.pszText;
		}
	};

	inline unsigned tier(const std::string& str)
	{
		unsigned i;
		for(i=0;i<str.size() && str[i]=='\t';++i);
		return i;
	}

	void set_from_file(HWND hwnd,HTREEITEM hitem,const char* fname)
	{
		std::fstream ifile(fname);
		std::stack<HTREEITEM> st;
		HTREEITEM top;
		std::string str;
		while(std::getline(ifile,str))
		{
			//while(tier(str)<tier(
		}

	}
}	//end of namespace eku

#endif	//_INC_EKU_WINDOWS_UICLASS_TREE