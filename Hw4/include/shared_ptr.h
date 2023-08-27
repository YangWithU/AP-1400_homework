#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
public:
    SharedPtr();
    explicit SharedPtr(T*);
    SharedPtr(SharedPtr&);
    ~SharedPtr();

    SharedPtr& operator=(SharedPtr&);

    T operator*() const;
    T* operator->() const;
    explicit operator bool();

    T* get();
    std::size_t use_count();

    void reset();
    void reset(T*);

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
T* SharedPtr<T>::operator->() const {
    return base_ptr;
}

template <typename T>
SharedPtr<T>::operator bool() {
    return base_ptr != nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr& rhs) {
    if(this != &rhs) {
        (*rhs.ref_counter) += 1;
        this->ref_counter = rhs.ref_counter;
        this->base_ptr = rhs.base_ptr;
    }
    return *this;
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

template <typename T>
void SharedPtr<T>::reset() {
    delete base_ptr;
    base_ptr = nullptr;
    delete ref_counter;
    ref_counter = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T *rhs) {
    delete base_ptr;
    delete ref_counter;
    base_ptr = rhs;
    ref_counter = new std::size_t {1};
}

#endif //SHARED_PTR