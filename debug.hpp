#ifndef _EKU_DEBUG
#define _EKU_DEBUG
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>

#if(__cplusplus == 201103)
#define CPP11
#endif

#ifdef CPP11
#include<type_traits>
template<bool b>
constexpr const char* _get_sep()
{return ", ";}
template<>
constexpr const char* _get_sep<true>()
{return ",\n ";}
template<class T>
constexpr const char* get_sep()
{return _get_sep<std::is_class<T>::value >();}
#else
template<class T>
const char* get_sep()
{return ", ";}
#endif

template<class T>
std::vector<T> mkv(const T* arr, int size)
{return std::vector<T>(arr, arr+size);}

template<class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{return os<<"("<<p.first<<", "<<p.second<<")";}

template<class itT>
void print(std::ostream& os, itT begin, itT end,
    const char* begstr="[", const char* endstr="]",
    const char* sepstr=get_sep<typename std::iterator_traits<itT>::value_type>())
{
    os<<begstr;
    if(begin!=end)
    {
        itT it = begin;
        os<<(*it);
        for(it++; it!=end; ++it)
            os<<sepstr<<(*it);
    }
    os<<endstr;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{print(os, v.begin(), v.end(), "[", "]"); return os;}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{print(os, s.begin(), s.end(), "{", "}"); return os;}

template<class KT, class VT>
std::ostream& operator<<(std::ostream& os, const std::map<KT, VT>& m)
{print(os, m.begin(), m.end(), "{{", "}}"); return os;}

void pais(std::ostream& os, const bool* v, int n)
//print as integer set
{
    int i;
    bool first = true;
    os<<"{";
    for(i=0; i<n; ++i)if(v[i])
    {
        if(!first)
        {os<<", "; first=false;}
        os<<i;
    }
}

#endif //_EKU_DEBUG
