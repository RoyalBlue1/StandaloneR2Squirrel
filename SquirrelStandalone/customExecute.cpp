#include "squirrel.h"
#include "hook.h"
#include <queue>
#include <spdlog/spdlog.h>
#include <set>

AUTOHOOK_INIT()


typedef char (*SQVMStartCallType)(HSquirrelVM* a1, SQClosure* a2, int a3, __int64 nInputParams, unsigned int a5, char a6);
typedef long long (*SQVMCallErrorHandlerType)(HSquirrelVM* sqvm, SQObject* a2);
typedef void (*sq_op_loadcopyType)(SQSharedState* a1, SQObject* a2, SQObject* a3);
typedef bool (*sq_op_callType)(HSquirrelVM* a1, SQInstruction* a2, SQObject* a3, int* a4, ...);
typedef long long (*sq_op_precallType)(HSquirrelVM* a1, SQInstruction* a2, SQObject* key);
typedef char (*SQVMGetType)(HSquirrelVM* self, SQObject* key, SQObject* dest, SQObject* temp_reg, char a5, char a6);
typedef int (*sq_errorHanderFor_SQVMGetType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef char (*SQVMNewSlotType)(HSquirrelVM* sqvm, SQObject* self, SQObject* key, SQObject* val, char bstatic);
typedef char (*sq_deleteType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_setType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, char a5);
typedef bool (*sq_op_eqType)(__int64 a1, SQObject* a2, SQObject* a3);
typedef char (*sq_bitwiseOperationType)(HSquirrelVM* a1, int a2, SQObject* a3, SQObject* a4, SQObject* a5);
typedef long long (*sq_sqvm_ReturnType)(HSquirrelVM* a1, int _arg0, int _arg1, SQObject* retval);
typedef SQObject* (*sq_copyObjectType)(SQObject* dest, SQObject* src);
typedef SQTable* (*sq_createTableType)(SQSharedState* sharedState, unsigned int length);;
typedef SQArray* (*sq_createSQArrayType)(SQSharedState* a1, unsigned int a2);
typedef long long (*sq_arrayPushValueType)(SQArray* a1, SQObject* a2);
typedef char (*sq_getParentType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef long long (*sq_compound_arithType)(HSquirrelVM* a1, unsigned int a2, SQObject* a3, SQObject* a4, SQObject* a5);
typedef bool (*sub_2B6C0Type)(HSquirrelVM* a1, __int64 a2, SQObject* a3, SQObject* a4, SQObject* a5);
typedef char (*sub_2E960Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, int a5);
typedef char (*sq_op_increment_prefix_localType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4);
typedef char (*sp_op_increment_prefix_structfieldType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4, int a5);
typedef char (*sub_2EA30Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, int a5);
typedef char (*sub_2E860Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4);
typedef char (*sq_op_increment_postfix_structfieldType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4, int a5);
typedef char (*sq_op_cmpType)(HSquirrelVM* a1, int a2, SQObject* a3, SQObject* a4, SQObject* dest);
typedef char (*sub_2CF10Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef char (*sub_2F0B0Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef char (*sub_2EE20Type)(
    HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4, SQObject* a5, int a6, int a7, int a8, CallInfo* a9);
typedef char (*sub_2EF60Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sub_34A30Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3);
typedef long long (*sub_2D950Type)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, __int64 a4);
typedef long long (*CUtlVectorResizeType)(CUtlVector<SQTrap>* a1, int a2);
typedef long long (*sub_2F2F0Type)(HSquirrelVM* a1, SQObject* a2, int a3, int a4);
typedef long long (*sub_3EA70Type)(void* a1, SQObject* a2, SQObject* a3);
typedef SQObject* (*SQVMToStringType)(HSquirrelVM* a1, SQObject* object, SQObject* res);
typedef char (*sq_op_addType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef long long (*sq_dropStackType)(HSquirrelVM* a1, int a2);
typedef long long (*resizeObjectVectorType)(CUtlVector<SQObject>* a1, int a2);

typedef SQStructInstance* (*sub_35B20Type)(HSquirrelVM* a1, SQObject* a2);
typedef char (*sq_op_subType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_mulType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_divType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_op_moduloType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, SQObject* a4);
typedef char (*sq_compareType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int* a4);
typedef SQObject* (*sq_setObjectToFloatType)(SQObject* a1, float a2);
typedef char (*sub_2E100Type)(HSquirrelVM* sqvm, __int64 a2, int a3, int a4, unsigned int a5);
typedef char (*sq_nativecallType)(HSquirrelVM* sqvm, SQNativeClosure* closure, __int64 a3, unsigned int a4, SQObject* a5, bool* shouldSuspend, bool argCheck);
typedef char (*sq_op_typecastType)(HSquirrelVM* a1, SQObject* a2, SQObject* a3, int a4);
typedef char (*sq_op_check_entity_classType)(HSquirrelVM* a1, SQObject* a2, __int64 a3);
typedef long long (*sub_29A40Type)(SQSharedState* sharedState, SQObject* a2, int* a3);
typedef long long (*sub_63E00Type)(SQSharedState* a1, unsigned int a2, unsigned int* a3);
typedef void (*sub_2EDB0Type)(HSquirrelVM* a1, __int16* a2);
typedef SQString* (*sqStringTableAddType)(StringTable* a1, char* newString, int length);
typedef long long (*sub_BEF0Type)(CUtlVector<SQObject>* a1, unsigned int a2, SQObject* a3);
typedef long long (*SQVMRaise_ErrorType)(HSquirrelVM* a1, const char* a2, ...);
typedef void (*sq_rdbg_hookType)(
    SQDbgServer* dbgServer,
    HSquirrelVM* sqvm,
    int event_type,
    unsigned int line,
    const char* srcFileName,
    int unknown,
    const char* funcName,
    int unknown1);
typedef long long (*sq_rdbg_updateType)(SQDbgServer* dbgServer);



SQVMStartCallType SQVMStartCall;
SQVMCallErrorHandlerType SQVMCallErrorHandler;
sq_op_loadcopyType sq_op_loadcopy;
sq_op_callType sq_op_call;
sq_op_precallType sq_op_precall;
SQVMGetType SQVMGet;
sq_errorHanderFor_SQVMGetType sq_errorHandlerFor_SQVMGet;
SQVMNewSlotType SQVMNewSlot;
sq_deleteType sq_delete;
sq_op_setType sq_op_set;
sq_op_eqType sq_op_eq;
sq_bitwiseOperationType sq_bitwiseOperation;
sq_sqvm_ReturnType sq_sqvm_Return;
sq_copyObjectType sq_copyObject;
sq_createTableType sq_createTable;
sq_createSQArrayType sq_createArray;
sq_arrayPushValueType sq_arrayPushValue;
sq_getParentType sq_getParent;
sq_compound_arithType sq_compound_arith;
sub_2B6C0Type __sub_2B6C0;
sub_2E960Type __sub_2E960;
sq_op_increment_prefix_localType sq_op_increment_prefix_local;
sp_op_increment_prefix_structfieldType sp_op_increment_prefix_structfield;
sub_2EA30Type sq_op_increment_postfix;
sub_2E860Type sq_op_increment_postfix_local;
sq_op_increment_postfix_structfieldType sq_op_increment_postfix_structfield;
sq_op_cmpType sq_op_cmp;
sub_2CF10Type __sub_2CF10;
sub_2F0B0Type __sub_2F0B0;
sub_2EE20Type __sub_2EE20;
sub_2EF60Type __sub_2EF60;
sub_34A30Type __sub_34A30;
sub_2D950Type __sub_2D950;
CUtlVectorResizeType CUtlVectorResize;
sub_2F2F0Type __sub_2F2F0;
sub_3EA70Type __sub_3EA70;
SQVMToStringType SQVMToString;
sq_op_addType sq_op_add;
sq_dropStackType sq_dropStack;
resizeObjectVectorType resizeObjectVector;
sub_35B20Type __sub_35B20;
sq_op_subType sq_op_sub;
sq_op_mulType sq_op_mul;
sq_op_divType sq_op_div;
sq_op_moduloType sq_op_modulo;
sq_compareType sq_compare;
sq_setObjectToFloatType sq_setObjectToFloat;
sub_2E100Type __sub_2E100;
sq_nativecallType sq_nativecall;
sq_op_typecastType sq_op_typecast;
sq_op_check_entity_classType sq_op_check_entity_class;
sub_29A40Type __sub_29A40;
sub_63E00Type __sub_63E00;
sub_2EDB0Type __sub_2EDB0;
sqStringTableAddType sqStringTableAdd;
sub_BEF0Type __sub_BEF0;
SQVMRaise_ErrorType SQVMRaise_Error;
sq_rdbg_hookType sq_rdbg_hook;
sq_rdbg_updateType sq_rdbg_update;

SQObject* globalClosure;

void callLineDebugger(SQDbgServer* dbgServer, HSquirrelVM* sqvm, int line, const char* srcFileName) {
    sq_rdbg_hook(dbgServer, sqvm, 'l', line, srcFileName, 0, 0, 0);
    if (dbgServer->_autoupdate && sq_rdbg_update(dbgServer))
        g_pSquirrel->__sq_raiseerror(sqvm, "invalid socket");
}

void* callReturnDebugger(SQDbgServer* dbgServer,HSquirrelVM* sqvm)

float fsqrt(float x)
{
    return sqrtf(x);
}

struct debugInstruction
{
    int index;
    int stackbase;
    SQInstruction* inst;
};
static std::queue<debugInstruction> instDebug;

struct workingInstruction
{
    size_t originalPosition;
    size_t newPosition;
    SQInstruction instruction;
};

//#define PRINT_INSTRUCTION_DEBUG
AUTOHOOK(SQFuncState__BuildProto,server.dll + 0x672D0,SQFunctionProto*,__fastcall,(SQFuncState* funcState))
{

#ifdef PRINT_INSTRUCTION_DEBUG
    const char* debugFunctionName = "InitItems";
    bool shouldPrintFunc =
        funcState->funcName._Type == OT_STRING && (strcmp(funcState->funcName._VAL.asString->_val, debugFunctionName) == 0);
    if (shouldPrintFunc)
    {
        char* funcName = funcState->funcName._VAL.asString->_val;
        spdlog::info("Function compile name:{}", std::string(funcName));
        for (int i = 0; i < funcState->_instructionsSize; i++)
        {
            workingInstruction inst;
            inst.originalPosition = i;
            inst.newPosition = -1;
            inst.instruction = funcState->_instructions[i];
            spdlog::info(
                "Index {} Instruction {} arg1 {} arg0 {} arg2 {} arg3 {}",
                i,
                std::string(sq_OpToString(inst.instruction.op)),
                inst.instruction.arg1,
                inst.instruction.output,
                inst.instruction.arg2,
                inst.instruction.arg3);
        }
        for (int i = 0; i < funcState->_lineInfoSize; i++)
        {
            spdlog::info("LineInfo Line: {} instruction {}", funcState->_lineInfoData[i].line, funcState->_lineInfoData[i].op);
        }
        for (int i = 0; i < funcState->_localvarinfoSize; i++)
        {
            SQLocalVarInfo* info = &funcState->_localvarinfoData[i];
            spdlog::info("{}", *info);
        }
    }
#endif
    std::vector<workingInstruction> newInstructions;
    for (unsigned int i = 0; i < funcState->_instructionsSize; i++)
    {
        workingInstruction inst;
        inst.originalPosition = i;
        inst.newPosition = -1;
        inst.instruction = funcState->_instructions[i];
        for (unsigned int j = 0; j < funcState->_lineInfoSize; j++)
        {
            if (funcState->_lineInfoData[j].op == i)
            {
                workingInstruction lineInst;
                lineInst.instruction.op = _OP_LINE;
                lineInst.instruction.arg1 = funcState->_lineInfoData[j].line;
                lineInst.instruction.output = 0;
                lineInst.instruction.arg2 = 0;
                lineInst.instruction.arg3 = 0;
                lineInst.originalPosition = -1;
                lineInst.newPosition = newInstructions.size();
                newInstructions.push_back(lineInst);
            }
        }
        inst.newPosition = newInstructions.size();
        newInstructions.push_back(inst);
    }
    for (auto& inst : newInstructions)
    {
        switch (inst.instruction.op)
        {
        case _OP_JMP:
        case _OP_JZ:
        case _OP_JNZ:
        case _OP_INCREMENT_LOCAL_DISCARD_JMP:
            for (auto& inst2 : newInstructions)
            {
                if (inst2.originalPosition == inst.originalPosition + inst.instruction.arg1)
                {
                    inst.instruction.arg1 =(int) (inst2.newPosition - inst.newPosition);
                    break;
                }
            }
            break;
        case _OP_FOREACH:
            if (inst.instruction.output == 0)
                break;
            for (auto& inst2 : newInstructions)
            {
                if (inst2.originalPosition == inst.originalPosition + inst.instruction.output)
                {
                    inst.instruction.output = (int)(inst2.newPosition - inst.newPosition);
                    inst2.instruction.arg1 = inst.instruction.output * -1;
                    break;
                }
            }
            break;
        case _OP_FOREACH_STATICARRAY_NEXT:
        case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_NEXT:
            for (auto& inst2 : newInstructions)
            {
                if (inst2.originalPosition == inst.originalPosition + inst.instruction.output)
                {
                    inst.instruction.output = (int)(inst2.newPosition - inst.newPosition);
                    break;
                }
            }
            break;
        }
    }

    while (funcState->_instructionsAllocatedSize < newInstructions.size())
    {
        g_pSquirrel->reallocinstructionvector(&funcState->_instructions, funcState->_instructionsAllocatedSize * 2);
    }

    for (unsigned int i = 0; i < funcState->_lineInfoSize; i++)
    {

        for (auto& inst : newInstructions)
        {
            if (inst.originalPosition == funcState->_lineInfoData[i].op)
            {
                funcState->_lineInfoData[i].op = (int)inst.newPosition - 1;
                break;
            }
        }
    }

    for (unsigned int i = 0; i < funcState->_localvarinfoSize; i++)
    {
        SQLocalVarInfo* info = &funcState->_localvarinfoData[i];
        for (auto& inst : newInstructions)
        {
            if (inst.originalPosition == info->_start_op)
            {
                info->_start_op = (int)inst.newPosition;
                break;
            }
        }
        for (auto& inst : newInstructions)
        {
            if (inst.originalPosition == info->_end_op)
            {
                info->_end_op = (int)inst.newPosition;
                break;
            }
        }
    }

    for (int i = 0; i < newInstructions.size(); i++)
    {
        workingInstruction inst = newInstructions[i];
        funcState->_instructions[i] = inst.instruction;
    }
    funcState->_instructionsSize =(unsigned int)newInstructions.size();

#ifdef PRINT_INSTRUCTION_DEBUG
    if (shouldPrintFunc)
    {
        char* funcName = funcState->funcName._VAL.asString->_val;
        spdlog::info("Function compile name:{}", std::string(funcName));
        for (int i = 0; i < funcState->_instructionsSize; i++)
        {
            workingInstruction inst;
            inst.originalPosition = i;
            inst.newPosition = -1;
            inst.instruction = funcState->_instructions[i];
            spdlog::info(
                "Index {} Instruction {} arg1 {} arg0 {} arg2 {} arg3 {}",
                i,
                std::string(sq_OpToString(inst.instruction.op)),
                inst.instruction.arg1,
                inst.instruction.output,
                inst.instruction.arg2,
                inst.instruction.arg3);
        }
        for (int i = 0; i < funcState->_lineInfoSize; i++)
        {
            spdlog::info("LineInfo Line: {} instruction {}", funcState->_lineInfoData[i].line, funcState->_lineInfoData[i].op);
        }
        for (int i = 0; i < funcState->_localvarinfoSize; i++)
        {
            SQLocalVarInfo* info = &funcState->_localvarinfoData[i];
            spdlog::info("{}", *info);
        }
    }
#endif

    return SQFuncState__BuildProto(funcState);
}
/**/


std::map<int,int> executedOPCodes; 
AUTOHOOK(SQVMExecute,server.dll+ 0x2F950,long long,__fastcall,( HSquirrelVM* sqvm, SQObject* closure, int paramAmount, int stackbase, SQObject* outres, int throwerror, unsigned int calltype))
{
    //spdlog::info("Running custom execute with {}", closure->_VAL.asClosure->_function._VAL.asFuncProto->funcName._VAL.asString->_val);
    //spdlog::info("paramAmount = {} stackbase = {} throwerror = {} calltype = {}", paramAmount, stackbase, throwerror, calltype);
    // only runs on server right now so no check for context

    ++sqvm->_nnativecalls;
    SQSharedState* sharedState = sqvm->sharedState;
    int traps = 0;
    SQInstruction* Instruction; // r14
    std::set<SQString> dasd;
    HSquirrelVM* savedSharedState = sharedState->_currentThreadMaybe;
    sharedState->_currentThreadMaybe = sqvm;
    if (calltype)
    {
        if ((calltype == 1) || (calltype <= 3))
        {
            traps = sqvm->trapAmount;
            sqvm->ci->_root = sqvm->_suspended_root;
            sqvm->ci->_vargs_base = sqvm->_suspend_varargs;
            sqvm->_suspended = 0;
            if (calltype == 3)
                goto label_errorHandler;
        }
    }
    else
    {
        sqvm->temp_reg = *closure;
        if (!SQVMStartCall(
            sqvm, sqvm->temp_reg._VAL.asClosure, sqvm->_top - paramAmount, (unsigned int)paramAmount, stackbase, 0))
        {
            if (!sqvm->ci)
                SQVMCallErrorHandler(sqvm, &sqvm->_lasterror);
            sharedState->_currentThreadMaybe = savedSharedState;
            --sqvm->_nnativecalls;
            return 0;
        }
        sqvm->ci->_root = 1;
    }

    

exeption_restore:
    while (2)
    {
        sqvm->ci->ip = &sqvm->ci->ip[1];
        Instruction = sqvm->ci->ip;
        debugInstruction deInst;
        deInst.index = (int)(Instruction - sqvm->ci->closure._VAL.asFuncProto->instruction);
        deInst.stackbase = sqvm->_stackbase;
        deInst.inst = Instruction;
        //instDebug.emplace(deInst);
        if (instDebug.size() > 300)
            instDebug.pop();

        //char instString[512];
        //sqInstructionToString(instString, 512, Instruction, sqvm);
        //spdlog::info("{}", std::string(instString));

        if (executedOPCodes.count(Instruction->op)) {
            executedOPCodes[Instruction->op]++;
        }
        else {
            executedOPCodes[Instruction->op] = 1;
        }

        switch (Instruction->op)
        {
        case _OP_LINE:
        {
            if (sqvm->sharedState->debugServer)
            {
                const char* name = "UNKNOWN";
                if (sqvm->ci->closure._Type == OT_FUNCPROTO && sqvm->ci->closure._VAL.asFuncProto->fileName._Type == OT_STRING)
                    name = sqvm->ci->closure._VAL.asFuncProto->fileName._VAL.asString->_val;

                callLineDebugger(sqvm->sharedState->debugServer, sqvm, Instruction->arg1, name);
            }

            continue;
        }
        case _OP_LOAD:
        {
            SQObject* target;
            SQObject* source;
            source = &sqvm->ci->_literals[Instruction->arg1];
            target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = *source;
            continue;
        }
        case _OP_LOADCOPY:
            sq_op_loadcopy(
                sqvm->sharedState, &sqvm->ci->_literals[Instruction->arg1], &sqvm->_stackOfCurrentFunction[Instruction->output]);
            continue;
        case _OP_LOADINT:
        {
            sqvm->_stackOfCurrentFunction[Instruction->output] = Instruction->arg1;
            continue;
        }
        case _OP_LOADFLOAT:
        {
            sqvm->_stackOfCurrentFunction[Instruction->output] = *(float*)&Instruction->arg1;
            continue;
        }
        case _OP_DLOAD:
        { // Double load
            SQObject* source = &sqvm->ci->_literals[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = *source;
            source = &sqvm->ci->_literals[(unsigned __int16)Instruction->arg3];
            target = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            *target = *source;
            continue;
        }
        case _OP_TAILCALL:
            if (!sq_op_call(sqvm, Instruction, outres, &traps, 1))
                goto label_errorHandler;
            if (sqvm->_suspended)
            {
                sharedState->_currentThreadMaybe = savedSharedState;
                --sqvm->_nnativecalls;
                return 1;
            }

            continue;
        case _OP_CALL:
            if (!sq_op_call(sqvm, Instruction, outres, &traps, 0))
                goto label_errorHandler;
            if (sqvm->_suspended)
            {
                sharedState->_currentThreadMaybe = savedSharedState;
                --sqvm->_nnativecalls;
                return 1;
            }
            continue;
        case _OP_PREPCALL:
            if (!sq_op_precall(sqvm, Instruction, &sqvm->_stackOfCurrentFunction[Instruction->arg1]))
                goto label_errorHandler;
            continue;
        case _OP_PREPCALLK:
            if (!sq_op_precall(sqvm, Instruction, &sqvm->ci->_literals[Instruction->arg1]))
                goto label_errorHandler;
            continue;
        case _OP_GETK:
        {
            SQObject res;
            if (!SQVMGet(
                sqvm, &sqvm->_stackOfCurrentFunction[Instruction->arg2], &sqvm->ci->_literals[Instruction->arg1], &res, 0, 1))
            {
                sq_errorHandlerFor_SQVMGet(
                    sqvm, &sqvm->_stackOfCurrentFunction[Instruction->arg2], &sqvm->ci->_literals[Instruction->arg1]);
                goto label_errorHandler;
            }
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = res;

            continue;
        }
        case _OP_MOVE:
        {

            SQObject* source = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = *source;
            continue;
        }
        case _OP_NEWSLOT:
            if (!SQVMNewSlot(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg3],
                0))
                goto label_errorHandler;
            continue;
        case _OP_DELETE:
        {
            SQObject res;
            SQObject* key = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            SQObject* self = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (!sq_delete(sqvm, self, key, &res))
            {
                goto label_errorHandler;
            }
            *target = res;
            continue;
        }
        case _OP_SET:
            if (!sq_op_set(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg3],
                1))
            {
                if (sqvm->_lasterror._Type == OT_NULL)
                    sq_errorHandlerFor_SQVMGet(
                        sqvm,
                        &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                        &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]);
                goto label_errorHandler;
            }
            continue;
        case _OP_GET:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!SQVMGet(sqvm, arg1Obj, arg2Obj, &res, 0, 1))
            {
                sq_errorHandlerFor_SQVMGet(sqvm, arg1Obj, arg2Obj);
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_EQ:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sq_op_eq(
                0,
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[Instruction->arg1])
                ? true
                : false;

            continue;
        }
        case _OP_NE:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sq_op_eq(
                0,
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[Instruction->arg1])
                ? false
                : true;
            continue;
        }
        case _OP_BITW:
        {
            int operation = (unsigned __int16)Instruction->arg3;
            SQObject* operator1 = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* operator2 = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;
            if (!sq_bitwiseOperation(sqvm, operation, &res, operator1, operator2))
            {
                goto label_errorHandler;
            }
            *target = res;
            continue;
        }
        case _OP_RETURN:
            if (!(unsigned int)sq_sqvm_Return(sqvm, Instruction->output, Instruction->arg1, &sqvm->temp_reg))
                continue;
            *outres = sqvm->temp_reg;

            sharedState->_currentThreadMaybe = savedSharedState;
            //spdlog::info("Return of {}", closure->_VAL.asClosure->_function._VAL.asFuncProto->funcName._VAL.asString->_val);
            --sqvm->_nnativecalls;
            return 1;
        case _OP_LOADNULLS:
            for (int i = 0; i < Instruction->arg1; i++)
            {
                SQObject* target = &sqvm->_stackOfCurrentFunction[i + Instruction->output];
                target->Null();
            }
            continue;
        case _OP_LOADROOTTABLE:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sqvm->_roottable_object;
            continue;
        }
        case _OP_LOADBOOL:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = (bool)Instruction->arg1;
            continue;
        }
        case _OP_DMOVE:
        {
            SQObject* source = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v94
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // v95
            *target = *source;

            source = &sqvm->_stackOfCurrentFunction[Instruction->arg3];
            target = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            *target = *source;
            continue;
        }
        case _OP_JMP:
            sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
            continue;
        case _OP_JNZ:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];

            if ((target->_Type & 0xB) != 0)
            {
                if (target->_VAL.asInteger)
                {
                    sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
                }
            }
            else
            {
                if (target->_Type != OT_FLOAT)
                {
                    sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
                }
                else if (target->_VAL.asFloat != 0.0)
                {
                    sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
                }
            }
            continue;
        }
        case _OP_JZ:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if ((target->_Type & 0xB) != 0)
            {
                if (!(target->_VAL.asInteger))
                {
                    sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
                }
            }
            else if (target->_Type == OT_FLOAT && target->_VAL.asFloat == 0.0)
            {
                sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
            }
            continue;
        }
        case _OP_LOADFREEVAR:
        {
            SQClosure* cl = sqvm->ci->obj10._VAL.asClosure;
            SQObject* source = &cl->_outervalues[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = *source;
            continue;
        }
        case _OP_VARGC:
        {
            int vargc = (unsigned int)*((__int16*)&sqvm->ci->_root + 2);
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];

            *target = vargc;
            continue;
        }
        case _OP_GETVARGV://TODO REDO
        {
            SQObject* indexObject = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v100
            if (sqvm->ci->_vargs_size <= 0)
            {
                SQVMRaise_Error(sqvm, "this function doesn't have var args");
                goto label_errorHandler;
            }

            if (!(indexObject->_Type & (1 << 0x1Au)))
            {
                const char* typeName = sq_getTypeName(indexObject->_Type);
                SQVMRaise_Error(sqvm, "indexing 'vargv' with %s", typeName);
                goto label_errorHandler;
            }
            int index; // v14
            if (indexObject->_Type == OT_FLOAT)
                index = (unsigned int)indexObject->_VAL.asFloat;
            else
                index = indexObject->_VAL.asInteger;
            if (index < 0 || index >= sqvm->ci->_vargs_size)
            {
                SQVMRaise_Error(sqvm, "vargv index out of range");
                goto label_errorHandler;
            }
            SQObject* vargv = &sqvm->_vargsstack[(index + sqvm->ci->_vargs_base)]; // v103
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // v104
            *target = *vargv;
            continue;
        }
        case _OP_NEWTABLE:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sq_createTable(sqvm->sharedState, Instruction->arg1);

            continue;
        }
        case _OP_NEWARRAY:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sq_createArray(sqvm->sharedState, 0);
            //spdlog::info("C6F0 in new Array is {:X}", (long long)target->_VAL.asArray->_values);
            resizeObjectVector(&target->_VAL.asArray->_values, Instruction->arg1);
            continue; //TODO refcounting
        }
        case _OP_APPENDARRAY:
        {
            SQObject* data;
            if (Instruction->arg3)
                data = &sqvm->ci->_literals[Instruction->arg1];
            else
                data = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            sq_arrayPushValue(sqvm->_stackOfCurrentFunction[Instruction->output]._VAL.asArray, data);
            continue;
        }
        case _OP_GETPARENT:
        {
            SQObject res; // v387 v388

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (!(unsigned __int8)sq_getParent(sqvm, &sqvm->_stackOfCurrentFunction[Instruction->arg1], &res))
            {
                goto label_errorHandler;
            }
            *target = res;

            continue;
        }
        case _OP_COMPOUND_ARITH:
            if (!sq_compound_arith(
                sqvm,
                (unsigned __int16)Instruction->arg3,
                &sqvm->_stackOfCurrentFunction[HIWORD(Instruction->arg1)],
                &sqvm->_stackOfCurrentFunction[Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[LOWORD(Instruction->arg1)]))
                goto label_errorHandler;
            continue;
        case _OP_COMPOUND_ARITH_LOCAL:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (!__sub_2B6C0(sqvm, (unsigned __int16)Instruction->arg3, arg1Obj, arg1Obj, arg2Obj))
                goto label_errorHandler;
            continue;
        }

        case _OP_INCREMENT_PREFIX:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!__sub_2E960(sqvm, &res, arg1Obj, arg2Obj, *(BYTE*)&Instruction->arg3))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_INCREMENT_PREFIX_LOCAL:
            if (sq_op_increment_prefix_local(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->output],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                *(BYTE*)&Instruction->arg3))
            {
                continue;
            }
            goto label_errorHandler;
        case _OP_INCREMENT_PREFIX_STRUCTFIELD:
            if (!(unsigned __int8)sp_op_increment_prefix_structfield(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->output],
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                (unsigned __int16)Instruction->arg2,
                *(BYTE*)&Instruction->arg3))
                goto label_errorHandler;
            continue;
        case _OP_INCREMENT_POSTFIX:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!(unsigned __int8)sq_op_increment_postfix(sqvm, &res, arg1Obj, arg2Obj, *(char*)&Instruction->arg3))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_INCREMENT_POSTFIX_LOCAL:
        {

            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v161
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // closure

            SQObject res; // v382 v383


            if (!sq_op_increment_postfix_local(sqvm, &res, arg2Obj, *(BYTE*)&Instruction->arg3))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_INCREMENT_POSTFIX_STRUCTFIELD:
            if (!sq_op_increment_postfix_structfield(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->output],
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                (unsigned __int16)Instruction->arg2,
                *(BYTE*)&Instruction->arg3))
            {
                goto label_errorHandler;
            }
            continue;
        case _OP_CMP:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v166
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v167
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // closure
            SQObject res; // v386

            if (!sq_op_cmp(sqvm, (unsigned __int16)Instruction->arg3, arg2Obj, arg1Obj, &res))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_EXISTS:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = SQVMGet(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->temp_reg,
                1,
                0)
                ? true
                : false;
            continue;
        }
        case _OP_INSTANCEOF:
        {
            SQObject* classObj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* instanceObj = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (((classObj->_Type != OT_CLAAS) || (instanceObj->_Type & 0x408000) == 0))
            {
                const char* classTypeName = sq_getTypeName(classObj->_Type);
                const char* instanceTypeName = sq_getTypeName(instanceObj->_Type);
                SQVMRaise_Error(
                    sqvm, "cannot apply instanceof between a %s and a %s", instanceTypeName, classTypeName);
                goto label_errorHandler;
            }

            long long classOfInstance = *(long long*)(instanceObj->_VAL.as64Integer + 56);
            bool isInstance = false;
            while (classOfInstance)
            {
                if (classOfInstance == classObj->_VAL.as64Integer)
                {
                    isInstance = true;
                    break;
                }
                classOfInstance = *(long long*)(classOfInstance + 56);
            }
            *target = isInstance;

            continue;
        }
        case _OP_NEG:
        {
            SQObject res;

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (!__sub_2CF10(sqvm, &res, &sqvm->_stackOfCurrentFunction[Instruction->arg1]))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_NOT:
        {

            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];


            if ((arg1Obj->_Type & 0xB) != 0)
            {
                *target = arg1Obj->_VAL.asInteger == 0;
            }
            else if (arg1Obj->_Type == OT_FLOAT)
            {
                *target = arg1Obj->_VAL.asFloat == 0.0;
            }
            else
            {
                *target = false;

            }

            continue;
        }
        case _OP_BWNOT:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // type = v188
            if (arg1Obj->_Type != OT_INTEGER)
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "attempt to perform a bitwise op on a %s", arg1TypeName);
                goto label_errorHandler;
            }
            
            sqvm->_stackOfCurrentFunction[Instruction->output] =  ~sqvm->_stackOfCurrentFunction[Instruction->arg1]._VAL.asInteger;
            continue;
        }
        case _OP_CLOSURE:
        {

            SQObject* arg1Obj = &sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[Instruction->arg1];

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res; // v365 v366


            if (!(unsigned __int8)__sub_2F0B0(sqvm, &res, arg1Obj))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_FOREACH:
            if (!__sub_2EE20(
                sqvm,
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg3],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2 + 1],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2 + 2],
                0,
                Instruction->output,
                Instruction->arg1,
                sqvm->ci))
            {
                goto label_errorHandler;
            }
            continue;
        case _OP_FOREACH_STATICARRAY_START:
        {
            SQObject* arg1_2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1 + 2]; // v201
            *arg1_2Obj = 0;
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v202
            *arg1Obj = 0;

            // TODO fix struct behaviour
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            SQObject* arg1_1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1 + 1]; // closure
            SQObject* structObj = &arg2Obj->_VAL.asStructInstance->data[arg2Obj->_structOffset]; // TODO struct

            *arg1_1Obj = *structObj;
            continue;
        }
        case _OP_FOREACH_STATICARRAY_NEXT:
        {

            // TODO fix struct behaviour
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg2 + 2];
            int arg2Int = ++arg2Obj->_VAL.asInteger;
            if (arg2Int >= (unsigned __int16)Instruction->arg3)
                continue;
            sqvm->_stackOfCurrentFunction[Instruction->arg2]= arg2Int;


            sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2 + 1] =
                sqvm->_stackOfCurrentFunction[Instruction->arg1]
                ._VAL.asStructInstance->data[sqvm->_stackOfCurrentFunction[Instruction->arg1]._structOffset + arg2Int];
            sqvm->ci->ip = &sqvm->ci->ip[Instruction->output];
            continue;
        }
        case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_START:
        {
            SQObject* arg1_2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1 + 2]; // v201
            *arg1_2Obj = 0;
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v202
            *arg1Obj = 0;

            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v10
            SQObject* arg1_1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1 + 1]; // closure
            *arg1_1Obj = *arg2Obj;
            continue;
        }
        case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_NEXT:
        {

            SQObject* arg2_2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg2 + 2];
            int arg2_2Int = ++arg2_2Obj->_VAL.asInteger;
            if (arg2_2Int >= (unsigned __int16)Instruction->arg3)
            {
                continue;
            }
            sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]=  arg2_2Int;

            sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2 + 1] = sqvm->_stackOfCurrentFunction[(__int8)Instruction->arg1];
            sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2 + 1]._structOffset += arg2_2Int * (Instruction->arg1 >> 8);
            sqvm->ci->ip = &sqvm->ci->ip[Instruction->output];

            continue;
        }
        case _OP_DELEGATE:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!__sub_2EF60(sqvm, &res, arg1Obj, arg2Obj))
            {
                goto label_errorHandler;
            }

            *target = res;
            continue;
        }
        case _OP_CLONE:
        {

            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;


            if (!__sub_34A30(sqvm, arg1Obj, &res))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "cloning a %s", arg1TypeName);
                goto label_errorHandler;
            }

            *target = res;
            continue;
        }
        case _OP_TYPEOF:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            __sub_2D950(sqvm, arg1Obj, &res, 0);

            *target = res;
            continue;
        }
        case _OP_PUSHTRAP:
        { // TODO cleanup maybe redo


            long long offset = 16 * (Instruction->arg1 + (((long long)sqvm->ci->ip - (sqvm->ci->closure._VAL.as64Integer + 272)) * 16));

            long long pointer = sqvm->ci->closure._VAL.as64Integer + offset + 272;
            if (sqvm->_traps.allocated <= sqvm->_traps.size)
                CUtlVectorResize(&sqvm->_traps, 2 * sqvm->_traps.size);
            SQTrap* trapPointer = &sqvm->_traps.data[sqvm->_traps.size];
            sqvm->_traps.size++;
            if (trapPointer)
            {
                trapPointer->_top = sqvm->_top;
                trapPointer->_stackbase = sqvm->_stackbase;
                trapPointer->Instruction = pointer;
                trapPointer->unknown = Instruction->output;
            }
            ++traps;
            ++sqvm->ci->_etraps;
            continue;
        }
        case _OP_POPTRAP:

            for (int i = 0; i < Instruction->output; i++)
            {
                --sqvm->_traps.size;
                --traps;
                --sqvm->ci->_etraps;
            }
            continue;
        case _OP_THROW:
            __sub_35B20(sqvm, &sqvm->_stackOfCurrentFunction[Instruction->output]);
            goto label_errorHandler;
        case _OP_CLASS:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;


            if (!(unsigned __int8)__sub_2F2F0(sqvm, &res, Instruction->arg1, (unsigned __int16)Instruction->arg2))
            {
                goto label_errorHandler;
            }

            *target = res;
            continue;
        }
        case _OP_NEWSLOTA:
            if (!SQVMNewSlot(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg3],
                (Instruction->output & 2) != 0))
                goto label_errorHandler;
            if ((Instruction->output & 1) != 0)
                __sub_3EA70(
                    (void*)&sqvm->_stackOfCurrentFunction[Instruction->arg1]._VAL.asString->vtable,
                    &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                    &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2 - 1]);
            continue;
        case _OP_EQ_LITERAL:
        {
            SQObject* arg1Obj = &sqvm->ci->_literals[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sq_op_eq(0, arg2Obj, arg1Obj) ? true : false;
            continue;
        }
        case _OP_NE_LITERAL:
        {
            SQObject* arg1Obj = &sqvm->ci->_literals[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sq_op_eq(0, arg2Obj, arg1Obj) ? false : true;

            continue;
        }
        case _OP_ASSERT_FAILED:
        {
            SQObject testObjectName;
            SQVMToString(sqvm, &sqvm->_stackOfCurrentFunction[Instruction->arg1], &testObjectName);
            SQVMRaise_Error(sqvm, "Assertion failed: %s", (const char*)(&testObjectName._VAL.asString->_val));
            goto label_errorHandler;
        }
        case _OP_ADD:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v87
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v88
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!sq_op_add(sqvm, &res, arg2Obj, arg1Obj))
            {
                goto label_errorHandler;
            }

            *target = res;
            continue;
        }
        case _OP_SUB:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v87
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v88
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!sq_op_sub(sqvm, &res, arg2Obj, arg1Obj))
            {
                goto label_errorHandler;
            }
            //spdlog::info("Sub result Type = {} value {:X}", sq_getTypeName(res._Type), res._VAL.as64Integer);

            *target = res;
            continue;
        }
        case _OP_MUL:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v87
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v88
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;

            if (!sq_op_mul(sqvm, &res, arg2Obj, arg1Obj))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_DIV:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v87
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v88
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;


            if (!sq_op_div(sqvm, &res, arg2Obj, arg1Obj))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_MOD:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v87
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v88
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject res;


            if (!sq_op_modulo(sqvm, &res, arg2Obj, arg1Obj))
            {
                goto label_errorHandler;
            }

            *target = res;

            continue;
        }
        case _OP_CMP_JZ:
        {
            int intRes;
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            //spdlog::info("arg1Type {} arg2Type {}", sq_getTypeName(arg1Obj->_Type), sq_getTypeName(arg2Obj->_Type));
            if (!sq_compare(
                sqvm,
                arg2Obj,
                arg1Obj,
                &intRes))
            {
                goto label_errorHandler;
            }

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // v170
            sqvm->ci->ip = &sqvm->ci->ip[1];


            if ((Instruction->arg3 == 0 && intRes > 0) || (Instruction->arg3 == 2 && intRes >= 0) ||
                (Instruction->arg3 == 3 && intRes < 0) || (Instruction->arg3 == 4 && intRes <= 0))
            {
                *target = true;
                continue;
            }

            *target = false;
            sqvm->ci->ip = &sqvm->ci->ip[sqvm->ci->ip->arg1];
            continue;
        }
        case _OP_INCREMENT_LOCAL_DISCARD_JMP:
        {
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v164
            if (arg2Obj->_Type == OT_INTEGER)
            {
                arg2Obj->_VAL.asInteger += *(BYTE*)&Instruction->arg3;
                sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
            }
            else if (arg2Obj->_Type == OT_FLOAT)
            {
                arg2Obj->_VAL.asFloat = (float)(*(BYTE*)&Instruction->arg3) + arg2Obj->_VAL.asFloat;
                sqvm->ci->ip = &sqvm->ci->ip[Instruction->arg1];
            }
            else
            {
                const char* arg2TypeName = sq_getTypeName(arg2Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot increment or decrement %s", arg2TypeName);
                goto label_errorHandler;
            }
            continue;
        }
        case _OP_NEWVECTOR:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg2];
            SQObject* arg3Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg3];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];

            if (!((arg1Obj->_Type & SQOBJECT_NUMERIC) && (arg2Obj->_Type & SQOBJECT_NUMERIC) && (arg3Obj->_Type & SQOBJECT_NUMERIC)))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                const char* arg2TypeName = sq_getTypeName(arg2Obj->_Type);
                const char* arg3TypeName = sq_getTypeName(arg3Obj->_Type);
                SQVMRaise_Error(
                    sqvm, "Vector component types are <%s, %s, %s>; must be integer or float", arg1TypeName, arg2TypeName, arg3TypeName);
                goto label_errorHandler;
            }

            SQVector targetVec;
            if (arg1Obj->_Type == OT_INTEGER)
            {
                targetVec.x = (float)arg1Obj->_VAL.asInteger;
            }
            else
            {
                targetVec.x = arg1Obj->_VAL.asFloat;
            }
            if (arg2Obj->_Type == OT_INTEGER)
            {
                targetVec.y = (float)arg2Obj->_VAL.asInteger;
            }
            else
            {
                targetVec.y = arg2Obj->_VAL.asFloat;
            }
            if (arg3Obj->_Type == OT_INTEGER)
            {
                targetVec.z = (float)arg3Obj->_VAL.asInteger;
            }
            else
            {
                targetVec.z = arg3Obj->_VAL.asFloat;
            }
            *target = targetVec;
            continue;
        }
        case _OP_ZEROVECTOR:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQVector targetVec;
            *target = targetVec;
            continue;
        }
        case _OP_GET_VECTOR_COMPONENT:
        {

            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (arg1Obj->_Type != 0x40000)
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot get vector component (.x/y/z) of %s", arg1TypeName);
                goto label_errorHandler;
            }
            SQVector* arg1Vec = (SQVector*)arg1Obj;
            float output = 0.0;
            switch (Instruction->arg2)
            {
            case 0:
                output = arg1Vec->x;
                break;
            case 1:
                output = arg1Vec->y;
                break;
            case 2:
                output = arg1Vec->z;
                break;
            default:
                SQVMRaise_Error(sqvm, "Invalid vector component index %d", Instruction->arg2);
                goto label_errorHandler;
            }
            sqvm->_stackOfCurrentFunction[Instruction->output] = output;
            continue;
        }

        case _OP_SET_VECTOR_COMPONENT:
        {

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (target->_Type != OT_VECTOR)
            {
                const char* targetTypeName = sq_getTypeName(target->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component (.x/y/z) of %s", targetTypeName);
                goto label_errorHandler;
            }

            if (!(arg1Obj->_Type & SQOBJECT_NUMERIC))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component to %s", arg1TypeName);
                goto label_errorHandler;
            }

            float arg1Float;
            if (arg1Obj->_Type == OT_INTEGER)
            {
                arg1Float = (float)arg1Obj->_VAL.asInteger;
            }
            else
            {
                arg1Float = arg1Obj->_VAL.asFloat;
            }
            SQVector* targetVec = (SQVector*)target;
            switch (Instruction->arg2)
            {
            case 0:
                targetVec->x = arg1Float;
                break;
            case 1:
                targetVec->y = arg1Float;
                break;
            case 2:
                targetVec->z = arg1Float;
                break;
            }

            continue;
        }
        case _OP_VECTOR_COMPONENT_MINUSEQ:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (target->_Type != OT_VECTOR)
            {
                const char* targetTypeName = sq_getTypeName(target->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component (.x/y/z) of %s", targetTypeName);
                goto label_errorHandler;
            }

            if (!(arg1Obj->_Type & SQOBJECT_NUMERIC))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component to %s", arg1TypeName);
                goto label_errorHandler;
            }
            float factor;
            if (arg1Obj->_Type == OT_INTEGER)
            {
                factor = (float)arg1Obj->_VAL.asInteger;
            }
            else
            {
                factor = arg1Obj->_VAL.asFloat;
            }
            SQVector* targetVec = (SQVector*)target;
            switch (Instruction->arg2)
            {
            case 0:
                targetVec->x = targetVec->x - factor;
                break;
            case 1:
                targetVec->y = targetVec->y - factor;
                break;
            case 2:
                targetVec->z = targetVec->z - factor;
                break;
            }
            continue;
        }
        case _OP_VECTOR_COMPONENT_PLUSEQ:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (target->_Type != OT_VECTOR)
            {
                const char* targetTypeName = sq_getTypeName(target->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component (.x/y/z) of %s", targetTypeName);
                goto label_errorHandler;
            }

            if (!(arg1Obj->_Type & SQOBJECT_NUMERIC))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component to %s", arg1TypeName);
                goto label_errorHandler;
            }
            float factor;
            if (arg1Obj->_Type == OT_INTEGER)
            {
                factor = (float)arg1Obj->_VAL.asInteger;
            }
            else
            {
                factor = arg1Obj->_VAL.asFloat;
            }
            SQVector* targetVec = (SQVector*)target;
            switch (Instruction->arg2)
            {
            case 0:
                targetVec->x = targetVec->x + factor;
                break;
            case 1:
                targetVec->y = targetVec->y + factor;
                break;
            case 2:
                targetVec->z = targetVec->z + factor;
                break;
            }
            continue;
        }
        case _OP_VECTOR_COMPONENT_MULEQ:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (target->_Type != OT_VECTOR)
            {
                const char* targetTypeName = sq_getTypeName(target->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component (.x/y/z) of %s", targetTypeName);
                goto label_errorHandler;
            }

            if (!(arg1Obj->_Type & SQOBJECT_NUMERIC))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component to %s", arg1TypeName);
                goto label_errorHandler;
            }
            float factor;
            if (arg1Obj->_Type == OT_INTEGER)
            {
                factor = (float)arg1Obj->_VAL.asInteger;
            }
            else
            {
                factor = arg1Obj->_VAL.asFloat;
            }
            SQVector* targetVec = (SQVector*)target;
            switch (Instruction->arg2)
            {
            case 0:
                targetVec->x = targetVec->x * factor;
                break;
            case 1:
                targetVec->y = targetVec->y * factor;
                break;
            case 2:
                targetVec->z = targetVec->z * factor;
                break;
            }
            continue;
        }
        case _OP_VECTOR_COMPONENT_DIVEQ:
        {

            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (target->_Type != OT_VECTOR)
            {
                const char* targetTypeName = sq_getTypeName(target->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component (.x/y/z) of %s", targetTypeName);
                goto label_errorHandler;
            }

            if (!(arg1Obj->_Type & SQOBJECT_NUMERIC))
            {
                const char* arg1TypeName = sq_getTypeName(arg1Obj->_Type);
                SQVMRaise_Error(sqvm, "Cannot set vector component to %s", arg1TypeName);
                goto label_errorHandler;
            }
            float divisor;
            if (arg1Obj->_Type == OT_INTEGER)
            {
                divisor = (float)arg1Obj->_VAL.asInteger;
            }
            else
            {
                divisor = arg1Obj->_VAL.asFloat;
            }
            SQVector* targetVec = (SQVector*)target;
            switch (Instruction->arg2)
            {
            case 0:
                targetVec->x = targetVec->x / divisor;
                break;
            case 1:
                targetVec->y = targetVec->y / divisor;
                break;
            case 2:
                targetVec->z = targetVec->z / divisor;
                break;
            }
            continue;
        }
        case _OP_VECTOR_NORMALIZE:
        {
            SQVector* vec = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (vec->_Type != OT_VECTOR)
            {
                const char* typeName = sq_getTypeName(vec->_Type);
                SQVMRaise_Error(sqvm, "Cannot normalize %s", typeName);
                goto label_errorHandler;
            }

            float normalizationFactor = 1.0f / (sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z) + 1.1754944e-38f);  //add float min to not devide by 0
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQVector targetVec;

            targetVec.x = normalizationFactor * vec->x;
            targetVec.y = normalizationFactor * vec->y;
            targetVec.z = normalizationFactor * vec->z;
            *target = targetVec;
            continue;
        }
        case _OP_VECTOR_NORMALIZE_IN_PLACE:
        {
            SQVector* vec = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (vec->_Type != OT_VECTOR)
            {
                const char* typeName = sq_getTypeName(vec->_Type);
                SQVMRaise_Error(sqvm, "Cannot normalize %s", typeName);
                goto label_errorHandler;
            }
            float vecLength = sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
            float normalizationFactor = 1.0f / (vecLength + 1.1754944e-38f); //add float min to not devide by 0
            vec->x *= normalizationFactor;
            vec->y *= normalizationFactor;
            vec->z *= normalizationFactor;

            sqvm->_stackOfCurrentFunction[Instruction->output] = vecLength;

            continue;
        }
        case _OP_VECTOR_DOT_PRODUCT:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot dot %s with %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }

            float dotProduct = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
            sqvm->_stackOfCurrentFunction[Instruction->output] = dotProduct;
            continue;
        }
        case _OP_VECTOR_DOT_PRODUCT2D:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot dot %s with %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            float dotProduct = vec1->x * vec2->x + vec1->y * vec2->y;
            sqvm->_stackOfCurrentFunction[Instruction->output] = dotProduct;
            continue;
        }
        case _OP_VECTOR_CROSS_PRODUCT:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQVector targetVec;
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot cross %s with %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            targetVec.x = vec1->y * vec2->z - vec1->z * vec2->y;
            targetVec.y = vec1->z * vec2->x - vec1->x * vec2->z;
            targetVec.z = vec1->x * vec2->y - vec1->y * vec2->x;
            *target = targetVec;
            continue;
        }
        case _OP_VECTOR_CROSS_PRODUCT2D:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot cross %s with %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            float crossProduct = vec1->x * vec2->y - vec1->y * vec2->x;
            sqvm->_stackOfCurrentFunction[Instruction->output] = crossProduct;
            continue;
        }

        case _OP_VECTOR_LENGTH:
        {
            SQVector* vec = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (vec->_Type != OT_VECTOR)
            {
                const char* typeName = sq_getTypeName(vec->_Type);
                SQVMRaise_Error(sqvm, "Cannot get length of %s", typeName);
                goto label_errorHandler;
            }
            float vecLength = fsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
            sqvm->_stackOfCurrentFunction[Instruction->output] = vecLength;
            continue;
        }
        case _OP_VECTOR_LENGTHSQR:
        {
            SQVector* vec = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (vec->_Type != OT_VECTOR)
            {
                const char* typeName = sq_getTypeName(vec->_Type);
                SQVMRaise_Error(sqvm, "Cannot get squared length of %s", typeName);
                goto label_errorHandler;
            }
            float vecLength = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
            sqvm->_stackOfCurrentFunction[Instruction->output] = vecLength;
            continue;
        }
        case _OP_VECTOR_LENGTH2D:
        {
            SQVector* vec = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (vec->_Type != OT_VECTOR)
            {
                const char* typeName = sq_getTypeName(vec->_Type);
                SQVMRaise_Error(sqvm, "Cannot get 2D length of %s", typeName);
                goto label_errorHandler;
            }
            float vecLength = fsqrt(vec->x * vec->x + vec->y * vec->y);
            sqvm->_stackOfCurrentFunction[Instruction->output] = vecLength;
            continue;
        }
        case _OP_VECTOR_LENGTH2DSQR:
        {
            SQVector* vec = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            if (vec->_Type != OT_VECTOR)
            {
                const char* typeName = sq_getTypeName(vec->_Type);
                SQVMRaise_Error(sqvm, "Cannot get 2D squared length of %s", typeName);
                goto label_errorHandler;
            }
            float vecLength = vec->x * vec->x + vec->y * vec->y;
            sqvm->_stackOfCurrentFunction[Instruction->output] = vecLength;
            continue;
        }
        case _OP_VECTOR_DISTANCE:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot get distance between %s and %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            float x = vec2->x - vec1->x;
            float y = vec2->y - vec1->y;
            float z = vec2->z - vec1->z;
            float distance = fsqrt(x * x + y * y + z * z);
            sqvm->_stackOfCurrentFunction[Instruction->output] = distance;
            continue;
        }
        case _OP_VECTOR_DISTANCESQR:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot get squared distance between %s and %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            float x = vec2->x - vec1->x;
            float y = vec2->y - vec1->y;
            float z = vec2->z - vec1->z;
            float distance = x * x + y * y + z * z;
            sqvm->_stackOfCurrentFunction[Instruction->output] = distance;
            continue;
        }
        case _OP_VECTOR_DISTANCE2D:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(sqvm, "Cannot get 2D distance between %s and %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            float x = vec2->x - vec1->x;
            float y = vec2->y - vec1->y;
            float distance = fsqrt(x * x + y * y);
            sqvm->_stackOfCurrentFunction[Instruction->output] = distance;
            continue;
        }
        case _OP_VECTOR_DISTANCE2DSQR:
        {
            SQVector* vec1 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQVector* vec2 = (SQVector*)&sqvm->_stackOfCurrentFunction[Instruction->arg2];
            if (vec1->_Type != OT_VECTOR || vec2->_Type != OT_VECTOR)
            {
                const char* vec1TypeName = sq_getTypeName(vec1->_Type);
                const char* vec2TypeName = sq_getTypeName(vec2->_Type);
                SQVMRaise_Error(
                    sqvm, "Cannot get 2D squared distance between %s and %s", vec1TypeName, vec2TypeName);
                goto label_errorHandler;
            }
            float x = vec2->x - vec1->x;
            float y = vec2->y - vec1->y;
            float distance = x * x + y * y;
            sqvm->_stackOfCurrentFunction[Instruction->output] = distance;
            continue;
        }
        case _OP_INCREMENT_LOCAL_DISCARD:
        {
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v14
            if (arg2Obj->_Type == OT_INTEGER)
            {
                arg2Obj->_VAL.asInteger += *(char*)&Instruction->arg3;
            }
            else
            {
                if (arg2Obj->_Type != OT_FLOAT)
                {
                    const char* arg2TypeName = sq_getTypeName(arg2Obj->_Type);
                    SQVMRaise_Error(sqvm, "Cannot increment or decrement %s", arg2TypeName);
                    goto label_errorHandler;
                }

                arg2Obj->_VAL.asFloat = (float)(*(char*)&Instruction->arg3) + arg2Obj->_VAL.asFloat;
            }
            continue;
        }
        case _OP_FASTCALL:
        {
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]; // v36
            *arg2Obj = *sqvm->_stackOfCurrentFunction;

            if (!__sub_2E100(
                sqvm,
                sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[Instruction->arg1]._VAL.as64Integer,
                Instruction->output,
                (unsigned __int16)Instruction->arg3,
                sqvm->_stackbase + (unsigned __int16)Instruction->arg2))
            {
                goto label_errorHandler;
            }
            continue;
        }
        case _OP_FASTCALL_NATIVE:
        case _OP_FASTCALL_NATIVE_ARGTYPECHECK:
        {
            SQObject* arg1Obj = &sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[Instruction->arg1]; // v40
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            *arg2Obj = *sqvm->_stackOfCurrentFunction;
            SQObject res; // src
            bool shouldSuspend;

            int newStackBase = (sqvm->_stackbase + (unsigned __int16)Instruction->arg2);
            bool argCheck = Instruction->op == _OP_FASTCALL_NATIVE_ARGTYPECHECK;
            //spdlog::info(
            //	"Calling native with name {} and param3 = {} funcPointer = {:X} l2116",
            //	arg1Obj->_VAL.asNativeClosure->_name->_val,
            //	Instruction->arg3,
            //	arg1Obj->_VAL.asNativeClosure->functionPointer);
            if (!sq_nativecall(
                sqvm, arg1Obj->_VAL.asNativeClosure, (unsigned __int16)Instruction->arg3, newStackBase, &res, &shouldSuspend, argCheck))
            {
                goto label_errorHandler;
            }
            if (shouldSuspend || sqvm->unknown_field_11C && sqvm->_nnativecalls == 1)
            {

                sqvm->_suspended = 1;
                sqvm->_suspended_target = Instruction->output;
                sqvm->trapAmount = traps;
                sqvm->_suspended_root = sqvm->ci->_root;
                sqvm->_suspend_varargs = *(int*)&sqvm->ci->_vargs_size;
                if (sqvm->unknown_field_11C == 0)
                    *outres = res;
                else
                    *outres = sqvm->_object_120;
                sqvm->unknown_field_11C = 0;
                sharedState->_currentThreadMaybe = savedSharedState;
                --sqvm->_nnativecalls;
                return 1;
            }

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // closure
            *target = res;

            continue;
        }
        case _OP_FASTCALL_ENV:
            if (!__sub_2E100(
                sqvm,
                sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[Instruction->arg1]._VAL.as64Integer,
                Instruction->output,
                (unsigned __int16)Instruction->arg3,
                sqvm->_stackbase + (unsigned __int16)Instruction->arg2))
            {
                goto label_errorHandler;
            }
            continue;

        case _OP_FASTCALL_NATIVE_ENV:
        case _OP_FASTCALL_NATIVE_ENV_ARGTYPECHECK:
        {
            bool localCalltype;
            SQObject* arg1Obj = &sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[Instruction->arg1];
            int newStackbase = sqvm->_stackbase + (unsigned int)(unsigned __int16)Instruction->arg2;
            bool argTypeCheck = Instruction->op == _OP_FASTCALL_NATIVE_ENV_ARGTYPECHECK;
            SQObject res; // v360

            //spdlog::info(
            //	"Calling native with name {} and param3 = {} l2169", arg1Obj->_VAL.asNativeClosure->_name->_val, Instruction->arg3);
            if (!sq_nativecall(
                sqvm,
                arg1Obj->_VAL.asNativeClosure,
                (unsigned __int16)Instruction->arg3,
                newStackbase,
                &res,
                &localCalltype,
                argTypeCheck))
            {
                goto label_errorHandler;
            }
            if (localCalltype || *(&sqvm->_suspend_varargs + 1) && sqvm->_nnativecalls == 1)
            {
                sqvm->_suspended = 1;
                sqvm->_suspended_target = Instruction->output;
                sqvm->trapAmount = traps;
                sqvm->_suspended_root = sqvm->ci->_root;
                sqvm->_suspend_varargs = *(&sqvm->ci->_root + 1);
                if (*(&sqvm->_suspend_varargs + 1) == 0)
                    *outres = res;
                else
                    *outres = sqvm->_object_120;
                *(&sqvm->_suspend_varargs + 1) = 0;
                sharedState->_currentThreadMaybe = savedSharedState;
                --sqvm->_nnativecalls;
                return 1;
            }
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]; // closure
            *target = res;

            continue;
        }

        case _OP_LOADGLOBALARRAY:
        {

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = sharedState->_globalsArray;
            continue;
        }
        case _OP_GETGLOBAL:
        {

            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject* arg1Obj = &sharedState->_globalsArray._VAL.asStructInstance->data[Instruction->arg1];
            *target = *arg1Obj;

            continue;
        }
        case _OP_SETGLOBAL:
        {
            SQObject* target = &sharedState->_globalsArray._VAL.asStructInstance->data[Instruction->arg1];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            *target = *arg2Obj;
            continue;
        }
        case _OP_COMPOUND_ARITH_GLOBAL:
        {
            SQObject* arg1Obj = &sharedState->_globalsArray._VAL.asStructInstance->data[Instruction->arg1];
            if (!__sub_2B6C0(
                sqvm,
                (unsigned __int16)Instruction->arg3,
                arg1Obj,
                arg1Obj,
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]))
            {
                goto label_errorHandler;
            }
            continue;
        }

        case _OP_GETSTRUCTFIELD:
        {
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1];
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            int fieldOffset = arg1Obj->_structOffset + (unsigned __int16)Instruction->arg2;
            SQObject* field = &arg1Obj->_VAL.asStructInstance->data[fieldOffset];
            *target = *field;
            continue;
        }
        case _OP_SETSTRUCTFIELD:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            int fieldOffset = Instruction->arg1 + target->_structOffset;
            SQObject* structField = &target->_VAL.asStructInstance->data[fieldOffset];
            *structField = *arg2Obj;
            continue;
        }
        case _OP_COMPOUND_ARITH_STRUCTFIELD:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output]._VAL.asStructInstance->data[Instruction->arg1 + sqvm->_stackOfCurrentFunction[Instruction->output]._structOffset];
            SQObject* arg2Obj = &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2];
            if (!__sub_2B6C0(sqvm, (unsigned __int16)Instruction->arg3, target, target, arg2Obj))
                goto label_errorHandler;
            continue;
        }
        case _OP_NEWSTRUCT:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = (SQStructInstance*)__sub_63E00(
                sqvm->sharedState,
                Instruction->arg1,
                *(unsigned int**)(*(long long*)&sqvm->ci->closure._VAL.asClosure->gap_C8[8] + 8 * (unsigned __int16)Instruction->arg2));
            continue;
        }
        case _OP_GETSUBSTRUCT:
        {
            SQObject* source = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v10
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            *target = *source;
            target->_structOffset += (unsigned __int16)Instruction->arg2;
            continue;
        }
        case _OP_GETSUBSTRUCT_DYNAMIC:
        {
            int factor = sqvm->_stackOfCurrentFunction[Instruction->arg2]._VAL.asInteger;
            int arg1_0 = Instruction->arg1 & 0xFFFF;
            int arg1_1 = Instruction->arg1 >> 16;
            if (factor >= arg1_1)
            {
                SQVMRaise_Error(sqvm, "Array index %d doesn't index size of %d", factor, arg1_1);
                goto label_errorHandler;
            }

            sqvm->_stackOfCurrentFunction[Instruction->output] = sqvm->_stackOfCurrentFunction[arg1_0];
            sqvm->_stackOfCurrentFunction[Instruction->output]._structOffset += factor * (unsigned __int16)Instruction->arg3;
            continue;
        }
        case _OP_TYPECAST:
            if (!sq_op_typecast(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->output],
                &sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2],
                Instruction->arg1))
            {
                const char* arg1TypeName = sq_getTypeName(Instruction->arg1);
                const char* arg2TypeName = sq_getTypeName(sqvm->_stackOfCurrentFunction[(unsigned __int16)Instruction->arg2]._Type);
                SQVMRaise_Error(sqvm, "Cannot cast type \"%s\" to \"%s\"", arg2TypeName, arg1TypeName);
                goto label_errorHandler;
            }
            continue;
        case _OP_TYPECHECK:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (!((int)target->_Type == (unsigned int)Instruction->arg1 ||
                (unsigned int)Instruction->arg1 == OT_ENTITY && target->_Type == OT_NULL))
            {
                const char* objectTypeName = sq_getTypeName(target->_Type);
                const char* testTypeName = sq_getTypeName((unsigned int)Instruction->arg1);
                SQVMRaise_Error(sqvm, "Expected type \"%s\", found type \"%s\"", testTypeName, objectTypeName);
                goto label_errorHandler;
            }
            continue;
        }

        case _OP_TYPECHECK_ORNULL:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            if (!(target->_Type == (unsigned int)Instruction->arg1 || target->_Type == OT_NULL))
            {
                const char* objectTypeName = sq_getTypeName(target->_Type);
                const char* testedTypeName = sq_getTypeName((unsigned int)Instruction->arg1);
                SQVMRaise_Error(
                    sqvm, "Expected type \"%s ornull\", found type \"%s\"", testedTypeName, objectTypeName);
                goto label_errorHandler;
            }
            continue;
        }

        case _OP_TYPECHECK_NOTNULL:
        {
            if (sqvm->_stackOfCurrentFunction[Instruction->output]._Type != OT_NULL)
            {
                SQVMRaise_Error(sqvm, "Expected non-null value, found \"null\"");
                goto label_errorHandler;
            }
            continue;
        }

        case _OP_CHECK_ENTITY_CLASS:

            if (!sq_op_check_entity_class(
                sqvm,
                &sqvm->_stackOfCurrentFunction[Instruction->arg1],
                *(long long*)(*(long long*)(sqvm->ci->closure._VAL.as64Integer + 256) + 8i64 * (unsigned __int16)Instruction->arg2))) //TODO reverse struct
            {
                goto label_errorHandler;
            }

            continue;
        case _OP_UNREACHABLE:
            SQVMRaise_Error(sqvm, "Execution reached script marked as unreachable");
            goto label_errorHandler;
        case _OP_ARRAY_RESIZE:
        {
            SQObject* target = &sqvm->_stackOfCurrentFunction[Instruction->output];
            SQObject* arg1Obj = &sqvm->_stackOfCurrentFunction[Instruction->arg1]; // v310=val
            SQArray* targetArray = target->_VAL.asArray; // v309

            if (arg1Obj->_VAL.asInteger < 0)
            {
                SQVMRaise_Error(sqvm, "Cannot resize to negative size %d", (unsigned int)arg1Obj->_VAL.asInteger);
                goto label_errorHandler;
            }
            unsigned int oldSize = targetArray->_values.size;
            __sub_BEF0(
                &targetArray->_values, arg1Obj->_VAL.asInteger, globalClosure); // global variable
            if ((targetArray->_values.size) <= targetArray->_values.allocated >> 2)
            {
                if (targetArray->_values.size > 4)
                    resizeObjectVector(&targetArray->_values, targetArray->_values.size);
            }
            int* value = (int*)sqvm->ci->closure._VAL.asFuncProto->unknownArray_D0[Instruction->arg2];

            while (oldSize < (unsigned int)arg1Obj->_VAL.asInteger)
                __sub_29A40(sqvm->sharedState, &targetArray->_values.data[oldSize++], value);


            continue;
        }
        default:
            continue;
        }
    }

