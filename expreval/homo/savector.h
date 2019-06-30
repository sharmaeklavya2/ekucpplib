#ifndef _INC_EKU_EXPREVAL_HOMO_SAVECTOR
#define _INC_EKU_EXPREVAL_HOMO_SAVECTOR

template<class typ>
savct<typ> vnorm(const savct<typ>& a){return savct<typ>(a.norm());}

template<class typ>
savct<typ> vabs(const savct<typ>& a){return savct<typ>(a.abs());}

template<class typ>
savct<typ> dot(const savct<typ>& a,const savct<typ>& b){return a.dot(b);}

template<class typ>
savct<typ> cross(const savct<typ>& a,const savct<typ>& b){return a.cross(b);}

template<class typ>
savct<typ> ang(const savct<typ>& a,const savct<typ>& b){return savct<typ>(a.ang(b));}

template<class typ>
savct<typ> divide(const savct<typ>& a,const savct<typ>& b){return a/b.n;}

#endif	//_INC_EKU_EXPREVAL_HOMO_SAVECTOR