#define windows

#ifdef windows
#include <windows.h>
#endif

#ifndef windows
#include <unistd.h>
#endif

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::max;
using std::min;
using std::set;
using std::string;
using std::swap;
using std::vector;