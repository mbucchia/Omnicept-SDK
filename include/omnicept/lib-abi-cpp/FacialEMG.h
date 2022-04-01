// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/Experimental.h>
#include <omnicept/lib-abi-cpp/SensorInfo.h>
#include <omnicept/lib-abi-cpp/DomainData.h>
#include <omnicept/lib-abi-cpp/DataFrame.h>
#include <omnicept/lib-abi-cpp/Timestamp.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for facial EMG.
     *
     * \warning FacialEMG development is unfinished, and it should not be used
     *
     * \internal 
     *  A single FacialEMG contains a single sample of all channels. Each channel
     *  represents a single EMG pad on the face. 
     * \endinternal
     */
    class FacialEMG : public DomainData
    {
    public:
        //! @cond
        FacialEMG();
        FacialEMG(const std::vector<double>& emgValues);
        virtual ~FacialEMG() override = default;

        std::vector<double> emgValues;

        bool operator == (const FacialEMG& other) const;
        bool dataEquals(const DomainData& other) const override;
        
        std::string toString() const;
        MessageVersion getLatestMessageVersion() const override;
        MessageType getMessageType() const override;
        //! @endcond
    };
    std::ostream & operator << (std::ostream &out, const FacialEMG&);

    /*! @brief Domain type for FacialEMG Frames.
     *
     * \warning FacialEMGFrame development is unfinished, and it should not be used 
     * \internal 
     *  The Frame contains one or more Facial EMG data points and
     *  a timestamp that represents the latest data.
     * \endinternal
     */
    class FacialEMGFrame : public DataFrame<FacialEMG>
    {
    public:
        //! @cond
        FacialEMGFrame();
        virtual ~FacialEMGFrame() = default;
        MessageType getMessageType() const override;
        MessageVersion getLatestMessageVersion() const override;
        //! @endcond
    };

    std::ostream& operator << (std::ostream& out, const FacialEMGFrame&);

}

}
}