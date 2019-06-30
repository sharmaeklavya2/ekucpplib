#ifndef _INC_EKU_EXPREVAL_EXPREVAL
#define _INC_EKU_EXPREVAL_EXPREVAL
//Contains functions used by expreval.h for formatting the inputted string and evaluating it

inline void putmultiply(std::string& a)
//puts a '*' sign between brackets
//eg. "(a+b)(c+d)" is converted to "(a+b)*(c+d)"
{
	unsigned i;
	for(i=0;i<a.size();i++)
		if(a[i]==')' && a[i+1]=='(')a.insert(i+1,1,'*');
}

inline bool isdelim(char ch)
{
	unsigned i;
	for(i=0;delim[i]!=0;i++)if(ch==delim[i])return true;
	return false;
}

inline bool isbindelimop(char ch)
{int i;for(i=0;bindelimop[i]!=0;i++){if(ch==bindelimop[i])return true;}return false;}

inline bool isundelimop(char ch)
{int i;for(i=0;undelimop[i]!=0;i++){if(ch==undelimop[i])return true;}return false;}

inline bool isillchar(char ch)
{int i;for(i=0;illchar[i]!=0;i++){if(ch==illchar[i])return true;}return false;}

inline bool hasillchar(std::string& a)
{int i,n=a.size();for(i=0;i<n;i++){if(isillchar(a[i]))return true;}return false;}

//------------------------------------------------------------------------------------

int bracmatch(std::string& a,int pos)
{
	bool fwd;
	if(a[pos]!='(')fwd=true;
	else if(a[pos]!=')')fwd=false;
	else return -1;
	int level=1,i,n=a.size(),pos2=-1;
	if(fwd)for(i=pos+1;i<n;i++)
	{
		if(a[i]=='(')level++;
		else if(a[i]==')')level--;
		if(level==0){pos2=i;break;}
	}
	else for(i=pos-1;i>=0;i--)
	{
		if(a[i]=='(')level++;
		else if(a[i]==')')level--;
		if(level==0){pos2=i;break;}
	}
	return pos2;
}

bool braccorr(std::string& a)
//are brackets correctly matched
{
	int i,level=0,n=a.size();
	for(i=0;i<n;i++)
	{
		if(a[i]=='(')level++;
		else if(a[i]==')')
		{
			level--;
			if(isalnum(a[i+1]))return false;
		}
		if(level<0)return false;
	}
	if(level>0)return false;
	else return true;
}

void bracconv(std::string& a)
//converts '[' and '{' to '(' and converts ']' and '}' to ')'
{
	int i,n=a.size();
	for(i=0;i<n;i++)
	{
		if(a[i]=='[' || a[i]=='{')a[i]='(';
		else if(a[i]==']' || a[i]=='}')a[i]=')';
	}
}

void delchar(std::string& a,char ch)
//delete all occurences of ch
{
	std::string b;
	b.reserve(a.size());
	int i,n=a.size();
	for(i=0;i<n;i++)if(a[i]!=ch)b.insert(b.end(),a[i]);
	a=b;
}

//------------------------------------------------------------------------------------

