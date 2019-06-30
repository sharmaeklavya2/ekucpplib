#ifndef _INC_EKU_EXPREVAL_APPLY
#define _INC_EKU_EXPREVAL_APPLY
//Uses expreval\expreval.h's functions to make user usable functions

template<class dtyp>
inline dtyp evaluate_loc_var(std::string a)
{std::vector<variable<dtyp> > var;load_var(var);ready<dtyp>(a);return eval(a,var);}

template<class dtyp>
inline dtyp evaluate_glob_var(std::string a)
{
	dtyp v;
	std::vector<variable<dtyp> >& var=varop<dtyp>::gvar;
	if(!math_mode<dtyp>::glob_var_loaded)
	{var.clear();load_var(var);math_mode<dtyp>::glob_var_loaded=true;}
	ready<dtyp>(a);
	v=eval(a,var);
	var[0].val=v;
	return v;
}

template<class dtyp>
inline dtyp evaluate(std::string& a)
{return ((expreval_mode::loc_var)?evaluate_loc_var<dtyp>(a):evaluate_glob_var<dtyp>(a));}

//diffr--------------------------------------------------------------------------------

template<class dtyp>
dtyp diffr_common(std::string& a,dtyp at,char* wrtvar,dtyp dx,std::vector<variable<dtyp> >& var)
{
	std::vector<dtyp> stack;
	dtyp p,q;int pos;bool exists=false;
	ready<dtyp>(a);
	for(i=0;i<int(var.size());i++)if(var[i]==wrtvar){exists=true;pos=i;break;}
	if(!exists){var.push_back(variable<dtyp>(wrtvar,at));pos=var.size()-1;}
	p=eval(a,var,stack);
	var[pos].val+=dx;
	q=eval(a,var,stack);
	if(!exists)var.erase(var.begin()+pos);
	return (q-p)/dx;
}

template<class dtyp>
inline dtyp diffr_loc_var(std::string a,dtyp at,char* wrtvar,dtyp dx)
{
	std::vector<variable<dtyp> > var;
	load_var<dtyp>(var);
	return diffr_common<dtyp>(a,at,wrtvar,dx,var);
}

template<class dtyp>
inline dtyp diffr_glob_var(std::string a,dtyp at,char* wrtvar,dtyp dx)
{
	dtyp v;
	std::vector<variable>& var=varop<dtyp>::gvar;
	if(!math_mode<dtyp>::glob_var_loaded)
	{var.clear();load_var<dtyp>(var);math_mode<dtyp>::glob_var_loaded=true;}
	v=diffr_common<dtyp>(a,at,wrtvar,dx,var);
	var[0].val=0;
	return v;
}

template<class dtyp>
inline dtyp diffr(std::string& a,dtyp at,char* wrtvar,dtyp dx)
{return ((expreval_mode::loc_var)?diffr_loc_var<dtyp>(a,at,wrtvar,dx):diffr_glob_var<dtyp>(a,at,wrtvar,dx));}

//intgr-------------------------------------------------------------------------------

template<class dtyp>
dtyp intgr_common(std::string& a,dtyp from,dtyp to,char* wrtvar,dtyp dx,std::vector<variable<dtyp> >& var)
{
	dtyp s=0,i;int j,pos;bool exists=false;
	std::vector<dtyp> stack;
	stack.reserve(10);
	ready(a);
	for(j=0;j<int(var.size());j++)if(var[j]==wrtvar){exists=true;pos=j;break;}
	if(!exists){var.push_back(variable<dtyp>(wrtvar,from));pos=var.size()-1;}
	for(i=from;i<=to;i+=dx){s+=eval(a,var,stack)*dx;var[pos].val+=dx;}
	if(!exists)var.erase(var.begin()+pos);
	return s;
}

template<class dtyp>
inline dtyp intgr_loc_var(std::string a,dtyp from,dtyp to,char* wrtvar,dtyp dx)
{
	std::vector<variable<dtyp> > var;
	load_var<dtyp>(var);
	return intgr_common<dtyp>(a,from,to,wrtvar,dx,var);
}

