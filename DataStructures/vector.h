#include <cstddef>
#include <memory>
#include "../Allocators/construct.h"
namespace TinySTL{
    template <class T, class Alloc = std::allocator<T>>
    class vector{
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type* iterator;
        typedef value_type& reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

    protected:
        typedef simple_alloc<value_type,Alloc> data_allocator;

        iterator start;
        iterator finish;
        iterator end_of_storage;

        // TODO insert_aux(iterator position, const T& X);
        // TODO deallocate();
        // TODO fill_initialize();

    public:
        iterator begin(){return start;}
        iterator end(){return finish;}

        size_type size() const {return size_type(end() - begin());}
        size_type capacity() const {return size_type(end_of_storage - begin());}

        bool empty() {return begin() == end();}
        reference operator[](size_type n){ return *(begin() + n);}

        vector(): start(0),finish(0),end_of_storage(0){}
        vector(size_type n ,const T& value){ /*TODO fill_initialize(n,value)*/}
        vector(long n ,const T& value){ /*TODO fill_initialize(n,value)*/}
        explicit vector(size_type n){/*TODO fill_initialize(n,T()*/}

        ~vector(){
            /*
             * TODO destroy(start,finish)
             * TODO deallocate()
             * */
        }

        reference front(){return start;}
        reference  back(){return finish;}

        void push_back(const T& x){
            if(finish != end_of_storage){
                /*TODO construct(finish,x)*/
                ++finish;
            }else{;
                /* TODO insert_aux*(end(),x)*/

            }
        }
        void pop_back(){
            --finish;
            destroy(finish);
        }

        iterator erase(iterator position){
            if(position + 1 != end()){
                copy(position+1, finish,position);
            }
            --finish;
            destroy(finish);
            return position;
        }

        void resize(size_type new_size, const T& x) {
            if(new_size < size()){
                erase(begin()+new_size,end());
            }else{
                insert(end(),new_size-size(),x);
            }
        }

        void resize(size_type new_size){ resize(new_size,T());}
        void clear(){ erase(begin(),end());}

    protected:
        /*TODO iterator allocate_and_fill(size_type n, const T& x){}*/
    };
}