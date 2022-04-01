// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <HP/lib-utils-cpp/IUuid.h>
#include <boost/uuid/uuid.hpp>
#include <string>

namespace HP {
namespace Utils {

    struct UuidImpl : public IUuid
    {
        UuidImpl();
        UuidImpl(const std::string&);
        virtual ~UuidImpl() = default;

        virtual operator std::string() const override;

    private:
        boost::uuids::uuid m_uuid;
    };

}
}
