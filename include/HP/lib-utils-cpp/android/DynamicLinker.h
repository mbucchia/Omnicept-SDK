// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <HP/lib-utils-cpp/IDynamicLinker.h>

namespace HP {
namespace Utils {

class DynamicLinker : public IDynamicLinker
{
public:
    DynamicLinker() = default;
    virtual ~DynamicLinker() = default;

    virtual IDynamicLinker::ModuleHandle loadModule(const std::wstring& fullModulePath, bool requireSignature) override
    {
        return nullptr;
    }

    virtual std::map<std::string, void*> loadFunctionsFromModule(ModuleHandle mod, const std::vector<std::string>& functionNames) override
    {
        return std::map<std::string, void*>{};
    }
};

}
}
