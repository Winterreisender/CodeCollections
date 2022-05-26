/**
 * @file bv2av.cpp
 * @author Winterreisender
 * @version 1.0
 * @license Apache-2.0
 * @note Algorithm is postponed by mcfx under WTFPL license 
*/

#include "bv2av.hpp"
using namespace std;

/*
#include <algorithm>
template<typename T> 
    concept Integral = is_integral<T>::value;


Integral auto readByRadix(string src, int radix)
{
    Integral auto r  = 0, curBase = 1;

    reverse(src.begin(), src.end());
    
    for(char& i : src )
    {
        r += (i-'0') * curBase;
        curBase *= radix; 
    }
    return r;
}

*/

inline int lookup(const char& c, const char* dict)
{
    int i = 0;
    for( ; dict[i] != '\0' && dict[i] != c ; ++i);
    return i;
}


string av2bv(const char* av)
{
    const char* alphabet = "fZodR9XQDSUm21yCkr6zBqiveYah8bt4xsWpHnJE7jL5VG3guMTKNPAwcF";
    const int   s[]      = {11,10,3,8,4,6};
    const u64   xorVal   = 0xA93B324ull ;
    const u64   addVal   = 8728348608ull;

    u64 x = atoll(av + 2);
    x = (x^xorVal) + addVal;
    string r = "BV1  4 1 7  ";

    u64 base = 1;
    for(int i=0 ; i < 6; ++i, base *= 58)
    {
        r[ s[i] ] = alphabet[ x / base % 58 ];
    }

    return r;
}


string bv2av(const char* inputBV)
{
    const char* alphabet = "fZodR9XQDSUm21yCkr6zBqiveYah8bt4xsWpHnJE7jL5VG3guMTKNPAwcF";
    const int   s[]      = {11,10,3,8,4,6};
    const u64   xorVal   = 0xA93B324ull ;
    const u64   addVal   = 8728348608ull;

    auto bv = inputBV;
    u64 r = 0, base = 1;
    for(int i=0; i < 6; ++i)
    {
        r += lookup(bv[ s[i] ], alphabet) * base;
        base *= 58;
    }

    string avHead = "av";
    return avHead + to_string(r-addVal ^ xorVal);
}

