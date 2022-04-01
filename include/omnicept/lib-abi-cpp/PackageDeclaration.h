// (c) Copyright 2018-2021 HP Development Company, L.P.

#pragma once
#include <stdint.h>
#include <string>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/MessageTypes.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Similar to a network packet header, a PackageDeclaration precedes every message body and declares its contents.
    *
    * A PackageDeclaration should not be used beyond the I/OMessageFacade classes. A module has no reason to send a PackageDeclaration only,
    * and the messaging system automatically generates declarations for messages that are sent.
    */
    class PackageDeclaration final
    {
    public:
        PackageDeclaration(MessageType type, std::string version, uint64_t length, const std::string& sender, const std::string& destination = "");
        
        PackageDeclaration();
        PackageDeclaration(const PackageDeclaration&) = default;
        PackageDeclaration(PackageDeclaration&&) = default;
        PackageDeclaration& operator = (const PackageDeclaration&) = default;
        PackageDeclaration& operator = (PackageDeclaration&&) = default;
        ~PackageDeclaration() = default;

        MessageType getType() const; /*!< @brief The MessageType is a deserialization hint to the messaging system. */
        std::string getVersion() const; /*!< @brief The version, including format and fields, related to the MessageType. */
        uint64_t getLength() const;  /*!< @brief The byte length of the message body, not the length of the PackageDeclaration. */
        const std::string& getSender() const; /*!< @brief A human-readable name and a UUID concatenated together, uniquely identifying the message source. */
        const std::string& getDestination() const; /*!< @brief A human-readable name and a UUID concatenated together, uniquely identifying the message destination. If blank, gets routed everywhere. */

        void setType(MessageType);
        void setVersion(std::string);
        void setLength(uint64_t);
        void setSender(const std::string&);
        void setDestination(const std::string&);

        const SensorInfo& getSensorInfo() const;
        void setSensorInfo(const SensorInfo& sensorInfo);

    private:
        SensorInfo m_sensorInfo;
        MessageType m_type;
        std::string m_version;
        uint64_t m_length;
        std::string m_sender;
        std::string m_destination;
    };
}

}
}