#include "stdafx.h"
#include "Runtime/RuntimeType.h"

#include "Runtime/MethodGroup.h"
#include "Runtime/MethodOverload.h"
#include "Emit/OpClt.h"
#include "Emit/OpCgt.h"
#include "Emit/OpLdcI4.h"
#include "Emit/OpCeq.h"
#include "Emit/OpAdd.h"
#include "Emit/OpSub.h"
#include "Emit/OpMul.h"
#include "Emit/OpDiv.h"
#include "Emit/OpMod.h"
#include "Emit/OpNeg.h"

void RuntimeType::prepareRuntimeTypes()
{
    if (s_runtimeTypesPrepared) return;
    s_runtimeTypesPrepared = true;

    s_int32 = new RuntimeType("int"s, true);
    s_boolean = new RuntimeType("bool", true);

    MethodGroup *methods;

    //Int32
    {
        methods = s_int32->getStaticMethods("__op_Equality"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 == int32
            ops.push_back(new OpCeq());
        }));
        methods = s_int32->getStaticMethods("__op_Inequality"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 != int32
            ops.push_back(new OpCeq());
            ops.push_back(new OpLdcI4(0));
            ops.push_back(new OpCeq());
        }));

        methods = s_int32->getStaticMethods("__op_LessThan"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 < int32
            ops.push_back(new OpClt());
        }));
        methods = s_int32->getStaticMethods("__op_GreaterThan"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 > int32
            ops.push_back(new OpCgt());
        }));
        methods = s_int32->getStaticMethods("__op_LessThanOrEqual"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 <= int32
            ops.push_back(new OpCgt());
            ops.push_back(new OpLdcI4(0));
            ops.push_back(new OpCeq());
        }));
        methods = s_int32->getStaticMethods("__op_GreaterThanOrEqual"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 >= int32
            ops.push_back(new OpClt());
            ops.push_back(new OpLdcI4(0));
            ops.push_back(new OpCeq());
        }));

        methods = s_int32->getStaticMethods("__op_Addition"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 + int32
            ops.push_back(new OpAdd());
        }));
        methods = s_int32->getStaticMethods("__op_Subtraction"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 - int32
            ops.push_back(new OpSub());
        }));

        methods = s_int32->getStaticMethods("__op_Multiply"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 * int32
            ops.push_back(new OpMul());
        }));
        methods = s_int32->getStaticMethods("__op_Division"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 / int32
            ops.push_back(new OpDiv());
        }));
        methods = s_int32->getStaticMethods("__op_Modulus"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32, s_int32 }, [](std::vector<Opcode*> &ops) {
            //int32 % int32
            ops.push_back(new OpMod());
        }));

        methods = s_int32->getStaticMethods("__op_UnaryNegation"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32 }, [](std::vector<Opcode*> &ops) {
            //-int32
            ops.push_back(new OpNeg());
        }));
        methods = s_int32->getStaticMethods("__op_UnaryPlus"s, true);
        methods->addOverload(new MethodOverload(s_int32, { s_int32 }, [](std::vector<Opcode*> &ops) {
            //+int32
            ; //NOP
        }));
    }

    //Boolean
    {
        methods = s_boolean->getStaticMethods("__op_Equality"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_boolean, s_boolean }, [](std::vector<Opcode*> &ops) {
            //boolean == boolean
            ops.push_back(new OpCeq());
        }));
        methods = s_boolean->getStaticMethods("__op_Inequality"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_boolean, s_boolean }, [](std::vector<Opcode*> &ops) {
            //boolean != boolean
            ops.push_back(new OpCeq());
            ops.push_back(new OpLdcI4(0));
            ops.push_back(new OpCeq());
        }));

        methods = s_boolean->getStaticMethods("__op_LogicalNot"s, true);
        methods->addOverload(new MethodOverload(s_boolean, { s_boolean }, [](std::vector<Opcode*> &ops) {
            //!boolean
            ops.push_back(new OpLdcI4(0));
            ops.push_back(new OpCeq());
        }));
    }
}

RuntimeType *RuntimeType::int32()
{
    if (!s_runtimeTypesPrepared) throw std::logic_error("You can't access runtime types before they are prepared! Call RuntimeType::prepareRuntimeTypes()"s);
    return s_int32;
}
RuntimeType *RuntimeType::boolean()
{
    if (!s_runtimeTypesPrepared) throw std::logic_error("You can't access runtime types before they are prepared! Call RuntimeType::prepareRuntimeTypes()"s);
    return s_boolean;
}

bool RuntimeType::s_runtimeTypesPrepared = false;

RuntimeType *RuntimeType::s_int32 = nullptr;
RuntimeType *RuntimeType::s_boolean = nullptr;
