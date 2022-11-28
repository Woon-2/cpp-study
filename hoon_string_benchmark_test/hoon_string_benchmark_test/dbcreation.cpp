#include "constants.h"

#include <random>
#include <fstream>
#include <iostream>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<> uid_alpha(MinAlpha, MaxAlpha);
std::uniform_int_distribution<> uid_len(MinLen, MaxLen);

int main()
{
    std::ios::sync_with_stdio(false);
    
    std::ofstream out{"DB.db"};
    
    for (auto row_cnt = RowCnt; row_cnt--;)
    {
        for (auto col_cnt = ColCnt; col_cnt--;)
        {
            const auto len = uid_len(dre);
            
            for (auto rest_chars = len; rest_chars--;)
            {
                out.put(static_cast<char>(uid_alpha(dre)));
            }
            
            out.put(Delim);
        }
        
        out.put('\n');
    }
}