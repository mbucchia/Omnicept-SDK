// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>

#include <vector>
#include <iostream>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for Camera Image data.*/
    class CameraImage : public DomainData
    {
    public:
        enum class ImageFormat 
        { 
            UNKNOWN,
            RGB888,
            YUY2,
            UYVY,
            YVYU,
            YUYV,
            AYUV,
            YV12,
            NV12,
            L8,
            CUSTOM
        };

        CameraImage();
        virtual ~CameraImage() = default;

        std::vector<unsigned char> imageData; /*!< @brief Container of bytes that contains image data in #format */
        ImageFormat format; /*!< @brief The specific arrangement of bytes for the data in #imageData e.g. YUY2*/
        uint32_t width; /*!< @brief Width of image in number of pixels */
        uint32_t height; /*!< @brief Height of image in number of pixels */
        uint64_t frameNumber; /*!< @brief Sequential image number for the frame */
        float framesPerSecond; /*!< @brief Number of frames camera captures per second */

        bool operator == (const CameraImage& other) const;
        bool dataEquals(const DomainData& other) const override;

        std::string toString() const;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    std::ostream& operator << (std::ostream& out, const CameraImage&);
}
}
}
