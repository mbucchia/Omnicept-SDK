// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/SessionLicense.h>
#include <string>
#include <vector>
#include <array>
#include <memory>


namespace HP {
namespace Omnicept {

    class LicenseParserUtil final
    {
        LicenseParserUtil() = delete;
    public:

        using UnderlyingLicenseModel_T = std::underlying_type_t<Abi::LicensingModel>;
        static constexpr char* CLIENT_ID_FLAG = "--clientId";
        static constexpr char* ACCESS_KEY_FLAG = "--accessKey";
        static constexpr char* LICENSE_MODEL_FLAG = "--licenseModel";
        static constexpr char* RUNNING_IN_EDITOR_FLAG = "--inEditor";

        static std::unique_ptr<Abi::SessionLicense> parseFromCmdLineArgs(const int argc, const char* const* const argv,
            Abi::LicensingModel minValidLicense = Abi::LicensingModel::CORE,
            Abi::LicensingModel maxValidLicense = Abi::LicensingModel::REV_SHARE);

        static std::unique_ptr<Abi::SessionLicense> parseFromVector(const std::vector<std::string>& licenseStrings,
            Abi::LicensingModel minValidLicense = Abi::LicensingModel::CORE,
            Abi::LicensingModel maxValidLicense = Abi::LicensingModel::REV_SHARE);

        static std::string getUsage(Abi::LicensingModel minValidLicense = Abi::LicensingModel::CORE, Abi::LicensingModel maxValidLicense = Abi::LicensingModel::REV_SHARE);

    };


}
}