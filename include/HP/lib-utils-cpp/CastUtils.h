// (c) Copyright 2021 HP Development Company, L.P.

#pragma once

#include <type_traits>
#include <typeinfo>
namespace HP {
namespace Utils {

    class CastUtils
    {
    public:
        template<typename CastToIntType, typename CastFromIntType,
        typename = std::enable_if_t<std::is_integral<CastToIntType>::value>, typename = std::enable_if_t<std::is_integral<CastFromIntType>::value>>
        static constexpr bool canCast(const CastFromIntType castFrom)
        {
            const CastToIntType castTo = static_cast<CastToIntType>(castFrom);
            const CastFromIntType convertBack = static_cast<CastFromIntType>(castTo);
            return convertBack == castFrom && ((castFrom < 0) == (castTo < 0));
        }

        template<typename EnumType, typename = std::enable_if_t<std::is_enum<EnumType>::value>, typename UnderlyingType = std::underlying_type_t<EnumType>>
        static constexpr UnderlyingType castEnumToUnderlying(const EnumType castFrom)
        {
            return static_cast<UnderlyingType>(castFrom);
        }

        // undefined behaviour if castFrom does not map to a value of EnumType.
        template<typename EnumType, typename = std::enable_if_t<std::is_enum<EnumType>::value>, typename UnderlyingType = std::underlying_type_t<EnumType>>
        static constexpr EnumType castUnderlyingToEnum(const UnderlyingType castFrom)
        {
            return static_cast<EnumType>(castFrom);
        }

        // only works if EnumType values are sequential. Throws std::bad_cast if castFrom is less than MinEnum, or greater than MaxEnum 
        template<typename EnumType, EnumType MinEnum, EnumType MaxEnum, typename = std::enable_if_t<std::is_enum<EnumType>::value>, typename UnderlyingType = std::underlying_type_t<EnumType>>
        static EnumType dynamicCastUnderlyingToSequentialEnum(const UnderlyingType castFrom)
        {
            constexpr UnderlyingType minUt = castEnumToUnderlying(MinEnum);
            constexpr UnderlyingType maxUt = castEnumToUnderlying(MaxEnum);
            if (castFrom < minUt || maxUt < castFrom)
            {
                throw std::bad_cast{};
            }
            return castUnderlyingToEnum<EnumType>(castFrom);
        }


    private:
        CastUtils() = delete;
    };
}
}
