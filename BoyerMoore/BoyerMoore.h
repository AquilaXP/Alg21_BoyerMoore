#pragma once

#include <vector>
#include <string>

#include "Utilites.h"

std::vector< size_t > BoyerMoore( const std::string& text, const std::string& pattern )
{
    std::vector<size_t> matches;
    if( text.size() < pattern.size() )
        return matches;

    auto BC = BadCharacterVariant( pattern );
    auto L = GoodSuffixTable( pattern );
    auto F = FullShiftTable( pattern );

    size_t shift = 0;
    intptr_t i = 0;
    while( shift < text.size() - pattern.size() + 1 )
    {
        i = pattern.size() - 1;
        while( i >= 0 && pattern[i] == text[shift + i] )
            i -= 1;
        // Нашли
        if( i == -1 )
        {
            matches.push_back( shift );
            shift += 1;
        }
        else
        {
            // Пытаемся максимизировать сдвиг
            intptr_t char_shift = 0;
            if( i != pattern.length() - 1 )
                char_shift += BC[pattern.back()];
            else
                char_shift += BC[text[shift + i]];

            intptr_t suffix_shift = 0;
            if( i + 1 == pattern.size() )
                suffix_shift = 1;
            else if( L[i + 1] == -1 )
            {
                suffix_shift = pattern.size() - F[i + 1];
            }
            else
            {
                suffix_shift = pattern.size() - L[i + 1] - 1;
            }
            auto max_shift = ( std::max )( char_shift, suffix_shift );
            shift += max_shift;
        }
    }
    return matches;
}