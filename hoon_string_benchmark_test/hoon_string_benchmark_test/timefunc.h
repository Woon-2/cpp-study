#ifndef _timefunc
#define _timefunc

#if __cplusplus >= 201703L

#include <variant>

#endif  // C++17

#if __cplusplus >= 201103L

#include <chrono>
#include <utility>

#endif  // C++11

#include <iostream>


#if __cplusplus >= 201103L

// returns std::pair
// first: return value of function
// second: elapsed time
template<class Time_t = std::chrono::milliseconds,
         class FPTime_t = std::chrono::duration<
            float, typename Time_t::period>,
         class Func, class ... Args>
auto
timefunc(Func func, Args&& ... args)
    -> std::pair<decltype(func(std::forward<Args>(args)...)),
                 FPTime_t>
{
    using std::chrono::system_clock;

    auto tp = system_clock::now();

    return { func(std::forward<Args>(args)...),
             system_clock::now() - tp };
}

// returns std::duration<float, typename Time_t::period>
// return value: elapsed time
template<class Time_t = std::chrono::milliseconds,
         class FPTime_t = std::chrono::duration<
            float, typename Time_t::period>,
         class Func, class ... Args>
FPTime_t
timefunc_noreturn(Func func, Args&& ... args)
{
    using std::chrono::system_clock;

    auto tp = system_clock::now();

    func(std::forward<Args>(args)...);

    return system_clock::now() - tp;
}

#else   // C++11

template <class ... _>
void
timefunc(_&& ...)
{
    static_assert(false,
        "timefunc is a C++11 extension");
}

#endif // C++11

#if __cplusplus >= 202002L

template <class Time_t = std::chrono::milliseconds,
          class CharT, class Traits, class Func, class ... Args>
decltype(auto)
run_and_print_elapsed_time(std::basic_ostream<CharT, Traits>& os,
                           Func func, Args&& ... args)
{
    auto [ret, elapsed] =
        timefunc<Time_t>(func, std::forward<Args>(args)...);
        
    os << elapsed << " elapsed\n";
    
    return std::forward<decltype(ret)>(ret);
}

template <class Time_t = std::chrono::milliseconds,
          class CharT, class Traits, class Func, class ... Args>
void
run_and_print_elapsed_time_noreturn(
    std::basic_ostream<CharT, Traits>& os,
    Func func, Args&& ... args)
{
    os << timefunc_noreturn<Time_t>(func,
        std::forward<Args>(args)...);
}

#elif __cplusplus >= 201103L    // C++20

template <class _>
constexpr const char* __time_suffix();

template <>
constexpr const char* __time_suffix<std::chrono::nanoseconds>()
{
    return "ns";
}

template <>
constexpr const char* __time_suffix<std::chrono::microseconds>()
{
    return "us";
}

template <>
constexpr const char* __time_suffix<std::chrono::milliseconds>()
{
    return "ms";
}

template <>
constexpr const char* __time_suffix<std::chrono::seconds>()
{
    return "s";
}

template <>
constexpr const char* __time_suffix<std::chrono::minutes>()
{
    return "m";
}

template <>
constexpr const char* __time_suffix<std::chrono::hours>()
{
    return "h";
}

template <class Time_t = std::chrono::milliseconds,
          class CharT, class Traits, class Func, class ... Args>
auto
run_and_print_elapsed_time(std::basic_ostream<CharT, Traits>& os,
                           Func func, Args&& ... args)
    -> decltype(func(std::forward<Args>(args)...))
{
    auto ret_and_time = timefunc<Time_t>(
        func, std::forward<Args>(args)...);
    
    os << ret_and_time.second.count() << __time_suffix<Time_t>()
        << " elapsed\n";
        
    return std::forward<decltype(ret_and_time.first)>(
            ret_and_time.first);
}

template <class Time_t = std::chrono::milliseconds,
          class CharT, class Traits, class Func, class ... Args>
void
run_and_print_elapsed_time_noreturn(
    std::basic_ostream<CharT, Traits>& os,
    Func func, Args&& ... args)
{
    
    os << timefunc_noreturn<Time_t>(
        func, std::forward<Args>(args)...).count()
        << __time_suffix<Time_t>() << " elapsed\n";
}

#else   // C++20, C++11

template <class ... _>
void
run_and_print_elapsed_time(_&& ...)
{
    static_assert(false,
        "run_and_print_elapsed_time is a C++11 extension");
}

template <class ... _>
void
run_and_print_elapsed_time_noreturn(_&& ...)
{
    static_assert(false,
        "run_and_print_elapsed_time is a C++11 extension");
}

#endif  // C++20, C++11

#if __cplusplus >= 201103L

template <class Time_t = std::chrono::milliseconds,
          class Func, class ... Args>
auto
run_and_print_elapsed_time(Func func, Args&& ... args)
    -> decltype(func(std::forward<Args>(args)...))
{
    return run_and_print_elapsed_time(std::cout, func,
        std::forward<Args>(args)...);
}

template <class Time_t = std::chrono::milliseconds,
          class Func, class ... Args>
void
run_and_print_elapsed_time_noreturn(Func func, Args&& ... args)
{
    run_and_print_elapsed_time_noreturn(std::cout, func,
        std::forward<Args>(args)...);
}

#endif  // C++11

#endif // _timefunc