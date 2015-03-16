#ifndef __COMMON_STL_H__
#define __COMMON_STL_H__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>

using namespace std;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef double float64;

#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a<b?b:a)


#define DebugLogCPP(s,...) GameUtilities::LogMessage(__FILE__,__LINE__,s,##__VA_ARGS__);

#define DebugLog( s, ... ) NSLog( @"<%@:(%d)> %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:(s), ##__VA_ARGS__] )


#endif /* __COMMON_STL_H__ */
