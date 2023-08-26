#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <iostream>
#include <memory>

template <typename T>
class UniquePtr {
public:
    UniquePtr(T* p);
    UniquePtr();
    ~UniquePtr();

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&&) noexcept;
    T* get();

private:
    T* base_ptr;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* p) : base_ptr(p) {}

template <typename T>
UniquePtr<T>::UniquePtr() : base_ptr(nullptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete base_ptr;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T> && rhs) noexcept : base_ptr(rhs.base_ptr) {
    rhs.base_ptr = nullptr;
}

template <typename T>
T* UniquePtr<T>::get() {
    return base_ptr;
}

// using perfect forwarding to properly forward all parameters
template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif //UNIQUE_PTR