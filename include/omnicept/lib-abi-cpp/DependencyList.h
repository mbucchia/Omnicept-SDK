// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <vector>
#include <omnicept/lib-abi-cpp/Dependency.h>

namespace HP {
namespace Omnicept {
namespace Abi {

    /*! @brief Domain type for a DependencyList. */
    class DependencyList
    {
    public:
        DependencyList() = default;
        explicit DependencyList(std::vector<Dependency>);
        virtual ~DependencyList() = default;

        /*! @brief Checks if dependency exist
         * @param dependency dependency to check
         * @return true if exist, else false
         */
        bool has(const Dependency& dependency) const;

        /*! @brief Retrieve number of attributes
         * @return number of attributes
         */
        std::size_t size() const noexcept;

        /*! @brief Adds specified dependency
         * @param dependency the dependency to add
         */
        void add(const Dependency& dependency);

        /*! @brief Removes specified dependency
         * @param dependency the dependency to remove
         */
        void remove(const Dependency& dependency);

        /*! @brief Retrieve a DependencyList instance that optionally depends on all domain message types
         */
        static const DependencyList& getDependencyListForAll();

        /*! @brief Retrieve a DependencyList instance that depends on nothing
         */
        static const DependencyList& getDependencyListForNone();

        /*! @brief Create a DependencyList instance from dependencies description file
         * @param content content of dependencies description file to load
         */
        static DependencyList loadFromDependenciesDescription(const std::string& content);

        bool operator==(const DependencyList& other) const;
        bool operator!=(const DependencyList& other) const;

        friend std::ostream& operator<<(std::ostream& out, const DependencyList&);

    private:
        std::vector<Dependency> m_dependencies;
    };
}
}
}
