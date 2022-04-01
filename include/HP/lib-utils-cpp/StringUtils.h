// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <string>

namespace HP {
namespace Utils {

    std::wstring astringToWstring(const std::string& str);

    /*! @brief A char-by-char copy of the wchar to narrow char.
     *
     *  Checks to make sure the chars going in are part of the ASCII character set
     */
    std::string wstringToAstringChecked(const std::wstring& wstr);

    /*! @brief A char-by-char copy of the wchar to narrow char.
     *
     *  Although the function is marked as unchecked, nothing bad happens except the
     *   string may be unintelligable to a human.
     */
    std::string wstringToAstringUnchecked(const std::wstring& wstr);

    /*! @brief Evaluates whether or not all the wchars will 'fit' into narrow chars*/
    bool isWstringToAstringSafe(const std::wstring& wstr);

    /*! @brief Trim the leading and trailing whitespace from a string */
    std::string trim(const std::string& str);

    std::string wstringToUtf8String(const std::wstring& str);

    std::wstring utf8StringToWstring(const std::string& str);

}
}
