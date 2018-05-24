#include "stdafx.h"
#include "OpcodeTag.h"

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
