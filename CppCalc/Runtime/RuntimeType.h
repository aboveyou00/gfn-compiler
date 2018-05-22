#pragma once

#include <unordered_map>

class MethodGroup;

class RuntimeType
{
public:
    static void prepareRuntimeTypes();

    static RuntimeType *int32();
    static RuntimeType *boolean();

private:
    static bool s_runtimeTypesPrepared;
    static RuntimeType *s_int32, *s_boolean;

public:
    RuntimeType(bool isPredefined);
    ~RuntimeType();

    bool isPredefined() const;

    MethodGroup *getStaticMethods(std::string name, bool createMethodGroup = false);
    MethodGroup *getInstanceMethods(std::string name, bool createMethodGroup = false);

private:
    bool m_isPredefined;
    std::unordered_map<std::string, MethodGroup*> m_static_methods;
    std::unordered_map<std::string, MethodGroup*> m_instance_methods;
};
