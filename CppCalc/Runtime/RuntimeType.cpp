#include "stdafx.h"
#include "Runtime/RuntimeType.h"

#include "Runtime/MethodGroup.h"

RuntimeType::RuntimeType(bool isPredefined)
    : m_isPredefined(isPredefined)
{
}
RuntimeType::~RuntimeType()
{
}

inline bool RuntimeType::isPredefined() const
{
    return this->m_isPredefined;
}

MethodGroup *RuntimeType::getStaticMethods(std::string name, bool createMethodGroup)
{
    auto group = this->m_static_methods[name];
    if (group == nullptr && createMethodGroup)
    {
        group = this->m_static_methods[name] = new MethodGroup();
    }
    return group;
}
MethodGroup *RuntimeType::getInstanceMethods(std::string name, bool createMethodGroup)
{
    auto group = this->m_instance_methods[name];
    if (group == nullptr && createMethodGroup)
    {
        group = this->m_instance_methods[name] = new MethodGroup();
    }
    return group;
}
