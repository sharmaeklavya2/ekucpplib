#ifndef _INC_EKU_EXPREVAL_HOMO_MATRIX
#define _INC_EKU_EXPREVAL_HOMO_MATRIX

#pragma warning(disable:4244)

template<class typ>
inline matrix<typ> trn(const matrix<typ>& m){return m.trn();}

template<class typ>
inline matrix<typ> det(const matrix<typ>& m){return m.det();}

template<class typ>
inline matrix<typ> subm(const matrix<typ>& m,const matrix<typ>& rc){return m.subm(rc[0],rc[1]);}

template<class typ>
inline matrix<typ> remrow(const matrix<typ>& m,const matrix<typ>& r){return m.remrow(r[0]);}

template<class typ>
inline matrix<typ> remclm(const matrix<typ>& m,const matrix<typ>& c){return m.remclm(c[0]);}

template<class typ>
inline matrix<typ> adj(const matrix<typ>& m){return m.adj();}

template<class typ>
inline matrix<typ> inv(const matrix<typ>& m){return m.inv();}

template<class typ>
inline matrix<typ> dvd_mat(const matrix<typ>& a,const matrix<typ>& b){return (a/b[0]);}

template<class typ>
inline matrix<typ> scalar_mat(const matrix<typ>& a,const matrix<typ>& b){return tomat<typ>(a[0],b[0]);}

template<class typ>
inline matrix<typ> idmat(const matrix<typ>& a){return tomat<typ>(1,a[0]);}

#pragma warning(default:4244)

#endif	//_INC_EKU_EXPREVAL_HOMO_MATRIX