label_errorHandler:
    {
        SQObject currentError; // a2
        currentError = sqvm->_lasterror; // v312

        int lastTop = sqvm->_top; // v315
        int n = 0; // v316
        if (!sqvm->ci)
        {
            sqvm->_lasterror = currentError;
            sqvm->sharedState->_currentThreadMaybe = savedSharedState;
            --sqvm->_nnativecalls;
            return 0;
        }
        if (traps)
        {

            while (sqvm->ci->obj10._Type != OT_NATIVECLOSURE || !n)
            {
                if (sqvm->ci->_etraps > 0)
                {
                    SQTrap* trap = &sqvm->_traps.data[sqvm->_traps.size-1];
                    sqvm->ci->ip = (SQInstruction*)trap->Instruction;
                    sqvm->_top = trap->_top;
                    sqvm->_stackbase = trap->_stackbase; // v324
                    sqvm->_stackOfCurrentFunction = &sqvm->_stack[sqvm->_stackbase];
                    SQObject* newError = &sqvm->_stack[sqvm->_stackbase + trap->unknown]; // 325
                    *newError = currentError;
                    --sqvm->_traps.size;
                    --traps;
                    --sqvm->ci->_etraps;
                    if (lastTop >= sqvm->_top)
                        sq_dropStack(sqvm, lastTop);

                    goto exeption_restore; // this continues execution in exeptionHander
                }
                __sub_2EDB0(sqvm, (__int16*)&sqvm->ci->_root + 2);

                --sqvm->_callsstacksize;
                sqvm->ci->obj10.Null();

                sqvm->ci->closure.Null();

                if (sqvm->_callsstacksize)
                {
                    sqvm->ci = &sqvm->_callsstack[sqvm->_callsstacksize - 1];
                }
                else
                {
                    sqvm->ci = 0i64;
                }
                ++n;
                if (!sqvm->_callsstacksize)
                    break;
            }
        }
        else if (throwerror)
        {
            char instString[512];
            while (instDebug.size() > 0)
            {
                debugInstruction inst = instDebug.front();
                sqInstructionToString(instString, 512, inst.inst, inst.index, inst.stackbase);
                spdlog::info("{}", std::string(instString));
                instDebug.pop();
            }



            std::map<int, std::string> functions;
            int lastBase = (int)(sqvm->_stackOfCurrentFunction - sqvm->_stack);
            for (int j = sqvm->_callsstacksize - 1; j >= 0; j--)
            {
                if (sqvm->_callsstack[j].closure._Type != OT_CLOSURE)
                    continue;
                spdlog::info("Function {} with base {}", std::string(sqvm->_callsstack[j].closure._VAL.asFuncProto->funcName._VAL.asString->_val), lastBase);
                functions.emplace(
                    lastBase, std::string(sqvm->_callsstack[j].closure._VAL.asFuncProto->funcName._VAL.asString->_val));
                lastBase -= sqvm->_callsstack[j]._stackbaseOffset;

            }

            //for (int i = 0; &sqvm->_stackOfCurrentFunction[i] < &sqvm->_stack[sqvm->_top]; i++)
            int functionStackIndex = 0;
            std::string funcname = "";
            for (int i = 0; i < sqvm->_top; i++)
            {

                spdlog::info("index {} with object {} functionstackIndex {} of function {}", i, sqvm->_stack[i], functionStackIndex, funcname);
                functionStackIndex++;
                if (functions.count(i + 1) > 0)
                {
                    funcname = functions[i];
                    functionStackIndex = 0;
                }
            }
            SQVMCallErrorHandler(sqvm, &currentError);
        }

        if (sqvm->ci)
        {
            do
            {
                sqvm->_stackbase -= sqvm->ci->_stackbaseOffset;
                sqvm->_stackOfCurrentFunction = &sqvm->_stack[sqvm->_stackbase];
                sqvm->_top = sqvm->_stackbase + sqvm->ci->_unknown;
                __sub_2EDB0(sqvm, (__int16*)&sqvm->ci->_root + 2);
                --sqvm->_callsstacksize;
                sqvm->ci->obj10.Null();
                sqvm->ci->closure.Null();
                if (sqvm->_callsstacksize)
                {
                    sqvm->ci = &sqvm->_callsstack[sqvm->_callsstacksize - 1];

                    if (sqvm->ci && sqvm->ci->obj10._Type == OT_NATIVECLOSURE)
                        break;
                }
                else
                {
                    sqvm->ci = 0i64;
                }
            } while ((sqvm->ci && (!sqvm->ci->_root)) && sqvm->_callsstacksize);
        }
        if (lastTop >= sqvm->_top)
            sq_dropStack(sqvm, lastTop);
        sqvm->_lasterror = currentError;

        sharedState->_currentThreadMaybe = savedSharedState;
        --sqvm->_nnativecalls;
        return 0;
    }
}
/**/

