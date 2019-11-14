#pragma once

#include <vector>
#include <string>

std::vector< size_t > FindSubString( const std::string& text, const std::string& pattern )
{
    std::vector<size_t> res;
    if( text.size() < pattern.size() )
        return res;

    size_t countStep = text.size() - pattern.size() + 1;
    for( size_t i = 0; i < countStep; ++i )
    {
        bool founded = true;
        for( size_t j = pattern.size(); j != 0; --j )
        {
            if( text[i + j - 1] != pattern[j - 1] )
            {
                founded = false;
                break;
            }
        }
        if( founded )
            res.push_back( i );
    }

    return res;
}