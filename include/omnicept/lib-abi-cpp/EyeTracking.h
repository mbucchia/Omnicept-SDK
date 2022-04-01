// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    class EyeTrackingFrame;

    enum class WhichEye
    {
        unknown = 0,
        left = 1,
        right = 2,
        both = 3,
    };

    // ------------------------------------------------------------------------
    /*! @brief Domain type for a normalized eye gaze vector.
    * 
    *   Relative from the user: +#x left, +#y up, +#z facing forward from the user.
    */
    struct EyeGaze
    {
        EyeGaze();
        EyeGaze(float x, float y, float z);
        float x;
        float y;
        float z;

        bool operator== (const EyeGaze& other) const;
        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const EyeGaze& eg);

    // ------------------------------------------------------------------------
    /*! @brief Domain type for pupil position. Normailzed to a [0.f,1.f] 2d coordinate system.
    * 
    * Where #x = 0.f, #y = 0.f is top left, and #x = 1.f, #y = 1.f is bottom right of coordinate system from the user's perspective.
    */
    struct PupilPosition
    {
        PupilPosition();
        PupilPosition(float x, float y);
        float x;
        float y;

        bool operator== (const PupilPosition& other) const;
        std::string toString() const;
    };

    std::ostream& operator<< (std::ostream& out, const PupilPosition& ep);

    // ------------------------------------------------------------------------
    /*! @brief Domain type for eye tracking data.
    */
    class EyeTracking : public DomainData
    {
    public:
        EyeTracking();
        virtual ~EyeTracking() = default;

        EyeGaze leftGaze; /*!< @brief EyeGaze for left eye */
        float leftGazeConfidence; /*!< @brief Confidence for #leftGaze in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */
        EyeGaze rightGaze; /*!< @brief EyeGaze for right eye */
        float rightGazeConfidence; /*!< @brief Confidence for #rightGaze in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */
        EyeGaze combinedGaze; /*!< @brief Combined EyeGaze */
        float combinedGazeConfidence; /*!< @brief Confidence #combinedGaze in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */

        float leftPupilDilation; /*!< @brief Left eye pupil dilation in millimeters */
        float leftPupilDilationConfidence; /*!< @brief Confidence for #leftPupilDilation in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */
        float rightPupilDilation; /*!< @brief Right eye pupil dilation in millimeters */
        float rightPupilDilationConfidence; /*!< @brief Confidence for #rightPupilDilation in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */

        PupilPosition leftPupilPosition; /*!< @brief PupilPosition of left pupil */
        float leftPupilPositionConfidence; /*!< @brief Confidence for #leftPupilPositionConfidence in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */
        PupilPosition rightPupilPosition; /*!< @brief PupilPosition of right pupil */
        float rightPupilPositionConfidence; /*!< @brief Confidence for #rightPupilPositionConfidence in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */

        float leftEyeOpenness; /*!< @brief Left eye openness 0.f = closed 1.f = open */
        float leftEyeOpennessConfidence; /*!< @brief Confidence for #leftEyeOpenness in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */
        float rightEyeOpenness; /*!< @brief Right eye openness 0.f = closed 1.f = open */
        float rightEyeOpennessConfidence; /*!< @brief Confidence for #rightEyeOpenness in range of [0.f, 1.f] where 0.f = invalid, 1.f = valid */

        bool operator== (const EyeTracking& other) const;
        bool dataEquals(const DomainData& other) const override;

        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
        std::string toString() const;

    };

    std::ostream& operator<< (std::ostream& out, const EyeTracking& et);

    // ------------------------------------------------------------------------
   /*! @brief Domain type for EyeTracking frame data.
   */
    class EyeTrackingFrame : public DataFrame<EyeTracking>
    {
    public:
        EyeTrackingFrame();
        virtual ~EyeTrackingFrame() = default;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };
}

}
}
