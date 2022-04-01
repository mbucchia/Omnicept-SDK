// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/SubscriptionResult.h>
#include <omnicept/lib-abi-cpp/GenericMessage.h>
#include <omnicept/lib-abi-cpp/MessageTypes.h>
#include <vector>
namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for a SubscriptionResultList.
     *
     * A SubscriptionResultList is a collection of Subscription Results, indicating the subscription result of each MessageTypes specified.
     *
     */
    class SubscriptionResultList : public GenericMessage
    {
    public:
        SubscriptionResultList();
        virtual ~SubscriptionResultList() = default;

        const std::vector<SubscriptionResult>& getSubscriptionResults() const;
        std::vector<SubscriptionResult>& getSubscriptionResults();

        void setSubscriptionResults(const std::vector<SubscriptionResult>& subscriptionResults);

        bool operator == (const SubscriptionResultList& other) const;
        std::string toString() const;

        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;

    protected:
        std::vector<SubscriptionResult> m_subscriptionResults;
    };
    std::ostream& operator << (std::ostream& out, const SubscriptionResultList&);
}
}
}
