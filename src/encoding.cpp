#include "encoding.h"

// https://stackoverflow.com/questions/3074776/how-to-convert-char-array-to-wchar-t-array
std::wstring enc_char_to_wstring(const char* text) {
    if (!text) return L"";

#ifdef _WIN32
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, text, -1, nullptr, 0);
    if (size_needed == 0) {
        std::wcerr << L"Ошибка при выполнении функции MultiByteToWideChar" << std::endl;
        exit(1);
    }

    std::wstring wstr(size_needed - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text, -1, &wstr[0], size_needed);
    return wstr;

#else
    if (!setlocale(LC_ALL, "ru_RU.utf8") &&
        !setlocale(LC_ALL, "en_US.utf8")) {
        std::wcerr << L"UTF-8 локаль не найдена" << std::endl;
        exit(1);
    }

    size_t needed = mbstowcs(nullptr, text, 0);
    if (needed == static_cast<size_t>(-1)) {
        std::wcerr << L"Некорректная последовательность UTF-8" << std::endl;
        exit(1);
    }

    std::wstring wstr(needed, L'\0');
    mbstowcs(&wstr[0], text, needed);
    return wstr;
#endif
}

std::string enc_wstring_to_string(const std::wstring& wstr) {
#ifdef _WIN32
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int) wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int) wstr.size(), &str[0], size_needed, nullptr, nullptr);
    return str;
#else
    size_t len = wcstombs(nullptr, wstr.c_str(), 0);
    std::string str(len, 0);
    wcstombs(&str[0], wstr.c_str(), len);
    return str;
#endif
}
