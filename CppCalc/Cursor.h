#pragma once

#include <stdexcept>
#include <string>
#include <type_traits>

template <typename T>
class Cursor
{
public:
    Cursor(const T *first, uint32_t length)
        : m_first(first), m_length(length), m_current(0)
    {
    }
    Cursor(const std::string &str)
        : Cursor(str.c_str(), (uint32_t)str.size())
    {
        static_assert(std::is_convertible<T, char>::value, "Can't construct a cursor with that type parameter using (std::string&)");
    }
    ~Cursor()
    {
    }

    uint32_t snapshot() const
    {
        return this->m_current;
    }
    void reset(uint32_t snapshot)
    {
        if (snapshot > this->m_length || snapshot < 0) throw std::out_of_range("Invalid snapshot");
        this->m_current = snapshot;
    }

    const T current() const
    {
        if (this->m_current >= this->m_length) throw std::logic_error("Can't peek at element; you've already consumed all of them!");
        return *(this->m_first + this->m_current);
    }
    void next()
    {
        if (this->m_current >= this->m_length) throw std::logic_error("Can't move to next element; you're already on the last one!");
        this->m_current++;
    }
    void previous()
    {
        if (this->m_current == 0) throw std::logic_error("Can't move to previous element; you're already on the first one!");
        this->m_current--;
    }
    bool isDone() const
    {
        return this->m_current == this->m_length;
    }

private:
    const T *m_first;
    uint32_t m_current;
    uint32_t m_length;
};
