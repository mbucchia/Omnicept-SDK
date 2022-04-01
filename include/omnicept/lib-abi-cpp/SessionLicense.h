// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once
#include <omnicept/lib-abi-cpp/LicensingModel.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

/*! @brief Session license information.*/
class SessionLicense
{
public:

    /*! @brief Used to store session license information.
    * 
    * @param clientId a unique string token as user identification
    * @param accessKey a unique string token tied to a user's application 
    * @param requestedLicense the type of license
    * @param isRunningInEditor only relevent when \p requestedLicense is LicensingModel::ENTERPRISE. 
             Should be set to true only if the license is being used for development.
    */
    SessionLicense(std::string clientId, std::string accessKey, LicensingModel requestedLicense, bool isRunningInEditor);
    bool operator == (const SessionLicense& other) const;
    const std::string& getClientId() const;
    const std::string& getAccessKey() const;
    Abi::LicensingModel getRequestedLicense() const;
    bool getIsRunningInEditor() const;

private:

    std::string m_clientId;
    std::string m_accessKey;
    LicensingModel m_requestedLicense;
    bool m_isRunningInEditor;
};


}
}
}
