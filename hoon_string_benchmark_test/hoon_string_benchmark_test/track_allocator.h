#ifndef _track_alloc
#define _track_alloc

#include "alloc_log.h"
#include <memory>
#include <limits>

template<class T>
class TrackAllocator
{
public:
    // log output stream ********************************
    
    static std::unique_ptr<std::ostream> out;
    
    template <class OSType, class ... Args>
    static
    void
    make_output_stream(Args&& ... args)
    {
        out.reset(new OSType(std::forward<Args>(args)...));
    }
    
    // ******************************** log output stream

    // aliases ******************************************
    
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    
    // ****************************************** aliases
    
    // helper classes ***********************************
    
    template <class U>
    struct rebind
    {
        using other = TrackAllocator<U>;
    };
    
    // *********************************** helper classes
    
    // constructors *************************************
    
    constexpr
    TrackAllocator() noexcept = default;
    
    constexpr
    TrackAllocator(const std::allocator<T>&) noexcept {}
    
    constexpr
    TrackAllocator(const TrackAllocator&) noexcept = default;
    
    template <class U>
    constexpr
    TrackAllocator(const TrackAllocator<U>&) noexcept {}
    
    // assignment operators *****************************
    
    constexpr
    TrackAllocator&
    operator=(const TrackAllocator&) noexcept = default;
    
    template <class U>
    constexpr
    TrackAllocator&
    operator=(const TrackAllocator<U>&) noexcept
    { return *this; }
    
    // ***************************** assignment operators
    
    // destructor ***************************************
    
    ~TrackAllocator() = default;
    
    // *************************************** destructor
    
    // memory managing **********************************
    
    [[nodiscard]]
    auto
    allocate(size_type n)
    {
        if (std::numeric_limits<size_type>::max()
            / sizeof(T) < n)
            throw std::bad_array_new_length{};
            
        const size_type sz = n * sizeof(T);
        
        if (auto ret = static_cast<T*>(std::malloc(sz)))
        {
            if (out) _alloc_memlog(*out, ret, sz);
            else _alloc_memlog(ret, sz);
            
            return ret;
        }
            
        throw std::bad_alloc{};
    }
    
    void
    deallocate(T* ptr, size_type n) noexcept
    {
        const size_type sz = n * sizeof(T);
        
        std::free(ptr);
        
        if (out) _dealloc_memlog(*out, ptr, sz);
        else _dealloc_memlog(ptr, sz);
    }
    
    // ********************************** memory managing
};

template <class T>
std::unique_ptr<std::ostream> TrackAllocator<T>::out;

#endif