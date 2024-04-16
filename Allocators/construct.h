#include <new>
#include <cstdlib>
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

