#pragma once

#include <cstdint>

#include <vector>
#include <string>

#include "Utilites.h"

std::vector<size_t> BoyerMooreHorspe( const std::string& text, const std::string& pattern )
{
    std::vector<size_t> matches;
    if( text.length() < pattern.length() )
        return matches;

    auto preprocessed = BadCharacterVariant( pattern );

    size_t shift = 0;
    while( shift < text.length() - pattern.length() + 1 )
    {
        intptr_t j = pattern.length() - 1;
        while( j >= 0 && text[shift + j] == pattern[j] )
            j -= 1;
        if( j < 0 )
        {
            matches.push_back( shift );
            shift += 1;
        }
        else
        {
            if( j != pattern.length() - 1 )
                shift += preprocessed[pattern.back()];
            else
                shift += preprocessed[text[shift + j]];
        }
    }

    return matches;
}
