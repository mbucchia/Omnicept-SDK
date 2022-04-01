// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#ifdef OMNICEPT_EXPERIMENTAL
#include <omnicept/lib-abi-cpp/Experimental.h>
#endif

#include <HP/lib-utils-cpp/ThreadOwner.h>
#include <omnicept/lib-abi-cpp/MessageTypes.h>
#include <omnicept/lib-abi-cpp/IMessage.h>
#include <omnicept/lib-abi-cpp/Errors.h>
#include <omnicept/lib-abi-cpp/HeartRate.h>
#include <omnicept/lib-abi-cpp/HeartRateVariability.h>
#include <omnicept/lib-abi-cpp/EyeTracking.h>
#include <omnicept/lib-abi-cpp/CognitiveLoad.h>
#include <omnicept/lib-abi-cpp/CognitiveLoadInputFeature.h>
#include <omnicept/lib-abi-cpp/PPG.h>
#include <omnicept/lib-abi-cpp/SubscriptionList.h>
#include <omnicept/lib-abi-cpp/CameraImage.h>
#include <omnicept/lib-abi-cpp/DataVaultResult.h>
#include <omnicept/lib-abi-cpp/IMU.h>
#include <omnicept/lib-abi-cpp/Audio.h>
#include <omnicept/lib-abi-cpp/SubscriptionResultList.h>

#include <shared_mutex>
#include <memory>
#include <map>
#include <functional>

namespace HP {
namespace Omnicept {

        class Glia;
        class GliaConnection;

        /*! @brief Used to receive and send messages to/from the %HP %Omnicept Runtime
        *
        * Has an internal thread that monitors incoming messages. 
        * When a message is received the Client caches it as the most recent value for the message's type, and executes a callback function mapped to
        * the message's type
        * 
        * A separate callback is executed when a Client's state is changed which can be done by request or by signals receive from the %HP %Omnicept Runtime. 
        * 
        * The internal thread will run until the client is destroyed or disconnected from the %HP %Omnicept Runtime.
        * 
        * To start receving messages after construction a Client must set a subscription to the messages it wants, via #setSubscriptions, and call #startClient
        * 
        * @note 
        * A Client can receive the following message types: 
        *   + Abi::CognitiveLoad
        *   + Abi::CognitiveLoadInputFeature
        *   + Abi::EyeTracking 
        *   + Abi::HeartRate
        *   + Abi::HeartRateVariability
        *   + Abi::PPGFrame
        *   + Abi::SceneColorFrame
        *   + Abi::CameraImage
        *   + Abi::DataVaultResult
        *   + Abi::IMUFrame
        *   + Abi::AudioFrame
        *   + Abi::SubscriptionResultList
        */
        class Client : public HP::Utils::ThreadOwner
        {
        public:
            /*!@brief struct representing the result of Client::getLastData<DomainType>()
            *
            * @tparam DomainType the type of data
            * 
            */
            template<class DomainType> struct LastValueCached
            {
                DomainType data; /*!< @brief data stored in Client's lvc if #valid is true, otherwise the default value of DomainType*/
                bool valid; /*!< @brief if #data is valid.*/
            };
            
            /*! @brief Enum representing the state of the Client
            */
            enum class State : uint8_t
            {
                /*! @brief The Client is connected but it is not currently receiving data. \n
                * This is the state the Client will be in after construction. Or after Client::pauseClient() is called successfully. \n
                * The Client's message callback's will not be called, nor will its lvc be updated while paused.
                */
                PAUSED = 0,

                /*! @brief The Client is connected and is currently receiving messages \n
                * This is the state the Client will be in after Client::startClient() is called successfully
                */
                RUNNING = 1,

                /*! @brief The Client is disconnected. This is the terminal state of a Client. \n
                * Once a Client is disconnected, it cannot be reconnected, a new Client has to be made. \n
                * A disconnection can happen by user request, when Client::disconnectClient() is called, or
                * or by the %HP %Omnicept Runtime disconnecting from the Client.
                */
                DISCONNECTED = 2,
            };

