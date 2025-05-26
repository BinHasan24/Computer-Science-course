#include <iostream>
#include <cstring> // for strlen, strcpy, ...

class MyString {
private:
    static const size_t SSO_BUFFER_SIZE = 15; // small string buffer size (fits in the union)
    
    union {
        char ssoBuffer[SSO_BUFFER_SIZE + 1]; 
        char* heapBuffer;
    };

    size_t _size;
    size_t _capacity;
    bool usingSSO;

    void allocateHeap(size_t newCapacity) {
        char* newBuffer = new char[newCapacity + 1];
        if (usingSSO) {
            std::strcpy(newBuffer, ssoBuffer);
        } else {
            std::strcpy(newBuffer, heapBuffer);
            delete[] heapBuffer;
        }
        heapBuffer = newBuffer;
        _capacity = newCapacity;
        usingSSO = false;
    }

public:
    // Default constructor: start as empty string using SSO
    MyString() : _size(0), _capacity(SSO_BUFFER_SIZE), usingSSO(true) {
        ssoBuffer[0] = '\0';
    }

    // Constructor from const char*
    MyString(const char* str) {
        _size = std::strlen(str);
        if (_size <= SSO_BUFFER_SIZE) {
            usingSSO = true;
            _capacity = SSO_BUFFER_SIZE;
            std::strcpy(ssoBuffer, str);
        } else {
            usingSSO = false;
            _capacity = _size;
            heapBuffer = new char[_capacity + 1];
            std::strcpy(heapBuffer, str);
        }
    }

    // Destructor
    ~MyString() {
        if (!usingSSO) {
            delete[] heapBuffer;
        }
    }

    // Copy constructor
    MyString(const MyString& other) {
        _size = other._size;
        _capacity = other._capacity;
        usingSSO = other.usingSSO;
        if (usingSSO) {
            std::strcpy(ssoBuffer, other.ssoBuffer);
        } else {
            heapBuffer = new char[_capacity + 1];
            std::strcpy(heapBuffer, other.heapBuffer);
        }
    }

    // operator[] for getting characters
    char& operator[](size_t index) {
        if (usingSSO) {
            return ssoBuffer[index];
        } else {
            return heapBuffer[index];
        }
    }

    const char& operator[](size_t index) const {
        if (usingSSO) {
            return ssoBuffer[index];
        } else {
            return heapBuffer[index];
        }
    }

    // Add a character at the end
    void add(char c) {
        if (_size + 1 > _capacity) {
            // Need to allocate more space
            size_t newCapacity = (_capacity * 2) + 1;
            allocateHeap(newCapacity);
        }

        if (usingSSO) {
            ssoBuffer[_size] = c;
            ssoBuffer[_size + 1] = '\0';
        } else {
            heapBuffer[_size] = c;
            heapBuffer[_size + 1] = '\0';
        }

        _size++;
    }

    // Return size
    size_t size() const {
        return _size;
    }

    // Return capacity
    size_t capacity() const {
        return _capacity;
    }

    // Reserve memory
    void reserve(size_t newCapacity) {
        if (newCapacity <= _capacity) return;

        allocateHeap(newCapacity);
    }

    // Print for debugging
    void print() const {
        if (usingSSO) {
            std::cout << ssoBuffer;
        } else {
            std::cout << heapBuffer;
        }
    }
};

// Example usage
int main() {
    MyString s("hello");
    s.add('!');
    s.print(); // prints: hello!
    std::cout << "\nSize: " << s.size() << ", Capacity: " << s.capacity() << std::endl;

    MyString s2 = s; // copy constructor
    s2.add('?');
    s2.print(); // prints: hello!?

    return 0;
}
