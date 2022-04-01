// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>

namespace HP {
namespace Omnicept {
namespace Abi {

     /*! @brief Domain type for photoplethysmography (%PPG) data.*/
    class PPG : public DomainData
    {
    public:
        PPG();
        PPG(const std::vector<uint32_t> &values);
        virtual ~PPG() = default;

        /*! @brief %PPG values
        * 
        * Values will be set based on SensorInfo. Check the containing PPGFrame::sensorInfo to ensure that the data is in the format you expect.
        * 
        * For %HP Reverb G2 %Omnicept Edition:
        * 
        *    - PPGFrame::sensorInfo will have: 
        *       + ID: "HP Reverb G2 Omnicept" 
        *       + SubID: "MAX86140" 
        *       + Location: "Forehead"
        * 
        *    - And the indices of the %PPG values returned for that correspond to:
        *       + ledValues[0] %PPG captured with only the first LED on. 
        *       + ledValues[1] %PPG captured with only the second LED on. 
        *       + ledValues[2] %PPG captured with just ambient light.
        */
        std::vector<uint32_t> ledValues;
     
        bool operator == (const PPG& other) const;
        bool dataEquals(const DomainData& other) const override;
        std::string toString() const;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
    };

    std::ostream & operator << (std::ostream &out, const PPG&);

    //-------------------------------------------------------------------------
    /*! @brief Domain type for PPG Frames.
    * 
    */ 
    class PPGFrame : public DataFrame<PPG>
    {
    public:
        PPGFrame();
        PPGFrame(std::vector<uint32_t>& ledCurrents);
        MessageVersion getLatestMessageVersion() const override;
        virtual ~PPGFrame() = default;
        
        

        /*! @brief LED brightness values on [0-255] scale.
        *
        * Values will be set based on SensorInfo. Check PPGFrame::sensorInfo to ensure that the data is in the format you expect.
        * 
        * For %HP Reverb G2 %Omnicept Edition: 
        * 
        *    - PPGFrame::sensorInfo will have: 
        *       + ID: "HP Reverb G2 Omnicept"
        *       + SubID: "MAX86140" 
        *       + Location: "Forehead"
        * 
        *    - And the indices of the LED brightness returned for that sensor correspond to: 
        *       + ledCurrents[0] brightness of the first LED,\n
        *       + ledCurrents[1] brightness of the second LED.
        */
        std::vector<uint32_t> ledCurrents;

        std::string toString() const;
        MessageType getMessageType() const override;
    };

    std::ostream & operator << (std::ostream &out, const PPGFrame&);
}
}
}