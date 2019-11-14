#pragma once

#include <cstdint>

#include <limits>
#include <array>
#include <vector>
#include <string>

const size_t sizeAlphabet = ( std::numeric_limits<char>::max )( );

std::array< std::vector< intptr_t >, sizeAlphabet > BadCharacterTable( const std::string& pattern )
{
    std::array< std::vector< intptr_t >, sizeAlphabet > table;
    table.fill( std::vector< intptr_t >( pattern.size() + 1, -1 ) );
    if( pattern.empty() )
        return table;

    std::array< intptr_t, sizeAlphabet > support;
    support.fill( -1 );

    for( size_t i = 0; i < pattern.size(); ++i )
    {
        support[pattern[i]] = i;
        for( size_t j = 0; j < pattern.size(); ++j )
            table[j][j + 1] = support[j];
    }

    return table;
}

std::vector< intptr_t > BadCharacterVariant( const std::string& pattern )
{
    const size_t sizeAlphabet = ( std::numeric_limits<char>::max )( );
    std::vector< intptr_t > table( sizeAlphabet, pattern.size() );
    if( pattern.size() < 2 )
        return table;

    for( size_t i = 0; i < pattern.size() - 1; ++i )
    {
        table[pattern[i]] = pattern.size() - 1 - i;
    }

    return table;
}

size_t MatchLength( const std::string& pattern, size_t i, size_t j )
{
    if( i == j )
        return pattern.size() - i;

    size_t matchLength = 0;
    for( ; i < pattern.size() && j < pattern.size() && pattern[i] == pattern[j]; ++i, ++j )
        matchLength += 1;
    return matchLength;
}

std::vector< intptr_t > FindPrefixes( const std::string& pattern )
{
    std::vector< intptr_t > Z( pattern.size(), 0 );
    if( pattern.empty() )
        return Z;

    for( size_t i = 0; i < pattern.size(); ++i )
    {
        for( size_t j = 0; i + j < pattern.size(); ++j )
        {
            if( pattern[i + j] == pattern[j] )
            {
                Z[i] += 1;
            }
            else
                break;
        }
    }

    return Z;
}

std::vector< intptr_t > GoodSuffixTable( const std::string& pattern )
{
    std::vector< intptr_t > L( pattern.size(), -1 );

    std::string revPattern = pattern;
    std::reverse( revPattern.begin(), revPattern.end() );
    auto Z = FindPrefixes( revPattern );
    std::reverse( Z.begin(), Z.end() );
    auto Z2 = FindPrefixes( pattern );
    for( size_t j = 0; j < pattern.size(); ++j )
    {
        auto i = pattern.size() - Z[j];
        if( i != pattern.size() )
            L[i] = j;
    }

    return L;
}

std::vector< intptr_t > FullShiftTable( const std::string& pattern )
{
    std::vector< intptr_t > F( pattern.size(), 0 );
    auto Z = FindPrefixes( pattern );
    std::reverse( Z.begin(), Z.end() );
    intptr_t longest = { 0 };
    for( size_t i = 0; i < pattern.length(); ++i )
    {
        if( Z[i] == i + 1 )
        {
            longest = ( std::max )( Z[i], longest );
        }
        else
        {
            longest = i;
        }
        F[i] = longest;
    }

    return F;
}