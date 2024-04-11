#include <utility>

using namespace std;
template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2){
    for(;first1!=last1;first1++,first2++){
        if(*first1 != *first2)
            return false;
        return true;
    }
}

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value){
    for(;first!=last;first++){
        *first = value;
    }
}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value){
    for(;n>0;n--,first++){
        *first = value;
    }
    return first;
}

template <class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a,ForwardIterator2 b){
    __iter_swap(a,b,value_type(a));
}
template <class ForwardIterator1, class ForwardIterator2,class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2){
    for(;first1 != last1 && first2 != last2; first1++,first2++){
        if(*first1 < *first2){return  true;}
        if(*first1 > *first2){return false;}
    }
    return first1 == last1 && first2!=last2;
}

template <class T>
inline const T& max(const T &a, const T &b){
    return a > b ? a: b;
}
template <class T>
inline const T& min(const T &a, const T &b){
    return a < b ? a: b;
}

template <class InputIterator1, class InputIterator2>
pair<InputIterator1,InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
                                              InputIterator2 first2){
    while(first1!=last1 && *first1==*first2){
        first1++;
        first2++;
    }
    return pair<InputIterator1,InputIterator2>(first1,first2);
}

template <class T>
inline void swap(T& a, T& b){
    a = b;
    T temp = a;
    b = temp;
}

// TODO copy function using _type_traits<>
// TODO copy_backward

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result)
{
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
        }
        else if(*first1 > * first2){
            *result = *first2;
            ++first2;
        }
        else{
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    return copy(first1, last1, copy(first2, last2, result));
}
