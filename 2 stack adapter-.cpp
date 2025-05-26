//----- StackAdapter.h

#include "MyDeque.h"

// Stack adapter that uses MyDeque internally
template <typename T>
class StackAdapter {
private:
    MyDeque<T> container;

public:
    void push(const T& value) {
        container.push_back(value);
    }

    void pop() {
        container.pop_back();
    }

    T& top() {
        return container.back();
    }

    int size() const {
        return container.size();
    }

    bool empty() const {
        return container.size() == 0;
    }
};
