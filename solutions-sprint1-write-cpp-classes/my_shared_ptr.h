#ifndef _my_shared_ptr
#define _my_shared_ptr

#include "my_unique_ptr.h"
#include <type_traits>

template <class T>
class my_shared_ptr
{
public:
    constexpr my_shared_ptr() noexcept;
    constexpr my_shared_ptr(std::nullptr_t) noexcept;
    template <class Y>
    explicit my_shared_ptr(Y*);
    my_shared_ptr(const my_shared_ptr&) noexcept;
    template <class Y>
    my_shared_ptr(const my_shared_ptr<Y>&) noexcept;
    my_shared_ptr(my_shared_ptr&&) noexcept;
    template <class Y>
    my_shared_ptr(my_shared_ptr<Y>&&) noexcept;
    template <class Y>
    my_shared_ptr(my_unique_ptr<Y>&&);

    my_shared_ptr& operator=(const my_shared_ptr&) noexcept;
    template <class Y>
    my_shared_ptr& operator=(const my_shared_ptr<Y>&) noexcept;
    my_shared_ptr& operator=(my_shared_ptr&&) noexcept;
    template <class Y>
    my_shared_ptr& operator=(my_shared_ptr<Y>&&) noexcept;
    template <class Y>
    my_shared_ptr& operator=(my_unique_ptr<Y>&&);
    
    ~my_shared_ptr() noexcept;
    
    T* const operator->() const noexcept;
    T& operator*() const noexcept(noexcept(*std::declval<T>()));
    T* const get() const noexcept;
    
    explicit operator bool() const noexcept;

private:
    static std::size_t* make_refs();
    void invalidate() noexcept;
    void copy_ptr_and_refs(const my_shared_ptr&) noexcept;
    void copy_ptr_and_refs(my_shared_ptr&&) noexcept;
    template <class Y>
    void copy_ptr_and_refs(const my_shared_ptr<Y>&) noexcept;
    template <class Y>
    void copy_ptr_and_refs(my_shared_ptr<Y>&&) noexcept;
    void inc_if_refs_valid() noexcept;
    void dec_or_free_refs_if_refs_valid() noexcept;

    T* ptr;
    std::size_t* refs;
};

#include "my_shared_ptr.inl"

#endif