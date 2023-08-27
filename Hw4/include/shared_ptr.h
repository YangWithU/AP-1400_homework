#ifndef SHARED_PTR
#define SHARED_PTR

//template <typename T>

template <typename T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T*);
    ~SharedPtr();

private:
    T* base_ptr;
    std::size_t ref_counter;
};

template <typename T>
SharedPtr<T>::SharedPtr() : base_ptr(nullptr), ref_counter(0) {}

template <typename T>
SharedPtr<T>::SharedPtr(T *p) {

}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    delete base_ptr;
    ref_counter = 0;
}

#endif //SHARED_PTR