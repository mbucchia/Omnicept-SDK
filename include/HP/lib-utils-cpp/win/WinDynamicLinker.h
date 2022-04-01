// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <HP/lib-utils-cpp/IDynamicLinker.h>
#include <Windows.h>
#include <SoftPub.h> //Authenticode provider#include <Windows.h>

namespace HP {
namespace Utils {

class WinDynamicLinker : public IDynamicLinker
{
public:
    WinDynamicLinker() = default;
    virtual ~WinDynamicLinker() = default;

    virtual IDynamicLinker::ModuleHandle loadModule(const std::wstring& fullModulePath, bool requireSignature) override;
    virtual std::map<std::string, void*> loadFunctionsFromModule(ModuleHandle mod, const std::vector<std::string>& functionNames) override;

protected:
    virtual void* loadFunction(HMODULE mod, LPCSTR functionName);
};

}
}
