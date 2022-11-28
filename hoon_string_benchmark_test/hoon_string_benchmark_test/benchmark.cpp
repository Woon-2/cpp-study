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
            std::getline(in, ret[i][j], Delim);
        }
    }
    
    return ret;
}

int main()
{
    TrackAllocator<char>::make_output_stream<std::ofstream>("memlog.txt");
    
    run_and_print_elapsed_time_noreturn(loadDB, "DB.db");
}