ON_DLL_LOAD("server.dll", CustomExecute, (CModule module)) {



    SQVMStartCall = module.Offset(0x2DD20).As<SQVMStartCallType>();
    SQVMCallErrorHandler = module.Offset(0x33A70).As<SQVMCallErrorHandlerType>();
    sq_op_loadcopy = module.Offset(0x3d390).As<sq_op_loadcopyType>();
    sq_op_call = module.Offset(0x2C440).As<sq_op_callType>();
    sq_op_precall = module.Offset(0x2C2B0).As<sq_op_precallType>();
    SQVMGet = module.Offset(0x343A0).As<SQVMGetType>();
    sq_errorHandlerFor_SQVMGet = module.Offset(0x35B80).As<sq_errorHanderFor_SQVMGetType>();
    SQVMNewSlot = module.Offset(0x34B30).As<SQVMNewSlotType>();
    sq_delete = module.Offset(0x34CF0).As<sq_deleteType>();
    sq_op_set = module.Offset(0x34810).As<sq_op_setType>();
    sq_op_eq = module.Offset(0x2F460).As<sq_op_eqType>();
    sq_bitwiseOperation = module.Offset(0x2B590).As<sq_bitwiseOperationType>();
    sq_sqvm_Return = module.Offset(0x2E490).As<sq_sqvm_ReturnType>();
    sq_copyObject = module.Offset(0x1370).As<sq_copyObjectType>();
    sq_createTable = module.Offset(0x1580).As<sq_createTableType>();
    sq_createArray = module.Offset(0x1800).As<sq_createSQArrayType>();
    sq_arrayPushValue = module.Offset(0x1A20).As<sq_arrayPushValueType>();
    sq_getParent = module.Offset(0x2F740).As<sq_getParentType>();
    sq_compound_arith = module.Offset(0x2E670).As<sq_compound_arithType>();
    __sub_2B6C0 = module.Offset(0x2B6C0).As<sub_2B6C0Type>();
    __sub_2E960 = module.Offset(0x2E960).As<sub_2E960Type>();
    sq_op_increment_prefix_local = module.Offset(0x2E780).As<sq_op_increment_prefix_localType>();
    sp_op_increment_prefix_structfield =
        module.Offset(0x2EB70).As<sp_op_increment_prefix_structfieldType>();
    sq_op_increment_postfix = module.Offset(0x2EA30).As<sub_2EA30Type>();
    sq_op_increment_postfix_local = module.Offset(0x2E860).As<sub_2E860Type>();
    sq_op_increment_postfix_structfield =
        module.Offset(0x2EC60).As<sq_op_increment_postfix_structfieldType>();
    sq_op_cmp = module.Offset(0x2D1E0).As<sq_op_cmpType>();
    __sub_2CF10 = module.Offset(0x2CF10).As<sub_2CF10Type>();
    __sub_2F0B0 = module.Offset(0x2F0B0).As<sub_2F0B0Type>();
    __sub_2EE20 = module.Offset(0x2EE20).As<sub_2EE20Type>();
    __sub_2EF60 = module.Offset(0x2EF60).As<sub_2EF60Type>();
    __sub_34A30 = module.Offset(0x34A30).As<sub_34A30Type>();
    __sub_2D950 = module.Offset(0x2D950).As<sub_2D950Type>();
    CUtlVectorResize = module.Offset(0x35800).As<CUtlVectorResizeType>();
    __sub_2F2F0 = module.Offset(0x2F2F0).As<sub_2F2F0Type>();
    __sub_3EA70 = module.Offset(0x3EA70).As<sub_3EA70Type>();
    SQVMToString = module.Offset(0x2D2D0).As<SQVMToStringType>();
    sq_op_add = module.Offset(0x2BAF0).As<sq_op_addType>();
    sq_dropStack = module.Offset(0x2B500).As<sq_dropStackType>();
    resizeObjectVector = module.Offset(0xC6F0).As<resizeObjectVectorType>();
    __sub_35B20 = module.Offset(0x35B20).As<sub_35B20Type>();
    sq_op_sub = module.Offset(0x2BC80).As<sq_op_subType>();
    sq_op_mul = module.Offset(0x2BE10).As<sq_op_mulType>();
    sq_op_div = module.Offset(0x2C020).As<sq_op_divType>();
    sq_op_modulo = module.Offset(0x2C1C0).As<sq_op_moduloType>();
    sq_compare = module.Offset(0x2D080).As<sq_compareType>();
    sq_setObjectToFloat = module.Offset(0x27430).As<sq_setObjectToFloatType>();
    __sub_2E100 = module.Offset(0x2E100).As<sub_2E100Type>();
    sq_nativecall = module.Offset(0x33E00).As<sq_nativecallType>();
    sq_op_typecast = module.Offset(0x2F500).As<sq_op_typecastType>();
    sq_op_check_entity_class = module.Offset(0x2F6B0).As<sq_op_check_entity_classType>();
    __sub_29A40 = module.Offset(0x29A40).As<sub_29A40Type>();
    __sub_63E00 = module.Offset(0x63E00).As<sub_63E00Type>();
    __sub_2EDB0 = module.Offset(0x2EDB0).As<sub_2EDB0Type>();
    __sub_BEF0 = module.Offset(0xBEF0).As<sub_BEF0Type>();
    SQVMRaise_Error = module.Offset(0x35A10).As<SQVMRaise_ErrorType>();
    globalClosure = module.Offset(0xBCCE30).As<SQObject*>();
    sq_rdbg_hook = module.Offset(0x6F680).As<sq_rdbg_hookType>();
    sq_rdbg_update = module.Offset(0x6C670).As<sq_rdbg_updateType>();


    AUTOHOOK_DISPATCH_MODULE(server.dll)
}





