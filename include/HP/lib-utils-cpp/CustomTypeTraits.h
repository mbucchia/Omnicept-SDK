// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <type_traits>

namespace HP {
namespace Utils {

    /*! @brief Provides custom type traits for template functions until we upgrade to c++ 20 and get concepts 
   *  Only add to this if you are adding something not currently in type_traits 
   */
    class CustomTypeTraits final
    {
        CustomTypeTraits() = delete;
    public:

        /*! @brief checks if \p Derived is-a child class of a template base class \p BaseTemplate.
        * 
        * Combined a few answers from https://stackoverflow.com/questions/34672441/stdis-base-of-for-template-classes for solution
        * 
        * Will not compile if \p Derived meets any of the following conditions: 
        *   - \p BaseTemplate is a private parent class of \p Derived (that should be obvious) 
        *   - \p BaseTemplate is a protected (or private) parent class of \p Derived and \p Derived is 'final'
        * 
        * enable-if syntax: to work with std::enable_if_t the enable_if_t<check_v<//>> *= nullptr syntax must be used
        *   template< typename Derived_T, typename std::enable_if_t<is_base_template_of_v<Base_T, Derived_T>>* = nullptr>
        */
        template <template <typename...> class BaseTemplate, typename Derived, typename TCheck = void>
        struct is_base_template_of_impl;

        template <template <typename...> class BaseTemplate, typename Derived>
        using is_base_template_of = typename is_base_template_of_impl<BaseTemplate, Derived>::type;

        template <template <typename...> class BaseTemplate, typename Derived>
        static constexpr bool is_base_template_of_v = is_base_template_of<BaseTemplate, Derived>::value;

        //Derived is a non-final class
        template <template <typename...> class BaseTemplate, typename Derived>
        struct is_base_template_of_impl<BaseTemplate, Derived, std::enable_if_t<std::is_class_v<Derived> && !std::is_final_v<Derived>>> : Derived
        {
            template<typename...T>
            static constexpr std::true_type is_base(BaseTemplate<T...>*);
            static constexpr std::false_type is_base(...);
            using type = decltype(is_base((is_base_template_of_impl*) nullptr));
        };

        //Derived is a final class  
        template <template <typename...> class BaseTemplate, typename Derived>
        struct is_base_template_of_impl<BaseTemplate, Derived, std::enable_if_t<std::is_class_v<Derived>&& std::is_final_v<Derived>>>
        {
            template<typename...T>
            static constexpr std::true_type is_base(BaseTemplate<T ...>*);
            static constexpr std::false_type is_base(...);
            using type = decltype(is_base(std::declval<Derived*>()));
        };

        //Derived is not a class
        template <template <typename...> class BaseTemplate, typename Derived>
        struct is_base_template_of_impl<BaseTemplate, Derived, std::enable_if_t<!std::is_class_v<Derived>>>
        {
            using type = std::false_type;
        };
    };

}
}
