#include <cstddef>
#include "../Algorithms/algobase.h"
#include "../Allocators/construct.h"

inline size_t __deque_buf_size(size_t n, size_t sz)
{
    return n != 0 ? n : (sz<512 ? size_t(512/sz) : size_t(1));
}

template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator
{
    typedef __deque_iterator<T,T&,T*,BufSiz> iterator;
    typedef __deque_iterator<T,const T&, const T*,BufSiz> const_iterator;
    static size_t buffer_size() {return __deque_buf_size(BufSiz,sizeof(T));}

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;

    typedef __deque_iterator self;
    T* current;
    T* first;
    T* last;
    map_pointer node;

    void set_node(map_pointer new_node)
    {
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const { return *current; }
    pointer operator->() const { return &(operator*());}

    difference_type operator-(const self& x) const
    {
        return difference_type((buffer_size()) * (node - x.node -1) +
        (current - first) + (x.last - x.current));
    }

    self& operator++(){
        ++current;
        if(current == last){
            set_node(node+1);
            current = first;
        }
        return *this;
    }

    self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--()
    {
        if(current == first){
            set_node(node -1);
            current = last;
        }
    }

    self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    /*TODO operator += + -= - []*/
};

template <class T, class Alloc = alloc,size_t BufSiz = 0>
class deque
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef size_t size_type;

public:
    typedef __deque_iterator<T, T&,T*, BufSiz> iterator;
protected:
    typedef pointer* map_pointer;

protected:
    iterator start;
    iterator finish;
    map_pointer map;
    size_type map_size;

public:
    iterator begin(){return start;}
    iterator end(){return finish;}
};