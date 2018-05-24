#include "stdafx.h"
#include "Emit/Opcode.h"

#include "Emit/OpcodeTag.h"

Opcode::Opcode()
{
}
Opcode::~Opcode()
{
    for (auto it = this->m_tags.begin(); it != this->m_tags.end(); it++)
    {
        delete *it;
    }
    this->m_tags.clear();
}

const std::vector<OpcodeTag*> &Opcode::tags() const
{
    return this->m_tags;
}
bool Opcode::hasTag(OpcodeTag *tag) const
{
    auto it = std::find(this->m_tags.begin(), this->m_tags.end(), tag);
    if (it == this->m_tags.end()) return false;
    return true;
}

void Opcode::addTag(OpcodeTag *tag)
{
    this->m_tags.push_back(tag);
}

void Opcode::eval(EvalContext &ctx) const
{
    this->eval(ctx.stack());
}
