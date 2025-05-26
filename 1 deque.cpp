// ---------------------------------  MyDeque.h

#include <iostream>

// ----- Simple chunked deque structure
template <typename T>
class MyDeque {
private:
    static const int CHUNK_SIZE = 4; // small chunk size)
    T** chunks;                      // array of pointers to chunks
    int frontIndex, backIndex;      // chunk boundaries
    int capacity;                   // number of chunk slots
    int count;                      // number of elements

    void allocateChunks(int newCapacity) {
        T** newChunks = new T*[newCapacity];
        for (int i = 0; i < newCapacity; ++i)
            newChunks[i] = nullptr;

        int offset = (newCapacity - capacity) / 2;  // offset?? (To center data efficiently without shifting all data)
        for (int i = 0; i < capacity; ++i)
            newChunks[i + offset] = chunks[i];

        delete[] chunks;
        chunks = newChunks;
        frontIndex += offset;
        backIndex += offset;         
        capacity = newCapacity;
    }

    void ensureFrontSpace() {
        if (frontIndex == 0)
            allocateChunks(capacity * 2);
        if (!chunks[frontIndex - 1])
            chunks[--frontIndex] = new T[CHUNK_SIZE];
    }

    void ensureBackSpace() {
        if (backIndex == capacity - 1)
            allocateChunks(capacity * 2);
        if (!chunks[backIndex + 1])
            chunks[++backIndex] = new T[CHUNK_SIZE];
    }

public:
    MyDeque() {
        capacity = 8;
        chunks = new T*[capacity];
        for (int i = 0; i < capacity; ++i)
            chunks[i] = nullptr;
        frontIndex = backIndex = capacity / 2;
        chunks[frontIndex] = new T[CHUNK_SIZE];
        count = 0;
    }

    // Destructor ---- freeing memorey
    ~MyDeque() {
        for (int i = 0; i < capacity; ++i)
            delete[] chunks[i];
        delete[] chunks;
    }

    // Copy constructor ------  new memory
    MyDeque(const MyDeque& other) {
        capacity = other.capacity;
        frontIndex = other.frontIndex;
        backIndex = other.backIndex;
        count = other.count;

        chunks = new T*[capacity];
        for (int i = 0; i < capacity; ++i) {
            if (other.chunks[i]) {
                chunks[i] = new T[CHUNK_SIZE];
                for (int j = 0; j < CHUNK_SIZE; ++j)
                    chunks[i][j] = other.chunks[i][j];
            } else {
                chunks[i] = nullptr;
            }
        }
    }

    // Assignment operator
    MyDeque& operator=(const MyDeque& other) {
        if (this != &other) {
            for (int i = 0; i < capacity; ++i)
                delete[] chunks[i];
            delete[] chunks;

            capacity = other.capacity;
            frontIndex = other.frontIndex;
            backIndex = other.backIndex;
            count = other.count;

            chunks = new T*[capacity];
            for (int i = 0; i < capacity; ++i) {
                if (other.chunks[i]) {
                    chunks[i] = new T[CHUNK_SIZE];
                    for (int j = 0; j < CHUNK_SIZE; ++j)
                        chunks[i][j] = other.chunks[i][j];
                } else {
                    chunks[i] = nullptr;
                }
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        int pos = count % CHUNK_SIZE;
        if (count != 0 && pos == 0)
            ensureBackSpace();
        chunks[backIndex][pos] = value;
        if (pos == CHUNK_SIZE - 1)
            backIndex++;
        count++;
    }

    void push_front(const T& value) {
        if (count != 0 && count % CHUNK_SIZE == 0)
            ensureFrontSpace();
        if (count == 0) {
            chunks[frontIndex][0] = value;
        } else {
            if (count % CHUNK_SIZE == 0)
                frontIndex--;
            chunks[frontIndex][CHUNK_SIZE - (count % CHUNK_SIZE) - 1] = value;
        }
        count++;
    }

    void pop_back() {
        if (count > 0) {
            count--;
            if (count % CHUNK_SIZE == 0)
                backIndex--;
        }
    }

    void pop_front() {
        if (count > 0) {
            count--;
            if (count % CHUNK_SIZE == 0)
                frontIndex++;
        }
    }

    int size() const {
        return count;
    }

    int capacity_info() const {
        return capacity * CHUNK_SIZE;
    }

    T& front() {
        return chunks[frontIndex][0];
    }

    T& back() {
        return chunks[backIndex][(count - 1) % CHUNK_SIZE];
    }
};
