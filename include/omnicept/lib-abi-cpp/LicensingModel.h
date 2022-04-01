// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <cstdint>

namespace HP {
namespace Omnicept {
namespace Abi {

    /**
     * @brief enum representing Licensing Model for Omnicept
     */
    enum class LicensingModel : uint16_t
    {
        /*! @brief \warning Invalid LicensingModel. 
        * 
        */
        UNKNOWN = 0,

        /*! @brief Licensing model for %Core licenses.
        *
        */
        CORE = 1,

        /*! @brief Licensing model for Trial licenses.
        *
        */
        TRIAL = 2,

        /*! @brief Licensing model for Enterprise licenses.
        *   
        */
        ENTERPRISE = 3,

        /*! @brief Licensing model for Rev Share licenses.
        *  Alias for Developer and Academic licenses
        */
        REV_SHARE = 4, 
    };
}

}
}