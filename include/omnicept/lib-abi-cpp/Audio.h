// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Describes an encoded buffer in WaveFormatEx format.
        *  Data format of the wave audio stream.
        *  See https://docs.microsoft.com/en-us/windows/win32/api/mmreg/ns-mmreg-waveformatex
        */
    class WaveFormatEx
    {
    public:
        WaveFormatEx();
        WaveFormatEx(const uint16_t formatTag, const uint16_t channels, const uint32_t samplesPerSec,
            const uint32_t avgBytesPerSec, const uint16_t blockAlign, const uint16_t bitsPerSample);

        virtual ~WaveFormatEx() = default;

        uint16_t formatTag;      /*!< @brief Waveform audio format type. */ //Limit to uint16
        uint16_t channels;       /*!< @brief Number of channels of audio data.  */ //Limit to uint16
        uint32_t samplesPerSec;  /*!< @brief Sample frequency at which each should be played. */
        uint32_t avgBytesPerSec; /*!< @brief Average data transfer rate in bytes per second. */
        uint16_t blockAlign;     /*!< @brief Block alignment in bytes. The size of the minumum atomic unit of data for the format type.  */ //Limit to uint16
        uint16_t bitsPerSample;  /*!< @brief Number fo bits per sample for the format type. */ //Limit to uint16
        const static uint16_t CB_SIZE; /*!< @brief size, in bytes, of extra format information appended to the end of the WAVEFORMATEX structure. 34 for WAVEFORMATEXTENSIBLE_IEC61937 structure */

        bool operator == (const WaveFormatEx& other) const;
        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const WaveFormatEx&);

    //------------------------------------------------------------------------
    /*! @brief Describes an encoded audio buffer in WaveFormatExtensible format.
        *  Format of the wave audio stream.
        *  See https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/ksmedia/ns-ksmedia-waveformatextensible
        */
    class WaveFormatExtensible
    {
    public:
        WaveFormatExtensible();
        WaveFormatExtensible(const WaveFormatEx waveFormatEx,
            const uint16_t samples, const uint32_t channelMask, const std::string subFormat);

        virtual ~WaveFormatExtensible() = default;

        WaveFormatEx waveFormatEx; /*!< @brief Data format of the wave audio stream. */
        uint16_t samples;        /*!< @brief A Union of validBitsPerSample, samplesPerBlock, or reserved. */ //Limit to uint16.
        uint32_t channelMask; /*!< @brief Assigment of channels in the multichannel stream to speaker positions. */
        std::string subFormat; /*!< @brief A GUID that specifies the subformat. */

        bool operator == (const WaveFormatExtensible& other) const;
        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const WaveFormatExtensible&);

    //------------------------------------------------------------------------
    /*! @brief Describes an encoded audio buffer in WaveFormatIEC61937 format.
        *  Effective number of channels, sample size, and data rate of a non-PCM format.
        *  See https://docs.microsoft.com/en-us/windows/win32/coreaudio/representing-formats-for-iec-61937-transmissions
        */
    class WaveFormatExtensibleIEC61937
    {
    public:
        WaveFormatExtensibleIEC61937();
        WaveFormatExtensibleIEC61937(const WaveFormatExtensible waveFormatExtensible,
            const uint32_t encodedSamplesPerSec, const uint32_t encodedChannelCount, const uint32_t averageBytesPerSec);

        virtual ~WaveFormatExtensibleIEC61937() = default;

        WaveFormatExtensible waveFormatExtensible; /*!< @brief Format of the wave audio stream. */
        uint32_t encodedSamplesPerSec; /*!< @brief Sampling rate of the post-decode audio. */
        uint32_t encodedChannelCount; /*!< @brief Channel count of the post-decode audio. */
        uint32_t averageBytesPerSec; /*!< @brief Byte rate of the content, Usually ignored and is 0. */

        bool operator == (const WaveFormatExtensibleIEC61937& other) const;
        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const WaveFormatExtensibleIEC61937&);

    //------------------------------------------------------------------------
    /*! @brief Domain type for Audio buffer.
    *  A single Audio contains a buffer and a WaveFormatIEC61937 description.
    *  See https://docs.microsoft.com/en-us/windows/win32/coreaudio/representing-formats-for-iec-61937-transmissions
    */
    class Audio : public DomainData
    {
    public:
        Audio();
        Audio(const std::vector<unsigned char>& buffer, const std::shared_ptr<const WaveFormatExtensibleIEC61937> waveFormatExtensibleIEC61937);

        virtual ~Audio() = default;

        std::vector<unsigned char> buffer; /*!< @brief Buffer of the Audio stream. */
        std::shared_ptr<const WaveFormatExtensibleIEC61937> waveFormatExtensibleIEC61937; /*!< @brief Format of the wave audio stream. */

        bool operator == (const Audio& other) const;
        bool dataEquals(const DomainData& other) const override;
        std::string toString() const;
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
    };

    std::ostream& operator<< (std::ostream& out, const Audio&);

    /*! @brief Domain type for Audio Frames.
        *
        *  The Frame contains one or more Audio data and
        *  a timestamp that represents the latest data.
        */
    class AudioFrame : public DataFrame<Audio>
    {
    public:
        AudioFrame();
        AudioFrame(const std::shared_ptr<const WaveFormatExtensibleIEC61937> waveFormatExtensibleIEC61937);

        virtual ~AudioFrame() = default;

        std::shared_ptr<const WaveFormatExtensibleIEC61937> waveFormatExtensibleIEC61937; /*!< @brief Format of the wave audio stream.  */
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
    };
}
}
}
