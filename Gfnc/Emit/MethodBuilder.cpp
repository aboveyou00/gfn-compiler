#include "stdafx.h"
#include "Emit/MethodBuilder.h"

#include "Emit/Opcode.h"
#include "Emit/OpNop.h"
#include "Emit/OpcodeTag.h"

namespace Gfn::Compiler::Emit
{
    MethodBuilder::MethodBuilder()
        : m_isFinalized(false)
    {
    }
    MethodBuilder::~MethodBuilder()
    {
        for (auto it = this->m_pendingTags.begin(); it != this->m_pendingTags.end(); it++)
        {
            delete *it;
        }
        this->m_pendingTags.clear();

        for (auto it = this->m_opcodes.begin(); it != this->m_opcodes.end(); it++)
        {
            delete *it;
        }
        this->m_opcodes.clear();
    }

    OpcodeTag *MethodBuilder::createTag(std::string name)
    {
        this->assertNotFinalized();
        return new OpcodeTag(name);
    }
    OpcodeTag *MethodBuilder::createAnonymousTag()
    {
        return this->createTag("target"s + std::to_string(++this->m_nextAnonymousIndex));
    }

    void MethodBuilder::addTagToNextOpcode(OpcodeTag *tag)
    {
        this->assertNotFinalized();
        this->m_pendingTags.push_back(tag);
    }
    void MethodBuilder::addOpcode(Opcode *op)
    {
        this->assertNotFinalized();
        for (auto it = this->m_pendingTags.begin(); it != this->m_pendingTags.end(); it++)
        {
            op->addTag(*it);
        }
        this->m_pendingTags.clear();
        this->m_opcodes.push_back(op);
    }

    void MethodBuilder::finalize()
    {
        if (this->m_isFinalized) return;
        if (this->m_pendingTags.size() > 0) this->addOpcode(new OpNop());
        this->m_isFinalized = true;
    }
    bool MethodBuilder::isFinalized() const
    {
        return this->m_isFinalized;
    }

    const std::vector<Opcode*> &MethodBuilder::ops() const
    {
        if (!this->m_isFinalized) throw std::logic_error("You can't get a MethodBuilder's opcodes before it has been finalized. Call mb.finalize()"s);
        return this->m_opcodes;
    }

    void MethodBuilder::assertNotFinalized() const
    {
        if (this->isFinalized()) throw std::logic_error("You can't make changes to a MethodBuilder after it has been finalized"s);
    }
}
