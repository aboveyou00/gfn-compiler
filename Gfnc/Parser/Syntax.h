#pragma once

#include <stdexcept>
#include <type_traits>

#include "Util/Cursor.h"

namespace Gfn::Compiler::Parser
{
    class Syntax
    {
    public:
        Syntax(uint32_t startIndex, uint32_t length);
        ~Syntax();

        uint32_t startIndex() const;
        uint32_t length() const;
        uint32_t endIndex() const;

        virtual void repr(std::stringstream &stream) const = 0;
        std::string stringify() const;
        virtual void stringify(std::stringstream &stream) const;
        friend std::stringstream &operator<<(std::stringstream &stream, const Syntax &syntax);
        friend std::ostream &operator<<(std::ostream &stream, const Syntax &syntax);

    private:
        uint32_t m_startIndex, m_length;
    };
}
