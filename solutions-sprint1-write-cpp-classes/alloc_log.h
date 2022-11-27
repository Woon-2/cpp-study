#ifndef _alloc_log
#define _alloc_log

#include <iostream>
#include <cstdlib>
#include <string>

std::size_t _get_and_inc_alloc_cnt()
{
    static std::size_t alloc_cnt = 0;
    return ++alloc_cnt;
}

std::size_t _get_and_inc_dealloc_cnt()
{
    static std::size_t dealloc_cnt = 0;
    return ++dealloc_cnt;
}

template <class CharT, class Traits>
void _memlog(std::basic_ostream<CharT, Traits>& os,
             void* const ptr,
             const char* modifying_memory_expr)
{
    os << modifying_memory_expr << " in [" << ptr << "]\n";
    os.width(4);
}

template <class CharT, class Traits>
void __memlog_print_memsize(std::basic_ostream<CharT, Traits>& os,
                            std::size_t sz)
{
    os.width(4);
    os << ": ";
    os << sz;
    os.width(0);
    os << " bytes\n";
}

template <class CharT, class Traits>
void _alloc_memlog(std::basic_ostream<CharT, Traits>& os,
                   void* const ptr)
{
    os.width(4);
    os << '(' << _get_and_inc_alloc_cnt() << ") - ";
    _memlog(os, ptr, "Allocation");
}

template <class CharT, class Traits>
void _alloc_memlog(std::basic_ostream<CharT, Traits>& os,
                   void* const ptr, std::size_t sz)
{
    _alloc_memlog(os, ptr);
    __memlog_print_memsize(os, sz);
}

template <class CharT, class Traits>
void _dealloc_memlog(std::basic_ostream<CharT, Traits>& os,
                     void* const ptr)
{
    os.width(4);
    os << '(' << _get_and_inc_dealloc_cnt() << ") - ";
    _memlog(os, ptr, "Deallocation");
}

template <class CharT, class Traits>
void _dealloc_memlog(std::basic_ostream<CharT, Traits>& os,
                     void* const ptr, std::size_t sz)
{
    _dealloc_memlog(os, ptr);
    __memlog_print_memsize(os, sz);
}

void _alloc_memlog(void* const ptr)
{
    _alloc_memlog(std::cout, ptr);
}

void _alloc_memlog(void* const ptr, std::size_t sz)
{
    _alloc_memlog(std::cout, ptr, sz);
}

void _dealloc_memlog(void* const ptr)
{
    _dealloc_memlog(std::cout, ptr);
}

void _dealloc_memlog(void* const ptr, std::size_t sz)
{
    _dealloc_memlog(std::cout, ptr, sz);
}

void* operator new(std::size_t sz)
{
    if (sz == 0)
        ++sz;
        
    if (void* ptr = std::malloc(sz))
    {
        _alloc_memlog(ptr, sz);
        return ptr;
    }
    
    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept
{
    _dealloc_memlog(ptr);
    std::free(ptr);
}

void* operator new[](std::size_t sz)
{
    return ::operator new(sz);
}

void operator delete[](void* ptr) noexcept
{
    ::operator delete(ptr);
}

#endif  // _alloc_log