template<class dtyp>
inline dtyp intgr_glob_var(std::string a,dtyp from,dtyp to,char* wrtvar,dtyp dx)
{
	std::vector<variable>& var=varop<dtyp>::gvar;
	if(!math_mode<dtyp>::glob_var_loaded)
	{var.clear();load_var<dtyp>(var);math_mode<dtyp>::glob_var_loaded=true;}
	return intgr_common<dtyp>(a,from,to,wrtvar,dx,var);
}

template<class dtyp>
inline dtyp intgr(std::string& a,dtyp from,dtyp to,char* wrtvar,dtyp dx)
{return ((expreval_mode::loc_var)?intgr_loc_var<dtyp>(a,from,to,wrtvar,dx):intgr_glob_var<dtyp>(a,from,to,wrtvar,dx));}

//sigma---------------------------------------------------------------------------------

template<class dtyp>
dtyp sigma_common(std::string& a,int from,int to,char* wrtvar,std::vector<variable<dtyp> >& var)
{
	dtyp s=0;int i,j,pos;bool exists=false;
	std::vector<dtyp> stack;
	stack.reserve(10);
	ready<dtyp>(a);
	for(j=0;j<int(var.size());j++)if(var[j]==wrtvar){exists=true;pos=j;break;}
	if(!exists){var.push_back(variable<dtyp>(wrtvar,from));pos=var.size()-1;}
	for(i=from;i<=to;i++){s+=eval(a,var,stack);var[pos].val++;}
	if(!exists)var.erase(var.begin()+pos);
	return s;
}

template<class dtyp>
inline dtyp sigma_loc_var(std::string& a,int from,int to,char* wrtvar)
{
	std::vector<variable<dtyp> > var;
	load_var<dtyp>(var);
	return sigma_common<dtyp>(a,from,to,wrtvar,var);
}

template<class dtyp>
inline dtyp sigma_glob_var(std::string& a,int from,int to,char* wrtvar)
{
	dtyp v;
	std::vector<variable<dtyp> >& var=varop<dtyp>::gvar;
	if(!math_mode<dtyp>::glob_var_loaded)
	{var.clear();load_var<dtyp>(var);math_mode<dtyp>::glob_var_loaded=true;}
	v=sigma_common<dtyp>(a,from,to,wrtvar,var);
	var[0].val=v;
	return v;
}

template<class dtyp>
inline dtyp sigma(std::string& a,int from,int to,char* wrtvar)
{return ((expreval_mode::loc_var)?sigma_loc_var<dtyp>(a,from,to,wrtvar):sigma_glob_var<dtyp>(a,from,to,wrtvar));}

//product------------------------------------------------------------------------------

template<class dtyp>
dtyp pi_common(std::string& a,int from,int to,char* wrtvar,std::vector<variable<dtyp> >& var)
{
	dtyp p=1;int i,j,pos;bool exists=false;
	std::vector<dtyp> stack;
	stack.reserve(10);
	ready<dtyp>(a);
	for(j=0;j<int(var.size());j++)if(var[j]==wrtvar){exists=true;pos=j;break;}
	if(!exists){var.push_back(variable<dtyp>(wrtvar,from));pos=var.size()-1;}
	for(i=from;i<=to;i++){p*=eval(a,var,stack);var[pos].val++;}
	if(!exists)var.erase(var.begin()+pos);
	return p;
}

template<class dtyp>
inline dtyp pi_loc_var(std::string& a,int from,int to,char* wrtvar)
{
	std::vector<variable<dtyp> > var;
	load_var<dtyp>(var);
	return pi_common<dtyp>(a,from,to,wrtvar,var);
}

template<class dtyp>
inline dtyp pi_glob_var(std::string& a,int from,int to,char* wrtvar)
{
	dtyp v;
	std::vector<variable<dtyp> >& var=varop<dtyp>::gvar;
	if(!math_mode<dtyp>::glob_var_loaded)
	{var.clear();load_var<dtyp>(var);math_mode<dtyp>::glob_var_loaded=true;}
	v=pi_common<dtyp>(a,from,to,wrtvar,var);
	var[0].val=v;
	return v;
}

template<class dtyp>
inline dtyp product(std::string& a,int from,int to,char* wrtvar)
{return ((expreval_mode::loc_var)?pi_loc_var<dtyp>(a,from,to,wrtvar):pi_glob_var<dtyp>(a,from,to,wrtvar));}

//-------------------------------------------------------------------------------------

#endif	//_INC_EKU_EXPREVAL_APPLY