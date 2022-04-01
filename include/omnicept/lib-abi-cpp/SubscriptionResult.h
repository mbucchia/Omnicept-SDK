// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <omnicept/lib-abi-cpp/MessageVersion.h>
#include <omnicept/lib-abi-cpp/Subscription.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    enum class SubscriptionResultType
    {
        UNKNOWN = 0,
        REJECTED = 1,
        PENDING = 2,
        APPROVED = 3,
    };

    enum class SubscriptionResultErrorType
    {
        UNKNOWN_ERROR = 0,
        SUCCESS_NO_ERROR = 1,
        NOT_LICENSED_ERROR = 2,
        REJECTED_BY_USER_ERROR = 3,
        SPECIFIED_VERSION_NOT_AVAILABLE_ERROR = 4,
        MESSAGE_NOT_SUPPORTED = 5,
        LEGACY_SUBSCRIPTION_NOT_CHECKED = 6,
    };
    /*! @brief A composite message to indicate Subscription Result with respond to the specific message type.
    *
    */
    class SubscriptionResult
    {
    public:
        SubscriptionResult();
        SubscriptionResult(SubscriptionResultType result, SubscriptionResultErrorType error, Subscription sub);
        std::string toString() const;
        bool operator == (const SubscriptionResult& rhs) const;
        
        SubscriptionResultType result; /*!< @brief Subscription result of the Subscription variable, m_subscription.*/
        
        SubscriptionResultErrorType error; /*!< @brief Error of the Subscription. There is no error if SubscriptionResultType value is APPROVED.*/

        Subscription subscription; /*!< @brief The detail information of the Subscrption.*/
    };
    std::ostream& operator <<(std::ostream& out, const SubscriptionResult& bvr);
}

}
}
