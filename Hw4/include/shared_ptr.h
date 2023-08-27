#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
public:
    SharedPtr();
    explicit SharedPtr(T*);
    SharedPtr(SharedPtr&);
    ~SharedPtr();

    T operator*() const;
    T* get();
    std::size_t use_count();

private:
    T* base_ptr{};
    std::size_t* ref_counter{};
};

template <typename T>
SharedPtr<T>::SharedPtr() : base_ptr(nullptr), ref_counter(new std::size_t {1}) {}

template <typename T>
SharedPtr<T>::SharedPtr(T *p) : base_ptr(p), ref_counter(new std::size_t {1}) {}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr &rhs) {
    (*rhs.ref_counter) += 1;
    this->ref_counter = rhs.ref_counter;
    this->base_ptr = rhs.base_ptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if(ref_counter == nullptr) return;
    else if(*ref_counter == 0) {
        delete ref_counter;
        ref_counter = nullptr;
    } else {
        (*ref_counter) -= 1;
        if(*ref_counter == 0) {
            delete base_ptr;
            base_ptr = nullptr;
            delete ref_counter;
            ref_counter = nullptr;
        }
    }
}

template <typename T>
T SharedPtr<T>::operator*() const {
    return *base_ptr;
}

template <typename T>
T* SharedPtr<T>::get() {
    return base_ptr;
}

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
std::size_t SharedPtr<T>::use_count() {
    if(ref_counter == nullptr) return 0;
    return *ref_counter;
}

#endif //SHARED_PTR