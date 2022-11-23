#ifndef _alloc_log
#define _alloc_log

#include <iostream>
#include <cstdlib>

void* operator new(std::size_t sz)
{
    static std::size_t alloc_cnt = 0;
    
    if (sz == 0)
        ++sz;
        
    if (void* ptr = std::malloc(sz))
    {
        std::cout.width(4);
        std::cout << '(' << ++alloc_cnt << ") - ";
        std::cout << "Allocation in [" << ptr << "] : ";
        std::cout.width(4);
        std::cout << sz;
        std::cout.width(0);
        std::cout << " bytes\n";
    
        return ptr;
    }
    
    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept
{
    static std::size_t dealloc_cnt = 0;
    
    std::cout.width(4);
    std::cout << '(' << ++dealloc_cnt << ") - ";
    std::cout << "Deallocation in [" << ptr << "]\n";
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