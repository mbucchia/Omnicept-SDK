// (c) Copyright 2020-2021 HP Development Company, L.P.

#pragma once

#include <string>
#include <map>
#include <vector>

namespace HP {
namespace Omnicept {
namespace Abi {

    class DependencyList;

    /*! @brief Domain type for a Dependency. */
    class Dependency
    {
    public:
        /*! @brief Create Dependency
         */
        Dependency() = default;

        /*! @brief Create Dependency from map
         * @param initial a map
         */
        explicit Dependency(std::map<std::string, std::string> initial);

        /*! @brief Create Dependency from string
         * @param initial a string containing JSON object
         *
         * Sample string: R"json({"device":"dummy","vid":"cafe","pid":"babe"})json"
         */
        explicit Dependency(const std::string& initial);

        /*! @brief Default destructor for Dependency
         */
        virtual ~Dependency() = default;

        /*! @brief Checks if attribute exist
         * @param key name of the attribute
         * @return true if exist, else false
         */
        bool has(const std::string& key) const;

        /*! @brief Return all attributes
         * @return attributes in this instance
         */
        std::vector<std::string> attributes() const;

        /*! @brief Retrieve attribute
         * @param key name of the attribute
         * @return value of attribute
         * @throw std::out_of_range if attribute does not exist
         */
        const std::string& get(const std::string& key) const;

        /*! @brief Retrieve number of attributes
         * @return number of attributes
         */
        std::size_t size() const noexcept;

        /*! @brief Adds specified attribute
         * @param key name of the attribute
         * @param value value of the attribute
         */
        void add(const std::string& key, const std::string& value);

        /*! @brief Removes specified attribute
         * @param key name of the attribute
         */
        void remove(const std::string& key);

        bool operator==(const Dependency& other) const;
        bool operator!=(const Dependency& other) const;

        friend std::ostream& operator<<(std::ostream &out, const Dependency&);
        friend std::ostream& operator<<(std::ostream& out, const DependencyList&);

    private:
        std::map<std::string, std::string> m_map;
    };
}
}
}