            /**
            * @brief Enum representing a result from operations on the Client
            * The success of some operations are dependent on the Client's Client::State
            */
            enum class Result : uint8_t
            {
                /*! @brief The Client operation was successful
                */
                SUCCESS = 0,

                /*! @brief The operation was unsuccessful because the Client's state is Client::State::DISCONNECTED
                */
                ERROR_CLIENT_DISCONNECTED = 1,

                /*! @brief The operation was not executed because the Client's state is Client::State::RUNNING
                */
                NO_OP_CLIENT_RUNNING = 2,

                /*! @brief The operation was not executed because the Client's state is Client::State::PAUSED
                */
                NO_OP_CLIENT_PAUSED = 3,

                /*! @brief The operation was not unsuccessful due to a function specific error
                */
                UNSPECIFIED_ERROR = 4,
            };

            using StateCallback_T = std::function<void(const State)>;

        protected:
            //Factory class
            friend Glia;

            /*! @brief Constructs a Client around the given connection
             * 
             * @param connection the connection used to communicate with the %HP %Omnicept Runtime
             * @param onStateChange the function to call whenever a Client's State is changed either by a 
             *          call to one of the member functions #startClient, #pauseClient, #disconnectClient,
             *          or by the %HP %Omnicept Runtime disconnecting from the Client.
             * 
             * @exception std::invalid_argument if \p onStateChange is a nullptr
            */
            Client(std::unique_ptr<GliaConnection> connection, StateCallback_T onStateChange);
        public:
            virtual ~Client();

            /*! @brief If the Client's State is State::PAUSED changes the Client's State to State::RUNNING
            *
            * @note This should not be confused with the inherited function Utils::ThreadOwner::start(), which can be ignored. 
            * 
            * @returns result which will be:
            *                 + Result::SUCCESS if the Client's State successfully transitioned to State::RUNNING, or \n
            *                 + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED, or \n
            *                 + Result::NO_OP_CLIENT_RUNNING if the Client's State is State::RUNNING
            */
            Result startClient();

            /*! @brief If the Client's State is State::RUNNING changes the Client's State to State::PAUSED
            *
            * @returns result which will be:
            *                 + Result::SUCCESS if the Client's State successfully transitioned to State::PAUSED
            *                 + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED
            *                 + Result::NO_OP_CLIENT_PAUSED if the Client's State is State::PAUSED,
            */
            Result pauseClient();

            /*! @brief If the Client's State is not State::DISCONNECTED changes the Client's State to State::DISCONNECTED
            *
            * If the Client's State was changed the state callback will be called
            *
            * @returns result which will be: 
            *                 + Result::SUCCESS if the Client's State successfully transitioned to State::DISCONNECTED
            *                 + Result::ERROR_CLIENT_DISCONNECTED if the Client's State was already State::DISCONNECTED
            */
            Result disconnectClient();

            /*! @brief Takes a \p DomainType as a template parameter and a function to be called when a \p DomainType message is received from the %HP %Omnicept Runtime.
             *
             * If a callback already exists for \p DomainType it will silently be overwritten
             *
             * @tparam DomainType the type of message the callback will receives
             * @param callback the function pointer
             * @returns result which will be: 
             *                  + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED
             *                  + Result::UNSPECIFIED_ERROR if \p callback is a nullptr 
             *                  + Result::SUCCESS otherwise
             */
            template <class DomainType>
            Result registerCallback(std::function<void(std::shared_ptr<DomainType>)> callback);

            /*! @brief Takes a \p DomainType as a template parameter and unregisters the function to be called for a specific \p DomainType
             *
             * @tparam DomainType The message type of the callback to remove
             *
             * @returns result which will be: 
             *                  + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED
             *                  + Result::SUCCESS otherwise
             */
            template <class DomainType>
            Result unregisterCallback()
            {
                Result result{ Result::ERROR_CLIENT_DISCONNECTED };
                if (m_state != State::DISCONNECTED)
                {
                    std::unique_lock<std::shared_mutex> lock{ m_callbackLock };
                    m_callbackMap.erase(Abi::MessageTypeUtils::getEnumForType<DomainType>());
                    result = Result::SUCCESS;
                }
                return result;
            }

