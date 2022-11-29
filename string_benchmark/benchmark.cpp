#include "track_allocator.h"
#include "timefunc.h"

#include "constants.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using string = std::basic_string<char, std::char_traits<char>,
    TrackAllocator<char>>;
    
template <typename T>
using vector = std::vector<T, TrackAllocator<T>>;

using CellType = string;           // 1. std::string
// using CellType = vector<char>;  // 2. std::vector<char>

using CellDB = vector<std::array<CellType, ColCnt>>;

CellDB loadDB(const std::string& file_path)#include "track_allocator.h"
#include "timefunc.h"

#include "constants.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using string = std::basic_string<char, std::char_traits<char>,
    TrackAllocator<char>>;
    
template <typename T>
using vector = std::vector<T, TrackAllocator<T>>;

using CellType = string;           // 1. std::string
// using CellType = vector<char>;  // 2. std::vector<char>

using CellDB = vector<std::array<CellType, ColCnt>>;

template<class _CharT, class _Traits, class Cont>
std::basic_istream<_CharT, _Traits>&
getline(std::basic_istream<_CharT, _Traits>& __in,
    Cont& __str, _CharT __delim)
{
    typedef std::basic_istream<_CharT, _Traits>		__istream_type;
    typedef Cont	                                __string_type;
    typedef typename __istream_type::ios_base       __ios_base;
    typedef typename __istream_type::int_type	    __int_type;
    typedef typename __string_type::size_type	    __size_type;

    __size_type __extracted = 0;
    const __size_type __n = 1'000'000'000;
    typename __ios_base::iostate __err = __ios_base::goodbit;
    typename __istream_type::sentry __cerb(__in, true);
    if (__cerb)
    {
	    try
	    {
	      __str.clear();
	      const __int_type __idelim = _Traits::to_int_type(__delim);
	      const __int_type __eof = _Traits::eof();
	      __int_type __c = __in.rdbuf()->sgetc();

	      while (__extracted < __n
		     && !_Traits::eq_int_type(__c, __eof)
		     && !_Traits::eq_int_type(__c, __idelim))
		{
		  __str.push_back(_Traits::to_char_type(__c));
		  ++__extracted;
		  __c = __in.rdbuf()->snextc();
		}

	      if (_Traits::eq_int_type(__c, __eof))
		__err |= __ios_base::eofbit;
	      else if (_Traits::eq_int_type(__c, __idelim))
		{
		  ++__extracted;		  
		  __in.rdbuf()->sbumpc();
		}
	      else
		__err |= __ios_base::failbit;
	    }
	    catch(...)
	    {
	      __in.setstate(__ios_base::badbit);
	    }
	}
      if (!__extracted)
	__err |= __ios_base::failbit;
      if (__err)
	__in.setstate(__err);
      return __in;
}

CellDB loadDB(const std::string& file_path)
{
    std::ifstream in(file_path);
    
    if (!in)
    {
        std::cout << "cannot open file \"" << file_path << "\"\n";
        std::abort();
    }
    
    CellDB ret(RowCnt);
    
    for (auto i = RowCnt & 0; i < RowCnt; ++i)
    {
        for (auto j = ColCnt & 0; j < ColCnt; ++j)
        {
            ret[i][j].reserve(MinLen);
            getline(in, ret[i][j], Delim);
        }
    }
    
    return ret;
}

int main()
{
    TrackAllocator<char>::make_output_stream<std::ofstream>("memlog.txt");
    
    run_and_print_elapsed_time_noreturn(loadDB, "DB.db");
}