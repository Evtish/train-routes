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

std::wstring enc_char_to_wstring(const char *text);
std::string enc_wstring_to_string(const std::wstring& wstr);
