#pragma once

#include <unordered_map>

class MethodGroup;

class RuntimeType
{
public:
    static void prepareRuntimeTypes();

    static RuntimeType *int32();
    static RuntimeType *string();
    static RuntimeType *boolean();

private:
    static bool s_runtimeTypesPrepared;
    static RuntimeType *s_int32, *s_string, *s_boolean;

public:
    RuntimeType(std::string displayName, bool isPredefined);
    ~RuntimeType();

    bool isPredefined() const;
    const std::string &displayName() const;

    MethodGroup *getStaticMethods(std::string name, bool createMethodGroup = false);
    MethodGroup *getInstanceMethods(std::string name, bool createMethodGroup = false);

private:
    std::string m_displayName;
    bool m_isPredefined;
    std::unordered_map<std::string, MethodGroup*> m_static_methods;
    std::unordered_map<std::string, MethodGroup*> m_instance_methods;
};
