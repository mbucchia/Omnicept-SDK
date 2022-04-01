// (c) Copyright 2021 HP Development Company, L.P.

#pragma once
#include<iterator>

namespace HP{
namespace Utils{

    /*! @brief a generic implementation of a random_access_iterator
    *
    * Afaik, stl doesn't provide a non-deprecated one, so i had to write this out.
    */
    template<typename ContiguousContainer>
    class ConstRandomAccessIterator 
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = typename ContiguousContainer::value_type;
        using difference_type = typename ContiguousContainer::difference_type;
        using pointer = typename ContiguousContainer::const_pointer;
        using reference = const value_type&;

        ConstRandomAccessIterator(const ConstRandomAccessIterator&) = default;
        ConstRandomAccessIterator(ConstRandomAccessIterator &&) = default;

        ConstRandomAccessIterator& operator =(const ConstRandomAccessIterator&) = default;
        ConstRandomAccessIterator& operator =(ConstRandomAccessIterator&&) = default;


        reference operator * () const
        {
            return *m_ptr;
        }

        pointer operator -> () const
        {
            return m_ptr;
        }

        ConstRandomAccessIterator& operator ++ ()
        {
            ++m_ptr;
            return *this;
        }

        ConstRandomAccessIterator& operator += (const typename ContiguousContainer::size_type offset)
        {
            m_ptr += offset;
            return *this;
        }

        ConstRandomAccessIterator& operator -= (const typename ContiguousContainer::size_type offset)
        {
            m_ptr -= offset;
            return *this;
        }

        difference_type operator - (const ConstRandomAccessIterator& rhs) const
        {
            return m_ptr - rhs.m_ptr;
        }

        reference operator[](const typename ContiguousContainer::size_type offset)
        {
            return *(*this + offset);
        }

        ConstRandomAccessIterator operator ++ (int)
        {
            auto temp = *this;
            ++m_ptr;
            return temp;
        }

        ConstRandomAccessIterator& operator -- ()
        {
            --m_ptr;
            return *this;
        }

        ConstRandomAccessIterator operator -- (int)
        {
            auto temp = *this;
            --m_ptr;
            return temp;
        }

        friend ConstRandomAccessIterator operator + (const ConstRandomAccessIterator& iter, const typename ContiguousContainer::size_type offset)
        {
            auto temp = iter;
            temp += offset;
            return temp;
        }

        friend ConstRandomAccessIterator operator + ( const typename ContiguousContainer::size_type offset, const ConstRandomAccessIterator& iter )
        {
            return iter + offset;
        }

        friend ConstRandomAccessIterator operator - (const ConstRandomAccessIterator& iter, const typename ContiguousContainer::size_type offset)  
        {
            auto temp = iter;
            temp -= offset;
            return temp;
        }

        bool operator == (const ConstRandomAccessIterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        bool operator != (const ConstRandomAccessIterator& other) const
        {
            return !(*this == other);
        }

        bool operator < (const ConstRandomAccessIterator& other) const
        {
            return m_ptr < other.m_ptr;
        }

        bool operator <= (const ConstRandomAccessIterator& other) const
        {
            return *this < other || *this == other;
        }

        bool operator > (const ConstRandomAccessIterator& other) const
        {
            return !(*this <= other);
        }

        bool operator >= (const ConstRandomAccessIterator& other) const
        {
            return !(*this < other);
        }

    private:
        //only constructible from owning container
        friend ContiguousContainer;
        ConstRandomAccessIterator(pointer ptr) : m_ptr{ ptr }
        {
        }

        ConstRandomAccessIterator() : ConstRandomAccessIterator{ nullptr }
        {
        }

        pointer m_ptr;
    };


}
}
