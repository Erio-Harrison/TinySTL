# include "algobase.h"
template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
    if(first == last) return first;
    ForwardIterator next = first;
    while(++first != last){
        if(*first == *next) return first;
        next = first;
    }
    return last;
}

template <class InputIterator,class T>
InputIterator find(InputIterator first, InputIterator last, const T& value){
    while(first != last && *first != value) ++first;
    return first;
}

template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred){
    while(first != last && !pred(*first)) ++first;
    return first;
}

// TODO find_end

template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                           ForwardIterator first2, ForwardIterator last2)
{
    for(;first1!=last1;++first1)
        for(ForwardIterator iter = first2; iter != last2; ++iter)
            if(*first1 == *iter) return first1;
    return last1;
}

template <class Inputerator, class Function>
Function for_each(Inputerator first, Inputerator last, Function f)
{
    for(; first!=last;++first)
        f(*first);
    return f;
}

template <class InputIterator, class Generator>
void generate(InputIterator first, InputIterator last, Generator gen){
    for(;first!=last;++first)
        *first = gen();
}

template <class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2)
{
    while(first1!=last1 && first2!=last2){
        if(*first1 > *first2)
            return false;
        else if(*first1 < *first2)
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}

template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
    if(first == last) return first;
    ForwardIterator result = first;
    while(++first != last){
        if(*result< *first) result = first;
    }
    return result;
}

//TODO merge function combined copy

template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
{
    if(first == last) return first;
    ForwardIterator result = first;
    while(++first != last){
        if(*result > *first) result = first;
    }
    return result;
}

/*template <class BidirectionalIterator,class Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last,Predicate pred)
{
    //TODO partion function
}*/

/*
   remove 函数主要用于直接在原地（in-place）修改序列，移除所有与指定值相等的元素
   它不删除元素，而是将不需移除的元素移到序列的开始处，返回新序列的结束迭代器
   删除操作通常通过容器的 erase 方法与 remove 结合来实现。

   例子：
   std::vector<int> v = {1, 2, 0, 4, 0, 6};
   auto newEnd = std::remove(v.begin(), v.end(), 0);
   v.erase(newEnd, v.end());  // 真正删除元素

 */
template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value)
{
    find(first,last,value);
    ForwardIterator next = first;
    return first == last? first: remove_copy(++next,last,first,value);
}

/*
例子：
    假设有一个数组，并且你想要创建一个新的数组，其中包含原始数组的所有非零元素
    int src[] = {1, 2, 0, 4, 0, 6};
    int dest[4];  // 假设已知非零元素的数量
    std::remove_copy(src, src + 6, dest, 0);

    这里，remove_copy 将 src 中所有非零元素复制到 dest 数组中。
 */

template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last,
                           OutputIterator result, const T& value)
{
    for(;first!=last;++first)
        if(*first != value)
            *result = *first;
            ++result;
    return result;
}

template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
{
    first = find_if(first,last,pred);
    ForwardIterator next = first;
    return  first == last ? first : remove_copy_if(++next,last,first,pred);
}

template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last,
                              OutputIterator result, Predicate pred)
{
    for(;first!=last;++first)
        if(!pred)
            *result = *first;
            ++result;
    return result;
}

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
{
    while(first != last) {
        if (*first == old_value) *first = new_value;
    }
}

template <class InputIterator, class outputIterator, class T>
void replace_copy(InputIterator first, InputIterator last, outputIterator result,
                  const T& old_value, const T& new_value)
{
    for(;first != last; ++first, ++result)
        *first = *first == old_value ? new_value : *first;

    return result;
}

template <class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& value)
{
    for(;first!=last;++first){
        if(pred(*first)) *first = value;
    }
}

template <class InputIterator, class OutputIterator, class Predicate,class T>
OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result,
                     Predicate pred,const T& value)
{
    for(; first!=last;++first,++result){
        *result = pred(*first) ? value : *first;
    }
    return result;
}

// TODO reverse function

// TODO rotate

// TODO search_copy

template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value)
{
    if(count <= 0){
        return first;
    }
    else{
        first = find(first,last,value);
        while(first != last){
            ForwardIterator i = first;
            Integer n = count -1;
            ++i;
            while(i!=last && n != 0 && *i == value){
                ++i;
                --n;
            }
            if(n == 0) return first;
            else first = find(i,last,value);
        }
        return last;
    }
}

/*
 * 将[first1,last1)区间内的元素与“从first2开始、个数相同”的元素互相交换。
 * 这两个序列可位于同一容器中，也可位于不同的容器中。
 * 如果第二序列的长度小于第一序列，或是两序列在同一容器中彼此重叠，执行结果未可预期
 * */
template < class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
                             ForwardIterator2 first2)
{
    for(;first1 != last1; ++first1, ++first2){
        iter_swap(first1,first2);
    }
    return first2;
}

template <class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation op)
{
    for(;first!=last;++first, ++result){
        *result = op(*first);
    }

    return result;
}

// TODO unique_copy
// TODO lower_bound
// TODO upper_bound
// TODO binary_search
// TODO next_permutation
// TODO prev_permutation

template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator rand)
{
    if(!first == last){
        for(RandomAccessIterator i = first +1; i != last; ++i){
            iter_swap(i,first+rand(i-first + 1));
        }
    }
}

// TODO partial_sort
// TODO partial_sort_copy

// TODO 排序


