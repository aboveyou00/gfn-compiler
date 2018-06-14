#pragma once

namespace Gfn::Compiler::Emit
{
    class OpcodeTag
    {
    public:
        OpcodeTag(std::string name);
        ~OpcodeTag();

        const std::string &name();

    private:
        std::string m_name;
    };
}
