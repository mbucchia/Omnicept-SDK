// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <string>

namespace HP {
namespace Utils {

	struct IUuid
	{
		IUuid() = default;
		virtual ~IUuid() = default;

		virtual operator std::string() const = 0;
	};

}
}
