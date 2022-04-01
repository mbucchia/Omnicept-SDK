// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

#ifdef WIN32
#include <Windows.h>
#endif

namespace HP {
namespace Utils {

/*! @brief Loads dynamically linked libraries and finds functions within.
*/
class IDynamicLinker
{
public:

#ifdef WIN32
    using ModuleHandle = std::shared_ptr<HMODULE>;
#elif defined(ANDROID)
    using ModuleHandle = std::shared_ptr<void>;
#endif

    virtual ~IDynamicLinker() = default;

    /*! @brief Loads a library, performing a signature check. */
    virtual ModuleHandle loadModule(const std::wstring& fullModulePath, bool requireSignature) = 0;

    /*! @brief Loads functions from a library
    *   @param mod the platform-specific library handle to load from
    *   @param functionNames The functions to find
    *   @return A map with only the functions that were found, functions that could not be found are missing from the map.
    */
    virtual std::map<std::string, void*> loadFunctionsFromModule(ModuleHandle mod, const std::vector<std::string>& functionNames) = 0;

protected:
    /*! @brief Use the DynamicLinkerFactory to get the right factory for the current platform.*/
    IDynamicLinker() = default;
};

}
}
