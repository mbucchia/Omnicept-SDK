// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include <HP/lib-utils-cpp/ConstRandomAccessIterator.h>
#include <stdexcept>
#include<type_traits>

namespace HP {
namespace Utils{

    /*! @brief a non-owning, immutable 'view' of a contiguous block of memory
    * 
    *  Useful for exposing contiguous subsections of allocated memory to other functions or classes without copying, transferring ownership, or using raw pointers and offsets
    *  Basically std::string_view, but generalized to type T 
    *  Warning: doesn't perform checks on memory to make sure it is contiguous, 
    *  before creating a DataView with a container, you should check whether the memory storage of the container is guranteed to be contiguous (i.e., std::array, std::vector) or not
    */
    template<typename T>
    class DataView
    {
        public:
            using element_type = T;
            using value_type = std::remove_cv_t<T>;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using const_pointer = const T*;
            using reference = T&;
            using const_reference = const T&;
            using const_iterator = ConstRandomAccessIterator<DataView>;
            using iterator = const_iterator;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;
            using reverse_iterator = const_reverse_iterator;


            DataView(const_pointer data, const size_type size) : m_data{ data }, m_size{ size }
            {
            }

            DataView() : DataView{ nullptr, 0 }
            {
            }

            virtual ~DataView() = default;

            bool empty() const
            {
                return size() == 0;
            }

            size_type size() const
            {
                return m_size;
            }

            const_pointer data() const
            {
                return m_data;
            }

            const_iterator cbegin() const
            {
                return const_iterator{ m_data };
            }

            const_iterator cend() const
            {
                return const_iterator{ m_data != nullptr ? m_data + m_size : nullptr };
            }

            const_reverse_iterator crbegin() const
            {
                return const_reverse_iterator{ end() };
            }

            const_reverse_iterator crend() const
            {
                return const_reverse_iterator{ begin() };
            }

            iterator begin() const
            {
                return cbegin();
            }

            iterator end() const
            {
                return cend();
            }

            iterator rbegin() const
            {
                return crbegin();
            }

            iterator rend() const
            {
                return crend();
            }

            const_reference operator [] (const size_t offset) const
            {
                return begin().operator[](offset);
            }

            DataView subView(const size_type offset, const size_type viewSize) const
            {
                if (m_size < offset + viewSize  )
                {
                    throw std::out_of_range{ "subview cannot be greater than the size of the data view" };
                }
                return DataView{ m_data + offset, viewSize };
            }

            DataView first(const size_type numElements) const
            {
                return subView(0, numElements);
            }

            DataView last(const size_type numElements) const
            {
                if (m_size < numElements)
                {
                    throw std::out_of_range{ "subview cannot be greater than the size of the data" };
                }
                return subView(m_size - numElements, numElements);
            }
        
        private:
            size_type m_size;
            const_pointer m_data;
        };
}
}
