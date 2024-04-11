#include <cstddef>
#include <stdexcept>  // For std::out_of_range

template <class T>
class stack {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef size_t size_type;

private:
    pointer array;           // Dynamic array to store stack elements
    size_type array_capacity;  // Current capacity of the stack
    size_type array_size;      // Current size of the stack (number of elements)

public:
    stack() : array(nullptr), array_capacity(0), array_size(0) {}

    ~stack() {
        delete[] array;
    }

    bool empty() const {
        return array_size == 0;
    }

    size_type size() const {
        return array_size;
    }

    void push(const T& value) {
        if (array_size == array_capacity) {
            // Increase the capacity of the array
            increase_capacity();
        }
        array[array_size++] = value;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack underflow");
        }
        --array_size;
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return array[array_size - 1];
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return array[array_size - 1];
    }

private:
    void increase_capacity() {
        size_type new_capacity = array_capacity == 0 ? 1 : 2 * array_capacity;
        pointer new_array = new T[new_capacity];

        for (size_type i = 0; i < array_size; ++i) {
            new_array[i] = array[i];
        }

        delete[] array;
        array = new_array;
        array_capacity = new_capacity;
    }
};
