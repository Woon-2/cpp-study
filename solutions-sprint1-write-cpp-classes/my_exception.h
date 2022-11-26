// if this header is included by a source,
// undef_macros.inl also should be included in the end of the source.

/**
 * @brief   checks if a value is in a specific range when _DEBUG macro is defined
 * @param   val     the value which will be checked
 * @param   lo      lower limit of the range
 * @param   hi      higher limit of the range
 * @param   expr    expression which will be forwarded to std::out_of_range
 * 
 * if val is not in [lo, hi] then throws std::out_of_range with expr
*/
#ifndef debug_check_out_of_range

#include "my_format.h"
#include <algorithm>
#include <type_traits>

    #define _fw(val) std::forward<std::remove_reference_t<decltype(val)>>(val)

    #ifdef _DEBUG
        #define debug_check_out_of_range(val, lo, hi, expr) \
            __check_out_of_range(val, lo, hi, __FILE__, __LINE__, __FUNCTION_NAME__, expr)
    #else
        #define debug_check_out_of_range(val, ...) (val)
    #endif
    
template <class T>
const T&
__check_out_of_range(const T& val, const T& lo, const T& hi,
                     const char* file, decltype(__LINE__) line,
                     const char* func, const char* expr)
{
    if (std::clamp(val, lo, hi) != val)
        throw std::out_of_range{_FMT("in %s:%d:%s:\n%s\n", file, line, func, expr)};
    return val;
}
    
#endif