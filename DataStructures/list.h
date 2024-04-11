#include <cstddef>
/*list的操作太多了，侯捷老师提到没有必要一一讲解，之后有时间可以慢慢补上*/
template <class T>
struct _list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <class T>
class list {
public:
    typedef _list_node<T> node_type;
    typedef node_type* link_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef size_t size_type;

private:
    link_type node;  // 哨兵节点

public:
    list() { empty_initialize(); }
    ~list() {
        // 清空列表并删除哨兵节点
        clear();
        delete node;
    }

    bool empty() const { return node->next == node; }
    size_type size() const {
        size_type result = 0;
        link_type cur = node->next;
        while (cur != node) {
            cur = cur->next;
            ++result;
        }
        return result;
    }

    void clear() {
        link_type cur = node->next;
        while (cur != node) {
            link_type tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        node->next = node;
        node->prev = node;
    }

    void push_back(const T& value) {
        insert(end(), value);
    }

    void pop_back() {
        iterator tmp = end();
        erase(--tmp);
    }

    // 定义迭代器
    class iterator {
        // ...
    };

    iterator begin() { return iterator(node->next); }
    iterator end() { return iterator(node); }

protected:
    void empty_initialize() {
        node = new node_type(T());  // 创建哨兵节点
        node->next = node;
        node->prev = node;
    }

    iterator insert(iterator position, const T& value) {
        link_type tmp = new node_type(value);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        position.node->prev->next = tmp;
        position.node->prev = tmp;
        return iterator(tmp);
    }

    iterator erase(iterator position) {
        link_type prev_node = position.node->prev;
        link_type next_node = position.node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
        delete position.node;
        return iterator(next_node);
    }
};
