#include "stdafx.h"
#include "OpcodeTag.h"

namespace Gfn::Compiler::Emit
{
    OpcodeTag::OpcodeTag(std::string name)
        : m_name(name)
    {
    }
    OpcodeTag::~OpcodeTag()
    {
    }

    const std::string &OpcodeTag::name()
    {
        return this->m_name;
    }
}
