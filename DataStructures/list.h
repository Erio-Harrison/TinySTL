#include <cstddef>
/*list�Ĳ���̫���ˣ������ʦ�ᵽû�б�Ҫһһ���⣬֮����ʱ�������������*/
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
    link_type node;  // �ڱ��ڵ�

public:
    list() { empty_initialize(); }
    ~list() {
        // ����б�ɾ���ڱ��ڵ�
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

    // ���������
    class iterator {
        // ...
    };

    iterator begin() { return iterator(node->next); }
    iterator end() { return iterator(node); }

protected:
    void empty_initialize() {
        node = new node_type(T());  // �����ڱ��ڵ�
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
