#pragma once

#include <cstdlib>
#include <cstring>
#include <clocale>
#include <cwchar>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <string>
#include <iostream>

using namespace std;

wstring char_to_wstring(const char *text);
string wstring_to_string(const wstring& wstr);
