#ifndef _INC_EKU_EXPREVAL
#define _INC_EKU_EXPREVAL

#include<string>
#include<boost\variant.hpp>

//namespace eku
//{

typedef int typ;
typedef typ functyp0();
typedef typ functyp1(typ);
typedef typ functyp2(typ,typ);
typedef typ functyp3(typ,typ,typ);
typedef boost::variant<typ,functyp0,functyp1,functyp2,functyp3> elem;

char delim[]="+-*()/%&|^,!;=";	//(delimiters) seperators in an expression
char bindelimop[]="+-*/%&|^";	//binary delimiting operators
char undelimop[]="+-!";			//unary delimiting operators
char illchar[]="\"#$\':<>?@\\`~";	//illegal characters
	
inline bool isdelim(char ch)
{
	unsigned i;
	for(i=0;delim[i]!=0;i++)if(ch==delim[i])return true;
	return false;
}

void format(std::string& a)
//seperates parts of the expression and gives them a header
//parts of an expression are constants('#'), variables('$'), functions('0'+n), and operators('0'+n)
//here n is the no. of arguments the function or operator expects
{
	const char f2sc=':';
	int olddelimpos,newdelimpos=-2,i;
	for(i=0;i<int(a.size());i++)if(isdelim(a[i]))
	{
		olddelimpos=newdelimpos;
		newdelimpos=i;
		a.insert(newdelimpos+1,1,f2sc);
		if(newdelimpos-olddelimpos==2)i+=1;
		else
		{
			a.insert(newdelimpos,1,f2sc);
			newdelimpos+=1;i+=1;
			if(a[newdelimpos]!='(')
			{
				if(isdigit(a[olddelimpos+2]))a.insert(olddelimpos+2,1,'#');
				else a.insert(olddelimpos+2,1,'$');
				i++;newdelimpos++;
			}
			else
			{
				int level=1,j=newdelimpos+2,count=0;
				for(;j<int(a.size());j++)
				{
					if(a[j]=='(')level++;
					else if(a[j]==')')level--;
					if(level==0)break;
					if(level==1 && a[j]==',')count++;
				}
				a.insert(olddelimpos+2,1,'1'+count);
				newdelimpos++;i++;
			}
		}
	}
	if(a[a.size()-1]==f2sc)return;
	olddelimpos=newdelimpos;newdelimpos=i;
	if(isdigit(a[olddelimpos+2]))a.insert(olddelimpos+2,1,'#');
	else a.insert(olddelimpos+2,1,'$');
	a.insert(a.end(),f2sc);
}

void unplusminus(std::string& a)
//formats unary '+' and '-'
{
	int oldpos,newpos=-1,i;
	char ch;
	if(a[0]=='-' || a[0]=='+'){a.insert(0,"1");}
	for(i=1;i<int(a.size())-1;i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		ch=a[oldpos+1];
		if((a[newpos+1]=='-' || a[newpos+1]=='+') && ch!=')' && ch!='#' && ch!='$' )
		{a.insert(newpos+1,1,'1');}
	}
}

void format2(std::string& a)
{
	int i;
	if(isundelimop(a[0]) && a[0]!='+' && a[0]!='-')a.insert(0,"1");
	else if(isbindelimop(a[0]))a.insert(0,"2");
	for(i=1;i<int(a.size());i++)if(a[i]==f2sc)
	{
		if(isundelimop(a[i+1]) && a[i+1]!='+' && a[i+1]!='-'){a.insert(i+1,1,'1');i++;}
		else if(isbindelimop(a[i+1])){a.insert(i+1,1,'2');i++;}
	}
}

void boolconst(std::string& a)
{
	int i,oldpos,newpos=-1;
	std::string b;
	for(i=0;i<int(a.size());i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		b=a.substr(oldpos+2,newpos-oldpos-2);
		if(b=="true" || b=="false")a[oldpos+1]='#';
	}
}

//}	//end of namespace eku

#endif	//_INC_EKU_EXPREVAL