// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-client-cpp/Client.h>
#include <omnicept/lib-abi-cpp/Errors.h>
#include <omnicept/lib-abi-cpp/LicensingModel.h>
#include <omnicept/lib-abi-cpp/SessionLicense.h>

#include <future>
#include <atomic>
#include <memory>

namespace HP {
    namespace Omnicept {

        class GliaConnection;

        /*! @brief Entry point in to the %HP %Omnicept SDK */
        class Glia
        {
        public:
            Glia() = delete;

            /*! @brief Synchronously builds a Client connected to the %HP %Omnicept Runtime
            *
            * The connection process can take a while. If code exectuion of the calling thread cannot be slowed down, use #StartBuildClient_Async instead
            * 
            * @param clientName will be in the sender field of all messages sent from this client.
            * @param license Licensing information for the client
            * @param onStateChange a function called whenever the state of the Client is changed 
            * 
            * @exception Abi::ProtocolError the client did not receive the message it was expecting when establishing the connection
            * @exception Abi::TransportError the client was unable to connect to the %HP %Omnicept Runtime
            * @exception Abi::HandshakeError the handshake was rejected by the %HP %Omnicept Runtime
            * @exception std::invalid_argument if invalid parameters were passed to the Client see exceptions listed in Client::Client for details
            * 
            * @returns a Client connected to the %HP %Omnicept Runtime
            */
            static std::unique_ptr<Client> BuildClient_Sync(const std::string& clientName,
                std::unique_ptr<HP::Omnicept::Abi::SessionLicense> license,
                Client::StateCallback_T onStateChange);

            /*! @brief A single use object that builds a Client connected to the %HP %Omnicept Runtime asynchronously
            * 
            */
            class AsyncClientBuilder final
            {
                friend Glia;
                AsyncClientBuilder(const std::string& clientName, std::unique_ptr<Abi::SessionLicense> license, Client::StateCallback_T onStateChange);
            public:

                /*! @brief Can the Client be built without blocking 
                *
                * @returns true if the AsyncClientBuilder #isValid, and the asynchronous thread building the Client has finished running.
                */
                bool isClientBuildFinished() const;

                /*! @brief Is the AsyncClientBuilder valid
                * 
                * An AsyncClientBuilder is valid after construction until #getBuildClientResultOrThrow is called, and will be invalid after that. 
                *
                * @returns true if #getBuildClientResultOrThrow has not been called yet. 
                */
                bool isValid() const;

                /*! @brief Waits for the asynchronous thread building a connection to the %HP %Omnicept Runtime to finish
                 * 
                 * Upon returning, #isClientBuildFinished will return true
                 * 
                 * @exception std::logic_error if the AsyncClientBuilder is no longer valid. Can check with AsyncClientBuilder::isValid()
                */
                void waitForConnection();

                /*! @brief Waits for the asynchronous thread building the Client connection to the %HP %Omnicept Runtime to finish, and returns the Client if successfull, 
                * or throws an exception if it is not
                *
                * Will block calling thread until the asynchronous thread building the Client connection is finished unless #isClientBuildFinished is true
                *
                * @exception Abi::ProtocolError the client did not receive the message it was expecting when establishing the connection
                * @exception Abi::TransportError the client was unable to connect to the %HP %Omnicept Runtime
                * @exception Abi::HandshakeError the handshake was rejected by the %HP %Omnicept Runtime
                * @exception std::invalid_argument if invalid parameters were passed to the Client see exceptions listed in Client::Client for details
                * 
                * @exception std::logic_error if the AsyncClientBuilder is no longer valid. Can check with #isValid
                * 
                * @returns a Client connected to the %HP %Omnicept Runtime
                * 
                * @note AsyncClientBuilder will be in an invalid state after this call until its destruction
                */
                std::unique_ptr<Client> getBuildClientResultOrThrow();

                /*! @brief Destructor for AsyncClientBuilder
                 *
                 * @note the destructor will NOT wait for the asynchronous thread to finish. 
                */
                ~AsyncClientBuilder() = default;

                AsyncClientBuilder(const AsyncClientBuilder&) = delete;
                AsyncClientBuilder& operator = (const AsyncClientBuilder&) = delete;
                AsyncClientBuilder(AsyncClientBuilder&&) = default;
                AsyncClientBuilder& operator = (AsyncClientBuilder&&) = default;
            private:
                std::future<std::unique_ptr<Client>> m_clientFuture;
                std::shared_ptr<std::atomic<bool>> m_isConnectionBuilt;
            };

            /*! @brief Starts asynchronously building a Client connected to the %HP %Omnicept Runtime, returns an object to finish building a Client
            * Constructs an AsyncClientBuilder builds a Client connected to the %HP %Omnicept Runtime asynchronously, then can be used to get the result of the call
            *
            * This factory function starts the Client building process.
            *
            * @param clientName The client name will be written into the sender field of all messages sent from this client.
            * @param license Licensing information for the client
            * @param onStateChange function that will be called whenever the Client changes state
            * 
            * @returns AsyncClientBuilder object that is asynchronously building a Client connected to the %HP %Omnicept Runtime, the result can be received by calling AsyncClientBuilder::getBuildClientResultOrThrow
            */
            static std::unique_ptr<AsyncClientBuilder> StartBuildClient_Async(const std::string& clientName,
                std::unique_ptr<HP::Omnicept::Abi::SessionLicense> license,
                Client::StateCallback_T onStateChange);

            /*! @attention This function is only required if you are loading %HP %Omnciept as a dll.  
             * @brief This function starts some asynchronous systems like logging, and should be called before any other functions.
             */
            static void startModule();

            /*! @attention This function is only required if you are loading %HP %Omnciept as a dll. 
             * @brief This function stops some asynchronous systems like logging, and should be called after all classes are cleaned up.
             */
            static void stopModule();

        };
    }
}
