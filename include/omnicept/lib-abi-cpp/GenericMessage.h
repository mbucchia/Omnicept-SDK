// (c) Copyright 2019-2021 HP Development Company, L.P.

#pragma once

#include <omnicept/lib-abi-cpp/IDomainType.h>
#include <omnicept/lib-abi-cpp/IVersioned.h>
#include <string>
namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Base class for all domain types*/
    class GenericMessage: public IDomainType, public virtual IVersioned
    {
    public:
        virtual ~GenericMessage() = default;
        bool operator== (const GenericMessage& other) const;

    protected:
        GenericMessage() = default;
    };
}

}
}