void format(std::string& a)
//seperates parts of the expression and gives them a header
//parts of an expression are constants('#'), variables('$'), functions('0'+n), and operators('0'+n)
//here n is the no. of arguments the function or operator expects
{
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

void unpre_to_unpost(std::string& a)
//converts pre-unary operators to post-unary operators
//not used in the function eval()
{
	int oldpos,newpos=-1,i;
	std::vector<cstr_wrap>	stack;
	for(i=1;i<int(a.size());i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		if(a[oldpos+1]>='1' && a[oldpos+1]<='9')
		{
			stack.push_back(cstr_wrap(a.substr(oldpos+1,newpos-oldpos)));
			if(a[oldpos+1]=='1'){a.erase(oldpos+1,newpos-oldpos);newpos=oldpos;i=oldpos;}
		}
		else if(a[newpos-1]=='('){stack.push_back(cstr_wrap("("));}
		else if(a[newpos-1]==')' && stack.size()>=2)
		{
			stack.pop_back();
			if(stack.back()[0]=='1')
			{
				a.insert(newpos+1,stack.back().a);
				i+=strlen(stack.back().a);
				oldpos=newpos;newpos=i;
				stack.pop_back();
			}
		}
	}
}

void binpre_to_binin(std::string& a)
//converts binary functions to binary infix operators
//not used in the function eval()
{
	int oldpos,newpos=-1,i;
	std::vector<cstr_wrap>	stack;
	for(i=1;i<int(a.size());i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		if(a[oldpos+1]=='2')
		{
			stack.push_back(cstr_wrap(a.substr(oldpos+1,newpos-oldpos)));
			a.erase(oldpos+1,newpos-oldpos);newpos=oldpos;i=oldpos;
		}
		else if(a[newpos-1]==',' && !stack.empty())
		{
			a.erase(newpos-1,1);
			a.insert(newpos-1,"):(");
			a.insert(newpos+1,stack.back().a);
			i+=strlen(stack.back().a)+2;
			oldpos=newpos;newpos=i;
			stack.pop_back();
		}
	}
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

inline void putmultiply2(std::string& a)
//puts a '*' sign between number and variable
//e.g. converts "#23ab:" to "#23:2*:$ab;"
//Hence, input of 23ab is interpreted as 23*ab
{
	int i,j,oldpos,newpos=-1;
	for(i=0;i<int(a.size());i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		if(a[oldpos+1]!='#')continue;
		for(j=oldpos+3;j<newpos;j++)if(isalpha(a[j]))
		{a.insert(j,":2*:$");break;}
	}
}

void putmultiply3(std::string& a)
//puts a '*' sign between a number and a function
//e.g. "123ab:(:4:):" is converted to "#23:2*:1ab:(:4:):"
//Hence, 23ab(4) is interpreted as 23*ab(4)
{
	int i,j,oldpos,newpos=-1;char fntype;
	for(i=0;i<int(a.size());i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		fntype=a[oldpos+1];
		if((fntype!='1' && fntype!='2') || !isdigit(a[oldpos+2]))continue;
		a[oldpos+1]='#';
		for(j=oldpos+3;j<newpos;j++)if(isalpha(a[j]))
		{
			a.insert(j,":2*:");j+=4;
			a.insert(j,1,fntype);
			goto A;
		}
		a.insert(newpos,":2*");
A:		i=i;	//dummy for goto
	}
}

inline void func_to_op(std::string& a)
//converts f(x,y,z) to f(x)(y)(z)
{
	int i,n=a.size();
	for(i=0;i<n;i++)if(a[i]==',')
	{a.erase(i,1);a.insert(i,"):(");}
}

template<class dtyp>
int priority(const char* str)
{
	char a[OP_NAME_SIZE];
	int i,n;
	strcpy(a,str);
	bool bin=true,un=true;
	if(a[strlen(a)-1]==f2sc)a[strlen(a)-1]='\0';
	if(a[0]=='1' || a[0]=='2')
	{
		if(a[0]!='1')un=false;
		if(a[0]!='2')bin=false;
		strcpy(a,a+1);
	}
	if(un){n=varop<dtyp>::op1.size();for(i=0;i<n;i++)if(strcmp(varop<dtyp>::op1[i].name,a)==0)return varop<dtyp>::op1[i].pr;}
	if(bin){n=varop<dtyp>::op2.size();for(i=0;i<n;i++)if(strcmp(varop<dtyp>::op2[i].name,a)==0)return varop<dtyp>::op2[i].pr;}
	strcpy(unknown_func_name,a);throw unknown_func;
}

template<class dtyp>
void infix_to_postfix(std::string& in,std::string& out)
{
	int oldpos,newpos=-1,i;
	out.erase();
	std::vector<cstr_wrap>	stack;
	char ch;std::string b;
	for(i=1;i<int(in.size());i++)if(in[i]==f2sc)
	{
		oldpos=newpos;newpos=i;ch=in[oldpos+1];
		if(ch=='#' || ch=='$')out.append(in.substr(oldpos+1,newpos-oldpos));
		else if(ch=='(')stack.push_back(cstr_wrap("(:"));
		else if(ch==')')
		{
			while(stack.back()!="(:"){out.append(stack.back().a);stack.pop_back();}
			stack.pop_back();
		}
		else if(stack.empty())stack.push_back(in.substr(oldpos+1,newpos-oldpos));
		else
		{
			b.assign(in,oldpos+1,newpos-oldpos);
			while(!stack.empty() && stack.back()!="(:" && priority<dtyp>(stack.back().a)>=priority<dtyp>(b.c_str()))
			{out.append(stack.back().a);stack.pop_back();}
			stack.push_back(b);
		}
	}
	while(!stack.empty()){out.append(stack.back().a);stack.pop_back();}
}

template<class dtyp>
dtyp askvar(char* a,std::vector<variable<dtyp> >& var)
{
	int i,n=var.size();
	for(i=0;i<n;i++)if(var[i]==a)return var[i].val;
	var.push_back(variable<dtyp>(a));
	STD(cout)<<"Enter "<<var[i].name<<": ";
	if(expreval_mode::recursive_eval)
	{
		std::string a;
		if(STD(cin).peek()=='\n')STD(cin).ignore();
		STD(getline)(STD(cin),a);
		var[i].val=evaluate<dtyp>(a);
	}
	else STD(cin)>>var[i].val;
	return var[i].val;
}

//template<class dtyp,int n>
//inline dtyp call(char* a){}
template<class dtyp>
inline dtyp call1(char* a,dtyp b)
{
	int i,n=varop<dtyp>::op1.size();
	for(i=0;i<n;i++)if(varop<dtyp>::op1[i]==a)
	{
		if(!varop<dtyp>::op1[i].is_valid_arg(b))throw bad_arg;
		return varop<dtyp>::op1[i].call(b);
	}
	strcpy(unknown_func_name,a);throw unknown_func;
}

template<class dtyp>
inline dtyp call2(char* a,dtyp b,dtyp c)
{
	int i,n=varop<dtyp>::op2.size();
	for(i=0;i<n;i++)if(varop<dtyp>::op2[i]==a)
	{
		if(!varop<dtyp>::op2[i].is_valid_arg(b,c))throw bad_arg;
		return varop<dtyp>::op2[i].call(b,c);
	}
	strcpy(unknown_func_name,a);throw unknown_func;
}

template<class dtyp>
inline dtyp call3(char* a,dtyp b,dtyp c,dtyp d)
{
	int i,n=varop<dtyp>::op3.size();
	for(i=0;i<n;i++)if(varop<dtyp>::op3[i]==a)
	{
		if(!varop<dtyp>::op3[i].is_valid_arg(b,c,d))throw bad_arg;
		return varop<dtyp>::op3[i].call(b,c,d);
	}
	strcpy(unknown_func_name,a);throw unknown_func;
}

template<class dtyp>
dtyp eval(std::string& a,std::vector<variable<dtyp> >& var,std::vector<dtyp>& stack)
{
	int i,n=a.size(),oldpos,newpos=-1;
	char ch,buff[50];
	dtyp arg2,arg3;
	for(i=1;i<n;i++)if(a[i]==f2sc)
	{
		oldpos=newpos;newpos=i;
		ch=a[oldpos+1];
		strcpy(buff,a.substr(oldpos+2,newpos-oldpos-2).c_str());
		if(ch=='#')stack.push_back(expreval_conv<dtyp>(buff));
		else if(ch=='$')stack.push_back(askvar(buff,var));
		else if(ch=='1')stack.back()=call1(buff,stack.back());
		else if(ch=='2')
		{
			arg2=stack.back();
			stack.pop_back();
			stack.back()=call2<dtyp>(buff,stack.back(),arg2);
		}
		else if(ch=='3')
		{
			arg3=stack.back();
			stack.pop_back();
			arg2=stack.back();
			stack.pop_back();
			stack.back()=call3<dtyp>(buff,stack.back(),arg2,arg3);
		}
	}
	if(stack.empty())return 0;else return stack.back();
}

template<class dtyp>
inline dtyp eval(std::string& a,std::vector<variable<dtyp> >& var)
{std::vector<dtyp> stack;return eval(a,var,stack);}

template<class dtyp>
bool ready(std::string& a)
{
	delchar(a,' ');
	putmultiply(a);
	if(hasillchar(a))
	{
#if defined(_IOSTREAM_) || defined(_INC_OSTREAM)
		STD(cout)<<"Illegal characters in expression"<<STD(endl);
#endif
	}
	bracconv(a);
	if(!braccorr(a))
	{
#if defined(_IOSTREAM_) || defined(_INC_OSTREAM)
		STD(cout)<<"Incorrect bracket placement"<<STD(endl);
#endif
		return false;
	}
	format(a);
	unplusminus(a);
//	binpre_to_binin(a);
	func_to_op(a);
	format2(a);
	putmultiply2(a);
	putmultiply3(a);
	if(!math_mode<dtyp>::func_loaded){load_func<dtyp>();math_mode<dtyp>::func_loaded=true;}
	std::string b;
	infix_to_postfix<dtyp>(a,b);
	a=b;
	return true;
}

template<>
bool ready<bool>(std::string& a)
{
	delchar(a,' ');
	putmultiply(a);
	if(hasillchar(a))
	{
#if defined(_IOSTREAM_) || defined(_INC_OSTREAM)
		STD(cout)<<"Illegal characters in expression"<<STD(endl);
#endif
	}
	bracconv(a);
	if(!braccorr(a))
	{
#if defined(_IOSTREAM_) || defined(_INC_OSTREAM)
		STD(cout)<<"Incorrect bracket placement"<<STD(endl);
#endif
		return false;
	}
	format(a);
	unplusminus(a);
	binpre_to_binin(a);
	format2(a);
	putmultiply2(a);
	putmultiply3(a);
	boolconst(a);
	if(!math_mode<bool>::func_loaded){load_func<bool>();math_mode<bool>::func_loaded=true;}
	std::string b;
	infix_to_postfix<bool>(a,b);
	a=b;
	return true;
}


#endif	//_INC_EKU_EXPREVAL_EXPREVAL