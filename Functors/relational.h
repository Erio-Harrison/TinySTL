#include "func_interface.h"
template <class T>
struct euqal_to : public binary_function<T,T,bool>
{
    bool operator()(const T& x, const T& y){ return x == y; }
};

template <class T>
struct not_euqal_to : public binary_function<T,T,bool>
{
    bool operator()(const T& x, const T& y) { return x != y;}
};

template <class T>
struct greater : public binary_function<T,T,bool>
{
    bool operator()(const T&x, const T&y) { return x>y;}
};

template < class T>
struct less : public binary_function<T,T,bool>
{
    bool operator()(const T& x, const T& y){ return x<y;}
};

template <class T>
struct greater_euqal : public binary_function<T,T,bool>
{
    bool operator()(const T&x, const T&y){ return x >= y;}
};

template < class T>
 struct less_equal : public binary_function<T,T,bool>
 {
     bool operator()(const T& x, const T& y) { return x <= y;}
 };
