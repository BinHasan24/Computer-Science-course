#include <iostream> // for std::cout --- test

// ---- Template for the smart pointer
template<typename T, typename Deleter>
class MySharedPtr {
private:
    T* ptr;              // raw pointer to the object
    int* refCount;       // shared reference count
    Deleter deleter;     // custom deleter 

public:
    // -- Constructor
    MySharedPtr(T* p) : ptr(p), refCount(new int(1)) {
        
    }

    // -- Copy Constructor
    MySharedPtr(const MySharedPtr& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        deleter = other.deleter;
        ++(*refCount); // increment reference count
    }

    // --  Assignment Operator
    MySharedPtr& operator=(const MySharedPtr& other) {
        if (this != &other) {
            release();        // decrease current object's ref count
            ptr = other.ptr;
            refCount = other.refCount;
            deleter = other.deleter;
            ++(*refCount);          // increase new object's ref count
        }
        return *this;
    }

    // --- Destructor
    ~MySharedPtr() {
        release(); // handles decreasing ref count and deletion
    }

    // Dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Arrow operator
    T* operator->() const {
        return ptr;
    }

    // Get the raw pointer
    T* get() const {
        return ptr;
    }

    //--- Get current reference count (for debug or testing)
    int use_count() const {
        return *refCount;
    }

private:
    //--------- just  Helper (ref count and deletion)
    void release() {
        if (--(*refCount) == 0) {
            deleter(ptr);     // custom deleter is used
            delete refCount;  // delete ref count
        }
    }
};

