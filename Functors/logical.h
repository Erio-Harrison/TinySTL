#include "func_interface.h"
template <class T>
struct logical_and : public binary_function<T,T,bool>
{
    bool operator()(const T& x, const T& y) {return x && y;}
};

template <class T>
struct logical_or : binary_function<T,T,bool>
{
    bool operator()(const T&x, const T&y){return x||y;}
};

template<class T>
struct logical_not : unary_function<T,bool>
{
    bool operator()(const T& x) { return !x;}
};

