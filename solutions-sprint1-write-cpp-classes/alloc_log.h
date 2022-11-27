#ifndef _alloc_log
#define _alloc_log

#include <iostream>
#include <cstdlib>

void _memlog(void* ptr, const char* modifying_memory_expr)
{
    std::cout << modifying_memory_expr << " in [" << ptr << "]\n";
    std::cout.width(4);
}

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

void __memlog_print_memsize(std::size_t sz)
{
    std::cout.width(4);
    std::cout << ": ";
    std::cout << sz;
    std::cout.width(0);
    std::cout << " bytes\n";
}

void _alloc_memlog(void* ptr)
{
    std::cout.width(4);
    std::cout << '(' << _get_and_inc_alloc_cnt() << ") - ";
    _memlog(ptr, "Allocation");
}

void _alloc_memlog(void* ptr, std::size_t sz)
{
    _alloc_memlog(ptr);
    __memlog_print_memsize(sz);
}

void _dealloc_memlog(void* ptr)
{
    std::cout.width(4);
    std::cout << '(' << _get_and_inc_dealloc_cnt() << ") - ";
    _memlog(ptr, "Deallocation");
}

void _dealloc_memlog(void* ptr, std::size_t sz)
{
    _dealloc_memlog(ptr);
    __memlog_print_memsize(sz);
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

#endif