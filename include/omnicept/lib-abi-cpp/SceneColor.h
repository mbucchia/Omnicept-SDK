// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/Experimental.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/Timestamp.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Struct containing RGB and luminance values 
    * 
    * RGB values are non-linear, normalized [0,1] in the sRGB color space
    * Luminance calculated using RGB converted to linear-light values. 
    */
    struct Color
    {
    public:
        Color();
        Color(float r, float g, float b, float y);

        virtual ~Color() = default;

        bool operator == (const Color& other) const;
        std::string toString() const;

        float r; /*!< @brief Red [0.f,1.f] */
        float g; /*!< @brief Green [0.f,1.f] */
        float b; /*!< @brief Blue [0.f,1.f] */
        float y; /*!< @brief Luminance [0.f,1.f] */
    };

    /*! @brief Domain type for eye average color and brightness
     *
     *  Contains the ambient and foveal average color a single
     *  Eye
     */
    class EyeSceneColors
    {
    public:
        EyeSceneColors();
        EyeSceneColors(const Color& ambient, const Color& foveal);
        virtual ~EyeSceneColors() = default;

        Color ambientColor; /*!< @brief Ambient color is average color calculated over the entire image */
        Color fovealColor; /*!< @brief Foveal color is average color calculated over the foveal region of the eye */

        bool operator == (const EyeSceneColors& other) const;
        std::string toString() const;
    };

    /*! @brief Domain type for HMD average color and brightness
     *
     *  Contains the ambient and foveal average color and left
     *  and right eyes.
     */
    class SceneColor : public DomainData
    {
    public:
        SceneColor();
        SceneColor(const EyeSceneColors& left, const EyeSceneColors& right);
        virtual ~SceneColor() override = default;

        EyeSceneColors leftEyeSceneColors; /*!< @brief EyeSceneColors for left display. */
        EyeSceneColors rightEyeSceneColors; /*!< @brief EyeSceneColors for right display. */

        bool operator == (const SceneColor& other) const;
        bool dataEquals(const DomainData& other) const override;

        std::string toString() const;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    /*! @brief Domain type for Framed SceneColors
     *
     *  Contains the ambient and foveal average color for the left
     *  and right eyes (Framed).
     */
    class SceneColorFrame : public DataFrame<SceneColor>
    {
    public:
        SceneColorFrame();
        virtual ~SceneColorFrame() override = default;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    std::ostream & operator << (std::ostream &out, const SceneColor&);
    std::ostream & operator << (std::ostream &out, const SceneColorFrame&);

}
}
}
