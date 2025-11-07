#include "encoding.h"

// https://stackoverflow.com/questions/3074776/how-to-convert-char-array-to-wchar-t-array
// wstring char_to_wstring(const char *text) {
//     const size_t size = strlen(text);
//     wstring wstr;
//     if (size > 0) {
//         wstr.resize(size);
//         mbstowcs(&wstr[0], text, size);
//     }
//     return wstr;
// }

wstring char_to_wstring(const char* text) {
    if (!text) return L"";

#ifdef _WIN32
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, text, -1, nullptr, 0);
    if (size_needed == 0) {
        throw runtime_error("MultiByteToWideChar failed");
    }

    wstring wstr(size_needed - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text, -1, &wstr[0], size_needed);
    return wstr;

#else
    if (!setlocale(LC_CTYPE, "en_US.utf8") &&
        !setlocale(LC_CTYPE, "ru_RU.utf8")) {
        wcerr << L"UTF-8 локаль не найдена" << endl;
        exit(1);
    }

    size_t needed = mbstowcs(nullptr, text, 0);
    if (needed == static_cast<size_t>(-1)) {
        wcerr << L"Некорректная последовательность UTF-8" << endl;
        exit(1);
    }

    wstring wstr(needed, L'\0');
    mbstowcs(&wstr[0], text, needed);
    return wstr;
#endif
}

// std::wstring string_to_wstring(const char* str)
// {
//     if (!str) return L"";
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
//     return conv.from_bytes(str);
// }

string wstring_to_string(const wstring& wstr) {
#ifdef _WIN32
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int) wstr.size(), nullptr, 0, nullptr, nullptr);
    string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int) wstr.size(), &str[0], size_needed, nullptr, nullptr);
    return str;
#else
    size_t len = wcstombs(nullptr, wstr.c_str(), 0);
    string str(len, 0);
    wcstombs(&str[0], wstr.c_str(), len);
    return str;
#endif
}