            /*! @brief Takes a \p DomainType as a template parameter and checks if a callback function is registered for the specified \p DomainType
            *
            * @tparam DomainType A type of message
            * @returns true if there is a callback registered for \p DomainType, else false
            */
            template <class DomainType>
            bool isCallbackRegisteredForType() const
            {
                std::shared_lock<std::shared_mutex> lock{ m_callbackLock };
                return m_callbackMap.find(Abi::MessageTypeUtils::getEnumForType<DomainType>()) != m_callbackMap.end();
            }

            /*! @brief Clears all registered callbacks
            */
            void clearAllCallbacks();

            /*! @brief Takes a \p DomainType as a template parameter and returns the last
             * value received of that \p DomainType.
             *
             * @tparam DomainType the domain type of the message (e.g. Abi::HeartRate)
             *
             * @exception Abi::SerializationError when the message is malformed
             * @returns LastValueCached for \p DomainType. If LastValueCached.valid is false the Client has yet to receive 
                        a message of \p DomainType, and LastValueCached.data will have \p DomainType's default constructed values.
             */
            template<class DomainType>
            LastValueCached<DomainType> getLastData();

            /*! @brief Start recording all DomainType messages data send to %HP %Omnicept Runtime.
             *
             * @param dvrCallback a callback to be registered for Abi::DataVaultResult messages received from the
             *      %HP %Omnicept Runtime
             * 
             * @returns result which will be: 
             *                  + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED
             *                  + Result::NO_OP_CLIENT_PAUSED if the Client's State is State::PAUSED
             *                  + Result::UNSPECIFIED_ERROR if \p dvrCallback is a nullptr 
             *                  + Result::SUCCESS otherwise
             */
            Result startDataRecord(std::function<void(std::shared_ptr<Abi::DataVaultResult>)> dvrCallback);

            /*! @brief Stop recording all DomainType messages data send to %HP %Omnicept Runtime.
             *
             * @returns result which will be: 
             *                  + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED
             *                  + Result::NO_OP_CLIENT_PAUSED if the Client's State is State::PAUSED
             *                  + Result::SUCCESS otherwise
             */
            Result stopDataRecord();

            /*! @brief Gets the current State of the Client
            * 
            * @returns the Client's State
            */
            State getClientState() const;

            /*! @brief Tells the Client what messages to ask the %HP %Omnicept Runtime for. 
            *
            * @warning If you subscribe to messages that you don't have the correct license for, you will not receive them. 
            * @attention The Client's default Abi::SubscriptionList is set Abi::SubscriptionList::GetSubscriptionListToNone(), and no messages will be received until one is set.
            *            Setting subscriptions happens asynchronously, so there will be a small delay between setting the subscriptions
            *            and receiving messages you subscribed to.
            * 
            * @param subList the messages the Client should ask to receive
            * @returns result which will be:
            *                  + Result::ERROR_CLIENT_DISCONNECTED if the Client's State is State::DISCONNECTED
            *                  + Result::SUCCESS otherwise
            */
            Result setSubscriptions(const Abi::SubscriptionList& subList);
            
        protected:
            std::shared_ptr<GliaConnection> m_connection;
            mutable std::shared_mutex m_callbackLock;
            std::map<Abi::MessageType, std::function<void(const GliaConnection&, std::shared_ptr<const Abi::IMessage> message)>> m_callbackMap;
            StateCallback_T m_onStateChange;
            Abi::SubscriptionList m_subscriptions;
            std::atomic<State> m_state;

            std::shared_mutex m_lvcMapLock;
            std::mutex m_subscriptionMutex;
            std::recursive_mutex m_stateChangeMutex;
            std::map<HP::Omnicept::Abi::MessageType, std::shared_ptr<const HP::Omnicept::Abi::IMessage>> m_lastValueCacheMap;

            virtual void unblock();
            virtual void readChannel() final;
            virtual void handleMessage(std::shared_ptr<const HP::Omnicept::Abi::IMessage> message);

            void threadFunction() override;
        };
    }
}
