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
    using iterator = __deque_iterator<T,T&,T*,BufSiz> ;
    using const_iterator =  __deque_iterator<T,const T&, const T*,BufSiz>;
    static size_t buffer_size() {return __deque_buf_size(BufSiz,sizeof(T));}

    using iterator_category =  random_access_iterator_tag;
    using value_type = T;
    using pointer = Ptr;
    using reference =  Ref;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using map_pointer = T**;

    using self =  __deque_iterator;
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
    typedef __deque_iterator<T, T&,T*, BufSiz> iterator;


    typedef iterator::reference reference;
    typedef iterator::difference_type difference_type;
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

    reference operator[](size_type n){
        return start[difference_type(n)];
    }

    reference front(){return *start;}
    reference back(){
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }

    size_type size() const {return finish - start;}
    size_type max_size() const {return size_type(-1);}
    bool empty() const {return finish == start;}
    size_type initial_map_size() const {
        // This size can be adjusted based on expected usage patterns or performance tuning
        return 8; // A reasonable default starting size
    }

    //TODO review
    void create_map_and_nodes(size_type num_elements)
    {
        if (__deque_iterator<T, T&, T*, BufSiz>::buffer_size() == 0){
            return;
        }

        size_type num_nodes = (num_elements / __deque_iterator<T, T&, T*, BufSiz>::buffer_size()) +
                              (num_elements % __deque_iterator<T, T&, T*, BufSiz>::buffer_size() != 0);
        map_size = max(initial_map_size(), num_nodes + 2); // Ensure at least two extra nodes for growth

        map = new pointer[map_size]; // Assuming pointer is `value_type*`
        fill_n(map, map_size, nullptr); // Initialize map pointers to nullptr
    }

    //TODO review
    void destroy_map_and_nodes() {
        if (map != nullptr) {
            // Iterate through the map and delete all allocated buffers
            for (map_pointer current = map; current < map + map_size; ++current) {
                if (*current != nullptr) {
                    // Assuming the buffer is filled with objects that need to be destructed
                    value_type* buffer = *current;
                    destroy(buffer, buffer + __deque_iterator<T, T&, T*, BufSiz>::buffer_size()); // Destroy objects
                    delete[] buffer;  // Deallocate buffer
                }
            }
            // Now delete the map itself
            delete[] map;
            map = nullptr; // Clear the pointer to avoid dangling references
            map_size = 0; // Reset size to ensure consistency
        }
    }

    void fill_initialize(size_type n, const value_type& value) {
        create_map_and_nodes(n); // Allocate nodes

        map_pointer current = map;
        try {
            for (size_type i = 0; i < n; ) {
                *current = new value_type[__deque_iterator<T, T&, T*, BufSiz>::buffer_size()]; // Allocate buffer
                size_type elements_to_init = min(n - i, __deque_iterator<T, T&, T*, BufSiz>::buffer_size());
                uninitialized_fill_n(*current, elements_to_init, value);
                ++current;
                i += elements_to_init;
            }
            start.set_node(map);
            finish.set_node(map + (n - 1) / __deque_iterator<T, T&, T*, BufSiz>::buffer_size());
            finish.current = finish.first + (n % __deque_iterator<T, T&, T*, BufSiz>::buffer_size()); // Adjust the finish.current
        } catch (...) { // Catch all exceptions
            destroy_map_and_nodes(); // Clean up resources
            throw; // Re-throw the exception to maintain the exception propagation
        }
    }

    deque(int n, const value_type& value): start(),finish(),map(0),map_size(0)
    {
        fill_initialize(n,value);
    }

public:
    //TODO review
    void reserve_map_at_back(size_type nodes_to_add = 1) {
        if (nodes_to_add + 1 > map_size - (finish.node - map)) {
            // Number of nodes needed to handle new growth
            const size_type old_num_nodes = finish.node - start.node + 1;
            const size_type new_num_nodes = old_num_nodes + nodes_to_add;

            map_pointer new_map = new pointer[new_num_nodes + 2];  // Allocate new map with extra space
            map_pointer new_map_start = new_map + 1;

            copy(start.node, finish.node + 1, new_map_start);  // Copy existing nodes to new map

            // Delete old map and assign new map with updated details
            delete[] map;
            map = new_map;
            map_size = new_num_nodes + 2;

            // Update start and finish iterators to point to the new map
            start.set_node(new_map_start);
            finish.set_node(new_map_start + old_num_nodes - 1);
        }
    }
    //TODO review
    pointer allocate_node() {
        return new value_type[iterator::buffer_size()];  // Allocate a new node with buffer size
    }

    void push_back_aux(const value_type& t)
    {
        value_type t_copy = t;
        reserve_map_at_back(); //������������������ػ�һ��map
        *(finish.node + 1) = allocate_node();
        try{
            construct(finish.current,t_copy);
            finish.set_node(finish.node + 1);
            finish.current = finish.first;
        }catch(...){
            destroy_map_and_nodes(); // Clean up resources
            throw; // Re-throw the exception to maintain the exception propagation
        }

    }

    void push_back(const value_type& t)
    {
        if(finish.current != finish.last -1)
        {
            construct(finish.current,t);
            ++finish.current;
        }
        else
        {
            push_back_aux(t);
        }
    }

};