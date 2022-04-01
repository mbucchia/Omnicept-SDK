// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>
#include <map>

namespace HP {
namespace Omnicept {
namespace Abi {

    enum class Blendshapes : uint32_t
    {
        Brow_Inner_Up = 1,
        Brow_Down_Left = 2,
        Brow_Down_Right = 3,
        Brow_Outer_Up_Left = 4,
        Brow_Outer_Up_Right = 5,
        Eye_Look_Up_Left = 6,
        Eye_Look_Up_Right = 7,
        Eye_Look_Down_Left = 8,
        Eye_Look_Down_Right = 9,
        Eye_Look_Out_Left = 10,
        Eye_Look_In_Left = 11,
        Eye_Look_In_Right = 12,
        Eye_Look_Out_Right = 13,
        Eye_Blink_Left = 14,
        Eye_Blink_Right = 15,
        Eye_Squint_Left = 16,
        Eye_Squint_Right = 17,
        Eye_Wide_Left = 18,
        Eye_Wide_Right = 19,
        Cheek_Puff = 20,
        Cheek_Squint_Left = 21,
        Cheek_Squint_Right = 22,
        Nose_Sneer_Left = 23,
        Nose_Sneer_Right = 24,
        Jaw_Open = 25,
        Jaw_Forward = 26,
        Jaw_Left = 27,
        Jaw_Right = 28,
        Mouth_Funnel = 29,
        Mouth_Pucker = 30,
        Mouth_Left = 31,
        Mouth_Right = 32,
        Mouth_Roll_Upper = 33,
        Mouth_Roll_Lower = 34,
        Mouth_Shrug_Upper = 35,
        Mouth_Shrug_Lower = 36,
        Mouth_Close = 37,
        Mouth_Smile_Left = 38,
        Mouth_Smile_Right = 39,
        Mouth_Frown_Left = 40,
        Mouth_Frown_Right = 41,
        Mouth_Dimple_Left = 42,
        Mouth_Dimple_Right = 43,
        Mouth_Upper_Up_Left = 44,
        Mouth_Upper_Up_Right = 45,
        Mouth_Lower_Down_Left = 46,
        Mouth_Lower_Down_Right = 47,
        Mouth_Press_Left = 48,
        Mouth_Press_Right = 49,
        Mouth_Stretch_Left = 50,
        Mouth_Stretch_Right = 51,
        Tongue_Out = 52,
    };

    enum class MacroExpressionStates : uint32_t
    {
        smiling = 1,
        frowning = 2,
        talking = 3,
        neutral = 4
    };

    /*! @brief Domain type for Expression data.
     */
    class Expression : public DomainData
    {
    private:
        std::map<Blendshapes, float> blendshapeValues = {
            { Blendshapes::Brow_Inner_Up, 0.0F },
            { Blendshapes::Brow_Down_Left, 0.0F },
            { Blendshapes::Brow_Down_Right, 0.0F },
            { Blendshapes::Brow_Outer_Up_Left, 0.0F },
            { Blendshapes::Brow_Outer_Up_Right, 0.0F },
            { Blendshapes::Eye_Look_Up_Left, 0.0F },
            { Blendshapes::Eye_Look_Up_Right, 0.0F },
            { Blendshapes::Eye_Look_Down_Left, 0.0F },
            { Blendshapes::Eye_Look_Down_Right, 0.0F },
            { Blendshapes::Eye_Look_Out_Left, 0.0F },
            { Blendshapes::Eye_Look_In_Left, 0.0F },
            { Blendshapes::Eye_Look_In_Right, 0.0F },
            { Blendshapes::Eye_Look_Out_Right, 0.0F },
            { Blendshapes::Eye_Blink_Left, 0.0F },
            { Blendshapes::Eye_Blink_Right, 0.0F },
            { Blendshapes::Eye_Squint_Left, 0.0F },
            { Blendshapes::Eye_Squint_Right, 0.0F },
            { Blendshapes::Eye_Wide_Left, 0.0F },
            { Blendshapes::Eye_Wide_Right, 0.0F },
            { Blendshapes::Cheek_Puff, 0.0F },
            { Blendshapes::Cheek_Squint_Left, 0.0F },
            { Blendshapes::Cheek_Squint_Right, 0.0F },
            { Blendshapes::Nose_Sneer_Left, 0.0F },
            { Blendshapes::Nose_Sneer_Right, 0.0F },
            { Blendshapes::Jaw_Open, 0.0F },
            { Blendshapes::Jaw_Forward, 0.0F },
            { Blendshapes::Jaw_Left, 0.0F },
            { Blendshapes::Jaw_Right, 0.0F },
            { Blendshapes::Mouth_Funnel, 0.0F },
            { Blendshapes::Mouth_Pucker, 0.0F },
            { Blendshapes::Mouth_Left, 0.0F },
            { Blendshapes::Mouth_Right, 0.0F },
            { Blendshapes::Mouth_Roll_Upper, 0.0F },
            { Blendshapes::Mouth_Roll_Lower, 0.0F },
            { Blendshapes::Mouth_Shrug_Upper, 0.0F },
            { Blendshapes::Mouth_Shrug_Lower, 0.0F },
            { Blendshapes::Mouth_Close, 0.0F },
            { Blendshapes::Mouth_Smile_Left, 0.0F },
            { Blendshapes::Mouth_Smile_Right, 0.0F },
            { Blendshapes::Mouth_Frown_Left, 0.0F },
            { Blendshapes::Mouth_Frown_Right, 0.0F },
            { Blendshapes::Mouth_Dimple_Left, 0.0F },
            { Blendshapes::Mouth_Dimple_Right, 0.0F },
            { Blendshapes::Mouth_Upper_Up_Left, 0.0F },
            { Blendshapes::Mouth_Upper_Up_Right, 0.0F },
            { Blendshapes::Mouth_Lower_Down_Left, 0.0F },
            { Blendshapes::Mouth_Lower_Down_Right, 0.0F },
            { Blendshapes::Mouth_Press_Left, 0.0F },
            { Blendshapes::Mouth_Press_Right, 0.0F },
            { Blendshapes::Mouth_Stretch_Left, 0.0F },
            { Blendshapes::Mouth_Stretch_Right, 0.0F },
            { Blendshapes::Tongue_Out, 0.0F }
        };
        std::map<MacroExpressionStates, float> macroExpressionValues{
            {MacroExpressionStates::smiling, 0.0F},
            {MacroExpressionStates::frowning, 0.0F},
            {MacroExpressionStates::talking, 0.0F},
            {MacroExpressionStates::neutral, 0.0F}
        };

    public:
        Expression();
        Expression(std::map<Blendshapes, float> blendshapeValues, std::map<MacroExpressionStates, float> macroExpressionValues);

        virtual ~Expression() = default;

        void setBlendshapeValues(std::map<Blendshapes, float> blendshapeValues);
        void setMacroExpressionValues(std::map<MacroExpressionStates, float> macroExpressionValues);
        std::map<Blendshapes, float> getBlendshapeValues() const;
        std::map<MacroExpressionStates, float> getMacroExpressionValues() const;
        

        bool operator == (const Expression& other) const;
        bool dataEquals(const DomainData& other) const override;
        std::string toString() const;
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
    };

    std::ostream& operator<< (std::ostream &out, const Expression&);

    /*! @brief Domain type for Expression Frames.
    */
    class ExpressionFrame : public DataFrame<Expression>
    {
    public:
        ExpressionFrame();
        virtual ~ExpressionFrame() = default;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };
}
}
}