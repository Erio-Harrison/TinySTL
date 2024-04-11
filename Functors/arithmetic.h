#include "func_interface.h"

template <class T>
struct plus : public binary_function<T,T,T>
{
    T operator() (const T& x, const T& y) const {return x+y;}
};

template <class T>
struct minus : public binary_function<T,T,T>
{
    T operator()(const T& x, const T& y){return x-y;}
};

template <class T>
struct multiplies : public binary_function<T,T,T>
{
    T operator()(const T& x, const T& y){return x*y;}
};

template <class T>
struct divides : public binary_function<T,T,T>
{
    T operator()(const T& x, const T& y) {return x/y;}
};

template <class T>
struct modules : public binary_function<T,T,T>
{
    T operator()(const T& x, const T& y) {return x%y;}
};

template <class T>
struct negate : public unary_function<T,T>
{
    T operator()(const T& x) {return -x;}
};


