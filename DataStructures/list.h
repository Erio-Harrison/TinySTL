#include <cstddef>
#include <memory>
#include "../Iterators/iterator.h"
#include "../Allocators/construct.h"

namespace TinySTL{
    //Node
    template <class T>
    struct __list_node{
        typedef void* void_pointer;
        void_pointer prev;
        void_pointer next;
        T data;
    };

//list�ĵ�����
    template <class T, class Ref, class Ptr>
    struct __list_iterator{
        typedef __list_iterator<T,T&,T*> iterator;
        typedef __list_iterator<T,Ref,Ptr> self;

        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef reference;
        typedef __list_node<T>* link_type;

        link_type node;
        //constructor
        __list_iterator(link_type x):node(x) {}
        __list_iterator(){}
        __list_iterator(const iterator& x):node(x.node) {}

        bool operator == (const self& x) const {return node == x.node;}
        bool operator != (const self& x) const {return node != x.node;}

        // "->" �䵱 "(*node).data;"���﷨��
        reference operator*() const {return (*node).data;}
        pointer operator->() const {return &(operator*());}

        self& operator++(){
            node = (link_type) ((*node).next);
            return *this;
        }

        self operator++(int){
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self& operator--(){
            node = (link_type) ((*node).prev);
            return *this;
        }

        self operator--(int){
            self tmp = *this;
            --*this;
            return tmp;
        }
    };
}

template <class T, class Alloc = std::allocator<T>>
class list{
protected:
    typedef TinySTL::__list_node<T> list_node;
    typedef simple_alloc<list_node,Alloc> list_node_allocator;
public:
    typedef list_node* link_type;
    typedef TinySTL::__list_iterator<T, T&, T*> iterator;
protected:
    link_type node;
public:
    iterator begin(){return (link_type)((*node).next);}
    iterator end(){return node;}
    bool empty() const {return node->next == node;}
    size_t size(){
        size_t result = 0;
        distance(begin(),end(),result);
        return result;
    }

    T& front(){ return *begin();}
    T& back(){ return *(--end());}
    void clear() {
        link_type cur = node->next;
        while (cur != node) {
            link_type next = cur->next;
            destroy_node(&cur->data);  // Assuming destroy deallocates and destroys an element
            put_node(cur);        // Deallocate node
            cur = next;
        }
        node->next = node;
        node->prev = node;
    }
protected:
    link_type get_node() {return list_node_allocator ::allocate();}
    void put_node(link_type p) {list_node_allocator ::deallocate();}

    link_type create_node(const T&x){
        link_type p = get_node();
        construct(&p -> data, x);
        return p;
    }
    void destroy_node(link_type p)
    {
        destroy(&p -> data);
        put_node(p);
    }

public:
    list(){empty_initialize();}
protected:
    void empty_initialize(){
        node = get_node();
        node -> next = node;
        node -> prev = node;
    }

public:
    iterator insert(iterator position, const T&x){
        link_type tmp = create_node(x);
        tmp -> next = position.node;
        tmp -> prev = position.node -> prev;
        (link_type(position.node -> prev)) -> next = tmp;
        position.node -> prev = tmp;
        return tmp;
    }
    
public:
    void push_front(const T&x) { insert(begin(),x);}
    void push_back(const T&x) { insert(end(),x);}
    
    iterator erase(iterator position){
        link_type next_node = link_type(position.node -> next);
        link_type prev_node = link_type (position.node -> prev);
        prev_node -> next = next_node;
        next_node -> prev = prev_node;
        destroy(position.node);
        return iterator(next_node);
    }
    
    void pop_front(){ erase(begin());}
    void pop_back() { 
        iterator tmp = end();
        erase(--tmp);
    }

    void remove(const T& value)
    {
        iterator first = begin();
        iterator last = end();
        while(first != last)
        {
            iterator next = first;
            ++next;
            if(*first == value) erase(first);
            first = next;
        }
    }

    void unique()
    {
        iterator first = begin();
        iterator last = end();
        if(first == last) return;
        iterator next = first;
        while(++next != last)
        {
            if(*first == *next)
                erase(next);
            else
                first = next;
            next = first;
        }
    }

    void transfer(iterator position,iterator first, iterator last)
    {
        if(position != last)
        {
            /*TODO*/
        }
    }

};

