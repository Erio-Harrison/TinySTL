#include <iterator>
template <class Iterator, class T>
Iterator find(Iterator begin, Iterator end, const T& value){
    while(begin != end && *begin != value){
        ++begin;
    }
    return begin;
}

template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init){
    for(;first!=last;++first){
        init += *first;
    }
    return init;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
                                    OutputIterator result, T*) {
    T value = *first;
    *result = value;
    while(++first != last){
        T temp = *first;
        *++result = temp - value;
        value = temp;
    }
    return ++result;
}

template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init){
    for(; first1!=last1;first1++,first2++)
        init += (*first1 * *first2);
    return init;
}

template <class InputIterator, class OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last,OutputIterator result){
    if(first == last) return;
    *result = *first;
    using ValueType = typename std::iterator_traits<InputIterator>::value_type;
    return __partial_sum(first, last, result, static_cast<ValueType*>(nullptr));
}
template <class InputIterator, class OutputIterator, class T>
OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator result, T*){
    T value = *first;
    while(++first!=last){
        value += *first;
        *++result = value;
    }
    return ++result;
}

