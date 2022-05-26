/**
 * @file bv2av.hpp
 * @author Winterreisender
 * @version 1.0
 * @license Apache-2.0
 * @note The AV to BV algorithm is provided by mcfx under WTFPL license 
*/
#pragma once

#include <string>
using namespace std;

typedef uint64_t u64;

/**
 * @param av (const char*) av number with "av"
 * @return  (String) bv number with "BV"
*/
string av2bv(const char* av);

/**
 * @param  input (String) bv number with "BV"
 * @return (const char*) av number with "av"
*/
string bv2av(const char* input);