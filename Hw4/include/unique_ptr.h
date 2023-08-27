#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <iostream>
#include <memory>
#include <string>

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* p);
    UniquePtr();
    ~UniquePtr();

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&&) noexcept;

    T& operator*() const;
    T* operator->() const;
    explicit operator bool();

    T* get();
    void reset();
    void reset(T*);
    T* release();

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
T& UniquePtr<T>::operator*() const {
    return *base_ptr;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
    return base_ptr;
}

template <typename T>
UniquePtr<T>::operator bool() {
    return base_ptr != nullptr;
}

template <typename T>
T* UniquePtr<T>::get() {
    return base_ptr;
}

template <typename T>
void UniquePtr<T>::reset() {
    delete base_ptr;
    base_ptr = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T *rhs) {
    delete base_ptr;
    base_ptr = rhs;
}

// transfer access
template <typename T>
T* UniquePtr<T>::release() {
    T* tmp = base_ptr;
    base_ptr = nullptr;
    return tmp;
}

// using perfect forwarding to properly forward all parameters
template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif //UNIQUE_PTR