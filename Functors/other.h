#include "func_interface.h"

template <class T>
struct identity : public unary_function<T,T>
{
    const T& operator()(const T&x) const {return x;}
};

template <class Pair>
struct select1st : public unary_function<Pair, typename Pair :: first_type>
{
    const typename Pair :: first_type& operator()(const Pair& x) const
    {
        return x.first;
    }
};

template <class Pair>
struct select2nd : public unary_function<Pair, typename Pair :: first_type>
{
    const typename Pair :: first_type& operator()(const Pair& x) const
    {
        return x.second;
    }
};

template <class Arg1,class Arg2>
struct project1st : public binary_function<Arg1,Arg2,Arg1>
{
    Arg1 operator()(const Arg1& x, const Arg2&) {return x;}
};

template <class Arg1,class Arg2>
struct project2nd : public binary_function<Arg1,Arg2,Arg1>
{
    Arg1 operator()(const Arg1& , const Arg2& y) {return y;}
};