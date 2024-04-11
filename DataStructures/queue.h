#include <cstddef>
#include <stdexcept>  // For std::out_of_range

template <class T>
class queue {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef size_t size_type;

private:
    pointer array;           // Dynamic array for storing elements
    size_type array_capacity;  // Capacity of the queue
    size_type head;           // Index of the front element
    size_type tail;           // Index where the next element will be inserted

public:
    queue() : array(nullptr), array_capacity(0), head(0), tail(0) {}

    ~queue() {
        delete[] array;
    }

    bool empty() const {
        return head == tail;
    }

    size_type size() const {
        return tail - head;
    }

    void enqueue(const T& value) {
        if (tail == array_capacity) {
            // Increase the capacity of the array
            increase_capacity();
        }
        array[tail++] = value;
    }

    void dequeue() {
        if (empty()) {
            throw std::out_of_range("Queue underflow");
        }
        ++head;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return array[head];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return array[head];
    }

private:
    void increase_capacity() {
        size_type new_capacity = array_capacity == 0 ? 1 : 2 * array_capacity;
        pointer new_array = new T[new_capacity];

        for (size_type i = head; i < tail; ++i) {
            new_array[i - head] = array[i];
        }

        delete[] array;
        array = new_array;
        tail -= head;
        head = 0;
        array_capacity = new_capacity;
    }
};
