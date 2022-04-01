// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/GenericMessage.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    enum class DataVaultResultType
    {
        UNKNOWN = 0,
        RECORDING_STARTED = 1,
        RECORDING_START_REJECTED = 2,
        RECORDING_STOPPED = 3,
        RECORDING_STOP_REJECTED = 4,
        RECORDING_ERROR = 5
    };

    enum class DataVaultResultErrorType
    {
        UNKNOWN_ERROR = 0,
        SUCCESS_NO_ERROR = 1,
        INVALID_LICENSE_ERROR = 2,
        CONNECTION_FAILED_ERROR = 3,
        CONNECTION_NEGOTIATING_ERROR = 4,
        RECORDING_HAS_ALREADY_STARTED_ERROR = 5,
        RECORDING_HAS_NOT_STARTED_ERROR = 6,
        RECORDING_STOP_NO_PERMISSON_ERROR = 7
    };
    /*! @brief A composite message to indicate DataVault recording result from a request to start or stop a DataVault recording.
    *
    */
    class DataVaultResult final : public GenericMessage
    {
    public:
        DataVaultResult();
        DataVaultResult(DataVaultResultType result, DataVaultResultErrorType error, std::string sessionId = "");
        std::string toString() const;
        bool operator == (const DataVaultResult & rhs) const;
        
        DataVaultResultType m_result; /*!< @brief Result of a request to start or stop a Datavault recording. If #DataVaultResultType::RECORDING_STARTED then a recording successfully started.
                                       * If #DataVaultResultType::RECORDING_STOPPED then a recording successfully stopped.
                                       * All other values indicate errors, a more specific error is stored in #m_error. 
                                       */
        
        DataVaultResultErrorType m_error; /*!< @brief Error from a DataVault request. There is no error if the value is #DataVaultResultErrorType::SUCCESS_NO_ERROR.*/

        std::string m_sessionId; /*!< @brief The sessionId for a successfully started DataVault recording. Only set if #m_result is #DataVaultResultType::RECORDING_STARTED. */
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };
    std::ostream& operator <<(std::ostream& out, const DataVaultResult& bvr);
}

}
}