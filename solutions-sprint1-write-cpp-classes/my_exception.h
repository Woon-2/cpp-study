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
        ([_val = _fw(val), _lo = _fw(lo), _hi = _fw(hi), _expr = _fw(expr), _file = __FILE__, _line = __LINE__, _func = __FUNCTION_NAME__]() \
        { \
            if (std::clamp((_val), (_lo), (_hi)) != (_val)) \
                throw std::out_of_range{_FMT("in %s:%d:%s:\n%s\n", _file, _line, _func, _expr)}; \
            return _val; \
        }())
    #else
        #define debug_check_out_of_range(val, ...) (val)
    #endif
    
#endif