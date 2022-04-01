// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <stdint.h>
#include <string>
#include <Windows.h>

namespace HP {
namespace Utils {

using SetThreadDescriptionFunction =  HRESULT(*)(HANDLE, PCWSTR);

struct WindowsVersion {
    uint32_t majorVersion;
    uint32_t minorVersion;
    uint32_t servicePackMajorVersion;
    uint32_t servicePackMinorVersion;

    WindowsVersion(uint32_t major, uint32_t minor, uint32_t spMajor, uint32_t spMinor);
};

const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)  
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.  
    LPCSTR szName; // Pointer to name (in user addr space).  
    DWORD dwThreadID; // Thread ID (-1=caller thread).  
    DWORD dwFlags; // Reserved for future use, must be zero.  
} THREADNAME_INFO;
#pragma pack(pop)

extern const wchar_t* kernel32Dll_LIBNAME;
extern const char* setThreadDescription_FUNCNAME;

extern bool hasTriedToFindThreadNamingFunction;
extern SetThreadDescriptionFunction threadNamingFunction;

OSVERSIONINFOEX windowsVersionToOsVersionInfoEx(const WindowsVersion& winVer);
WindowsVersion osVersionInfoExToWindowsVersion(const OSVERSIONINFOEX& osvi);

bool isWindowsVersionGreatherThanOrEqualTo(const WindowsVersion& winVer);

void setThreadName(DWORD dwThreadID, const char* threadName);

/*! @brief If the threads name can be set, it is, otherwise fails silently.
@param threadName the name to use.
@return Whether or not the name was set.*/
bool setCurrentThreadName(const std::string& threadName);

/*! @brief If the threads name can be set, it is, otherwise fails silently.
@param threadName the name to use.
@return Whether or not the name was set.*/
bool setThreadName(void* handle, const std::string& threadName);

/*! @brief Only for internal use by WinUtils. Returns SetThreadDescription or a nullptr.*/
SetThreadDescriptionFunction getThreadNamingFunctionOrNullptr();

/*! @brief Convert Unicode string into ANSI string. 
@param unicodeString Unicode string as input, ansiString output, numCharsInAnsiString string lenght of ANSI string
    Unicode string must be null terminated
@return If successful, returns the number of bytes written to the ansiString, otherwise 0.*/
int convertUnicodeStringToAnsiString(const TCHAR* unicodeString, char* ansiString,
	int numCharsInAnsiString);

}
}
