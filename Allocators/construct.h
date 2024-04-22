#include <new>
#include <cstdlib>
#include <type_traits>

//构造
template <class T1, class T2>
inline void construct(T1* p, T2 value)
{
    new (p) T1(value);
}
//析构
template <class T>
inline void destroy(T* pointer)
{
    pointer -> ~T();
}

template <class T, class Alloc>
class simple_alloc
{
public:
    static T *allocate(size_t n)
    {
        return 0 == n ? 0 : (T*) Alloc::allocate(n * sizeof(T));
    }

    static T*allocate(void)
    {
        return (T*) Alloc::allocate(sizeof (T));
    }

    static void deallocate(T *p, size_t n)
    {
        if(0!=n) Alloc::deallocate(p,n*sizeof(T));
    }

    static void deallocate(T *p)
    {
        Alloc::deallocate(p,sizeof (T));
    }
};


//一级配置器
template <int inst>
class __malloc_alloc_template
{
private:
    static void *oom_malloc(size_t);
    static void *oom_realloc(void*,size_t);
    static void (* __malloc_alloc_oom_handler)();

public:
    static void * allocate(size_t n)
    {
        void *result = malloc(n);
        if(result == nullptr) result = oom_malloc(n);
        return result;
    }

    static void deallocate(void *p, size_t /*n*/)
    {
        free(p);
    }

    static void * reallocate(void *p, size_t old_sz,size_t new_sz)
    {
        void *result = realloc(p,new_sz);
        if(result == nullptr) result = oom_realloc(p,new_sz);
        return result;
    }

    static void (* set_malloc_handler(void (*f)())) ()
    {
        void (*old) () = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);
    }
};
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;

template <int inst>
void (* __malloc_alloc_template<inst> :: __malloc_alloc_oom_handler)() = nullptr;

template <int inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void (* my_malloc_handler) ();
    void *result;

    for(;;)
    {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(my_malloc_handler == nullptr) {throw std::bad_alloc();}
        result = malloc(n);
        if(result) return result;
    }
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p,size_t n)
{
    void(* my_malloc_handler)();
    void *result;
    for(;;)
    {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(my_malloc_handler == nullptr) {throw std::bad_alloc();}
        result = realloc(p,n);
        if(result) return result;
    }
}

//二级配置器
/*TODO*/

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
{
    return __uninitialized_fill_n(first,n,x,value_type(first));
}

template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T&x, T1*)
{
    typedef typename std::is_pod<T1>::value is_POD;
    return __uninitializede_fill_n_aux(first,n,x,is_POD);
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, std::true_type) {
    return std::fill_n(first, n, x); // PODs can be handled by simply copying
}

template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type)
{
    ForwardIterator current = first;
    for(; n>0; --n, ++current)
        construct(&*cur,x);
    return current;
}