// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <HP/lib-utils-cpp/IUuid.h>
#include <string>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief A unique identifier for each connection in %HP %Omnicept 
    * 
    * Made up of a human-readable connection name, assigned by an incoming connection,
    * a delimiter, and a uuid assigned by the %HP %Omnicept Runtime 
    */
    class ConnectionIdentifier
    {
    public:
        /*! @brief Constructs a ConnectionIdentifier
        * 
        * @param connectionName the human readable name given by the incoming connection
        * @param uuid the uuid assigned by the %HP %Omnicept Runtime as a string
        *
        * @exception std::invalid_argument if the \p connectionName is empty or if the \p uuid is invalid
        */
        ConnectionIdentifier(const std::string connectionName, const std::string uuid);

        /*! @brief Constructs a ConnectionIdentifier
        *
        * @param identifier a stringified ConnectionIdentifier
        *
        * @exception std::invalid_argument the delimiter is missing, if the connectionName is empty, or if the uuid is invalid
        */
        ConnectionIdentifier(const std::string identifier);

        /*! @brief Constructs a ConnectionIdentifier
        *
        * @param connectionName the human readable name given by the incoming connection
        * @param uuid the uuid assigned by the %HP %Omnicept Runtime
        *
        * @exception std::invalid_argument if the \p connectionName is empty, or if the \p uuid is invalid
        */
        ConnectionIdentifier(const std::string connectionName, const HP::Utils::IUuid& uuid);

        /*! @brief Gets the ConnectionIdentifier's connection name
        *
        * @return the ConnectionIdentifier's connection name
        */
        std::string getConnectionName() const;

        /*! @brief Gets the ConnectionIdentifier's uuid as a string
        *
        * @return the ConnectionIdentifier's uuid as a string
        */
        std::string getUuid() const;

        /*! @brief Gets the delimiter used to separate the fields of a stringified ConnectionIdentifier
        *
        * @return the delimiter string
        */
        static std::string getDelimiter();


        /*! @brief Checks if a string is a valid ConnectionIdentifier
        *
        * @param toCheck a possible ConnectionIdentifier string
        * @return true if \p toCheck is a valid ConnectionIdentifier, else false
        */
        static bool isConnectionIdentifier(const std::string& toCheck);

        ConnectionIdentifier() = delete;
        ConnectionIdentifier(const ConnectionIdentifier&) = default;
        ConnectionIdentifier(ConnectionIdentifier&&) = default;
        ConnectionIdentifier& operator =(const ConnectionIdentifier&) = default;
        ConnectionIdentifier& operator =(ConnectionIdentifier&&) = default;
        operator std::string() const;
        bool operator == (const ConnectionIdentifier& other) const;
        bool operator != (const ConnectionIdentifier& other) const;
        bool operator < (const ConnectionIdentifier& other) const;
        bool operator > (const ConnectionIdentifier& other) const;
        bool operator <= (const ConnectionIdentifier& other) const;
        bool operator >= (const ConnectionIdentifier& other) const;
    private:
        std::string m_connectionName;
        std::string m_uuid;
        static constexpr const char * delimiter = "_";
    };

    std::ostream& operator << (std::ostream& out, const HP::Omnicept::Abi::ConnectionIdentifier& cId);

    //string comp overloards
    bool operator == (const ConnectionIdentifier& lhs, const std::string& rhs);
    bool operator != (const ConnectionIdentifier& lhs, const std::string& rhs);
    bool operator < (const ConnectionIdentifier& lhs, const std::string& rhs);
    bool operator > (const ConnectionIdentifier& lhs, const std::string& rhs);
    bool operator <= (const ConnectionIdentifier& lhs, const std::string& rhs);
    bool operator >= (const ConnectionIdentifier& lhs, const std::string& rhs);

}
}
}
