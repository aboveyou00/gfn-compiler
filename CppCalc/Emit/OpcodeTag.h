#pragma once

class OpcodeTag
{
public:
    OpcodeTag(std::string name);
    ~OpcodeTag();

    const std::string &name();

private:
    std::string m_name;
};
