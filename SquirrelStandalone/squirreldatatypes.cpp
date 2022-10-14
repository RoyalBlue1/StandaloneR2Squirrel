

#include "squirreldatatypes.h"
#include <cstdio>

SQObject& SQObject::operator=(SQTable* other)
{
    if (this->_Type & SQOBJECT_REF_COUNTED)
    {
        if (this->_VAL.asRefCounted->uiRef-- == 1)
            // if (this->_VAL.asRefCounted->vtable && this->_VAL.asRefCounted->vtable->destructor)
            this->_VAL.asRefCounted->vtable->destructor(this->_VAL.asRefCounted);
    }

    other->uiRef++;
    this->_Type = OT_TABLE;
    this->_structOffset = 0;
    this->_VAL.asTable = other;
    return *this;
}

SQObject& SQObject::operator=(SQArray* other)
{
    if (this->_Type & SQOBJECT_REF_COUNTED)
    {
        if (this->_VAL.asRefCounted->uiRef-- == 1)
            // if (this->_VAL.asRefCounted->vtable && this->_VAL.asRefCounted->vtable->destructor)
            this->_VAL.asRefCounted->vtable->destructor(this->_VAL.asRefCounted);
    }

    other->uiRef++;
    this->_Type = OT_ARRAY;
    this->_structOffset = 0;
    this->_VAL.asArray = other;
    return *this;
}

SQObject& SQObject::operator=(SQStructInstance* other)
{
    if (this->_Type & SQOBJECT_REF_COUNTED)
    {
        if (this->_VAL.asRefCounted->uiRef-- == 1)
            // if (this->_VAL.asRefCounted->vtable && this->_VAL.asRefCounted->vtable->destructor)
            this->_VAL.asRefCounted->vtable->destructor(this->_VAL.asRefCounted);
    }

    other->uiRef++;
    this->_Type = OT_STRUCT_INSTANCE;
    this->_structOffset = 0;
    this->_VAL.asStructInstance = other;
    return *this;
}

SQObject& SQObject::operator=(SQString* other)
{
    if (this->_Type & SQOBJECT_REF_COUNTED)
    {
        if (this->_VAL.asRefCounted->uiRef-- == 1)
            // if (this->_VAL.asRefCounted->vtable && this->_VAL.asRefCounted->vtable->destructor)
            this->_VAL.asRefCounted->vtable->destructor(this->_VAL.asRefCounted);
    }

    other->uiRef++;
    this->_Type = OT_STRING;
    this->_structOffset = 0;
    this->_VAL.asString = other;
    return *this;
}


const char* sq_getTypeName(int type)
{
    switch (type)
    {
    case OT_ASSET:
        return "asset";
    case OT_INTEGER:
        return "int";
    case OT_BOOL:
        return "bool";
    case SQOBJECT_NUMERIC:
        return "float or int";
    case OT_NULL:
        return "null";
    case OT_VECTOR:
        return "vector";
    case 0:
        return "var";
    case OT_USERDATA:
        return "userdata";
    case OT_FLOAT:
        return "float";
    case OT_STRING:
        return "string";
    case OT_ARRAY:
        return "array";
    case OT_NATIVECLOSURE:
        return "native function";
    case OT_STRUCT_DEF:
        return "structdef";
    case OT_THREAD:
        return "thread";
    case OT_FUNCPROTO:
        return "function";
    case OT_CLAAS:
        return "class";
    case OT_WEAKREF:
        return "weakref";
    case OT_UNIMPLEMENTED_FUNCTION:
        return "unimplemented function";
    case OT_STRUCT_INSTANCE:
        return "struct instance";
    case OT_TABLE:
        return "table";
    case OT_INSTANCE:
        return "instance";
    case OT_ENTITY:
        return "entity";
    case OT_CLOSURE:
        return "closure";
    }
    return "";
}
const char* sq_OpToString(int op)
{
    switch (op)
    {
    case _OP_LINE:
        return "_OP_LINE";
    case _OP_LOAD:
        return "_OP_LOAD";
    case _OP_LOADCOPY:
        return "_OP_LOADCOPY";
    case _OP_LOADINT:
        return "_OP_LOADINT";
    case _OP_LOADFLOAT:
        return "_OP_LOADFLOAT";
    case _OP_DLOAD:
        return "_OP_DLOAD";
    case _OP_TAILCALL:
        return "_OP_TAILCALL";
    case _OP_CALL:
        return "_OP_CALL";
    case _OP_PREPCALL:
        return "_OP_PREPCALL";
    case _OP_PREPCALLK:
        return "_OP_PREPCALLK";
    case _OP_GETK:
        return "_OP_GETK";
    case _OP_MOVE:
        return "_OP_MOVE";
    case _OP_NEWSLOT:
        return "_OP_NEWSLOT";
    case _OP_DELETE:
        return "_OP_DELETE";
    case _OP_SET:
        return "_OP_SET";
    case _OP_GET:
        return "_OP_GET";
    case _OP_EQ:
        return "_OP_EQ";
    case _OP_NE:
        return "_OP_NE";
    case _OP_ARITH:
        return "_OP_ARITH";
    case _OP_BITW:
        return "_OP_BITW";
    case _OP_RETURN:
        return "_OP_RETURN";
    case _OP_LOADNULLS:
        return "_OP_LOADNULLS";
    case _OP_LOADROOTTABLE:
        return "_OP_LOADROOTTABLE";
    case _OP_LOADBOOL:
        return "_OP_LOADBOOL";
    case _OP_DMOVE:
        return "_OP_DMOVE";
    case _OP_JMP:
        return "_OP_JMP";
    case _OP_JNZ:
        return "_OP_JNZ";
    case _OP_JZ:
        return "_OP_JZ";
    case _OP_LOADFREEVAR:
        return "_OP_LOADFREEVAR";
    case _OP_VARGC:
        return "_OP_VARGC";
    case _OP_GETVARGV:
        return "_OP_GETVARGV";
    case _OP_NEWTABLE:
        return "_OP_NEWTABLE";
    case _OP_NEWARRAY:
        return "_OP_NEWARRAY";
    case _OP_APPENDARRAY:
        return "_OP_APPENDARRAY";
    case _OP_GETPARENT:
        return "_OP_GETPARENT";
    case _OP_COMPOUND_ARITH:
        return "_OP_COMPOUND_ARITH";
    case _OP_COMPOUND_ARITH_LOCAL:
        return "_OP_COMPOUND_ARITH_LOCAL";
    case _OP_INCREMENT_PREFIX:
        return "_OP_INCREMENT_PREFIX";
    case _OP_INCREMENT_PREFIX_LOCAL:
        return "_OP_INCREMENT_PREFIX_LOCAL";
    case _OP_INCREMENT_PREFIX_STRUCTFIELD:
        return "_OP_INCREMENT_PREFIX_STRUCTFIELD";
    case _OP_INCREMENT_POSTFIX:
        return "_OP_INCREMENT_POSTFIX";
    case _OP_INCREMENT_POSTFIX_LOCAL:
        return "_OP_INCREMENT_POSTFIX_LOCAL";
    case _OP_INCREMENT_POSTFIX_STRUCTFIELD:
        return "_OP_INCREMENT_POSTFIX_STRUCTFIELD";
    case _OP_CMP:
        return "_OP_CMP";
    case _OP_EXISTS:
        return "_OP_EXISTS";
    case _OP_INSTANCEOF:
        return "_OP_INSTANCEOF";
    case _OP_NEG:
        return "_OP_NEG";
    case _OP_NOT:
        return "_OP_NOT";
    case _OP_BWNOT:
        return "_OP_BWNOT";
    case _OP_CLOSURE:
        return "_OP_CLOSURE";
    case _OP_FOREACH:
        return "_OP_FOREACH";
    case _OP_FOREACH_STATICARRAY_START:
        return "_OP_FOREACH_STATICARRAY_START";
    case _OP_FOREACH_STATICARRAY_NEXT:
        return "_OP_FOREACH_STATICARRAY_NEXT";
    case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_START:
        return "_OP_FOREACH_STATICARRAY_NESTEDSTRUCT_START";
    case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_NEXT:
        return "_OP_FOREACH_STATICARRAY_NESTEDSTRUCT_NEXT";
    case _OP_DELEGATE:
        return "_OP_DELEGATE";
    case _OP_CLONE:
        return "_OP_CLONE";
    case _OP_TYPEOF:
        return "_OP_TYPEOF";
    case _OP_PUSHTRAP:
        return "_OP_PUSHTRAP";
    case _OP_POPTRAP:
        return "_OP_POPTRAP";
    case _OP_THROW:
        return "_OP_THROW";
    case _OP_CLASS:
        return "_OP_CLASS";
    case _OP_NEWSLOTA:
        return "_OP_NEWSLOTA";
    case _OP_EQ_LITERAL:
        return "_OP_EQ_LITERAL";
    case _OP_NE_LITERAL:
        return "_OP_NE_LITERAL";
    case _OP_FOREACH_SETUP:
        return "_OP_FOREACH_SETUP";
    case _OP_ASSERT_FAILED:
        return "_OP_ASSERT_FAILED";
    case _OP_ADD:
        return "_OP_ADD";
    case _OP_SUB:
        return "_OP_SUB";
    case _OP_MUL:
        return "_OP_MUL";
    case _OP_DIV:
        return "_OP_DIV";
    case _OP_MOD:
        return "_OP_MOD";
    case _OP_PREPCALLK_CALL:
        return "_OP_PREPCALLK_CALL";
    case _OP_PREPCALLK_MOVE_CALL:
        return "_OP_PREPCALLK_MOVE_CALL";
    case _OP_PREPCALLK_LOADINT_CALL:
        return "_OP_PREPCALLK_LOADINT_CALL";
    case _OP_CMP_JZ:
        return "_OP_CMP_JZ";
    case _OP_INCREMENT_LOCAL_DISCARD_JMP:
        return "_OP_INCREMENT_LOCAL_DISCARD_JMP";
    case _OP_JZ_RETURN:
        return "_OP_JZ_RETURN";
    case _OP_JZ_LOADBOOL_RETURN:
        return "_OP_JZ_LOADBOOL_RETURN";
    case _OP_NEWVECTOR:
        return "_OP_NEWVECTOR";
    case _OP_ZEROVECTOR:
        return "_OP_ZEROVECTOR";
    case _OP_GET_VECTOR_COMPONENT:
        return "_OP_GET_VECTOR_COMPONENT";
    case _OP_SET_VECTOR_COMPONENT:
        return "_OP_SET_VECTOR_COMPONENT";
    case _OP_VECTOR_COMPONENT_MINUSEQ:
        return "_OP_VECTOR_COMPONENT_MINUSEQ";
    case _OP_VECTOR_COMPONENT_PLUSEQ:
        return "_OP_VECTOR_COMPONENT_PLUSEQ";
    case _OP_VECTOR_COMPONENT_MULEQ:
        return "_OP_VECTOR_COMPONENT_MULEQ";
    case _OP_VECTOR_COMPONENT_DIVEQ:
        return "_OP_VECTOR_COMPONENT_DIVEQ";
    case _OP_VECTOR_NORMALIZE:
        return "_OP_VECTOR_NORMALIZE";
    case _OP_VECTOR_NORMALIZE_IN_PLACE:
        return "_OP_VECTOR_NORMALIZE_IN_PLACE";
    case _OP_VECTOR_DOT_PRODUCT:
        return "_OP_VECTOR_DOT_PRODUCT";
    case _OP_VECTOR_DOT_PRODUCT2D:
        return "_OP_VECTOR_DOT_PRODUCT2D";
    case _OP_VECTOR_CROSS_PRODUCT:
        return "_OP_VECTOR_CROSS_PRODUCT";
    case _OP_VECTOR_CROSS_PRODUCT2D:
        return "_OP_VECTOR_CROSS_PRODUCT2D";
    case _OP_VECTOR_LENGTH:
        return "_OP_VECTOR_LENGTH";
    case _OP_VECTOR_LENGTHSQR:
        return "_OP_VECTOR_LENGTHSQR";
    case _OP_VECTOR_LENGTH2D:
        return "_OP_VECTOR_LENGTH2D";
    case _OP_VECTOR_LENGTH2DSQR:
        return "_OP_VECTOR_LENGTH2DSQR";
    case _OP_VECTOR_DISTANCE:
        return "_OP_VECTOR_DISTANCE";
    case _OP_VECTOR_DISTANCESQR:
        return "_OP_VECTOR_DISTANCESQR";
    case _OP_VECTOR_DISTANCE2D:
        return "_OP_VECTOR_DISTANCE2D";
    case _OP_VECTOR_DISTANCE2DSQR:
        return "_OP_VECTOR_DISTANCE2DSQR";
    case _OP_INCREMENT_LOCAL_DISCARD:
        return "_OP_INCREMENT_LOCAL_DISCARD";
    case _OP_FASTCALL:
        return "_OP_FASTCALL";
    case _OP_FASTCALL_NATIVE:
        return "_OP_FASTCALL_NATIVE";
    case _OP_FASTCALL_NATIVE_ARGTYPECHECK:
        return "_OP_FASTCALL_NATIVE_ARGTYPECHECK";
    case _OP_FASTCALL_ENV:
        return "_OP_FASTCALL_ENV";
    case _OP_FASTCALL_NATIVE_ENV:
        return "_OP_FASTCALL_NATIVE_ENV";
    case _OP_FASTCALL_NATIVE_ENV_ARGTYPECHECK:
        return "_OP_FASTCALL_NATIVE_ENV_ARGTYPECHECK";
    case _OP_LOADGLOBALARRAY:
        return "_OP_LOADGLOBALARRAY";
    case _OP_GETGLOBAL:
        return "_OP_GETGLOBAL";
    case _OP_SETGLOBAL:
        return "_OP_SETGLOBAL";
    case _OP_COMPOUND_ARITH_GLOBAL:
        return "_OP_COMPOUND_ARITH_GLOBAL";
    case _OP_GETSTRUCTFIELD:
        return "_OP_GETSTRUCTFIELD";
    case _OP_SETSTRUCTFIELD:
        return "_OP_SETSTRUCTFIELD";
    case _OP_COMPOUND_ARITH_STRUCTFIELD:
        return "_OP_COMPOUND_ARITH_STRUCTFIELD";
    case _OP_NEWSTRUCT:
        return "_OP_NEWSTRUCT";
    case _OP_GETSUBSTRUCT:
        return "_OP_GETSUBSTRUCT";
    case _OP_GETSUBSTRUCT_DYNAMIC:
        return "_OP_GETSUBSTRUCT_DYNAMIC";
    case _OP_TYPECAST:
        return "_OP_TYPECAST";
    case _OP_TYPECHECK:
        return "_OP_TYPECHECK";
    case _OP_TYPECHECK_ORNULL:
        return "_OP_TYPECHECK_ORNULL";
    case _OP_TYPECHECK_NOTNULL:
        return "_OP_TYPECHECK_NOTNULL";
    case _OP_CHECK_ENTITY_CLASS:
        return "_OP_CHECK_ENTITY_CLASS";
    case _OP_UNREACHABLE:
        return "_OP_UNREACHABLE";
    case _OP_ARRAY_RESIZE:
        return "_OP_ARRAY_RESIZE";
    default:
        return "UNKNOWN";
    }
}
int sqInstructionToString(char* outBuffer, int outBufferLength, SQInstruction* instruction, int index, int stackbase)
{

    switch (instruction->op)
    {
    case _OP_MOVE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, src: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase);
    case _OP_LOAD:
    case _OP_LOADCOPY:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, literal: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_LOADINT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, setTo: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_LOADFLOAT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, setTo: %f",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            (float)instruction->arg1);
    case _OP_DLOAD:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest1: %d, literalsIndex1: %d, dest2: %d, literalsIndex2: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_GETK:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase);
    case _OP_NEWSLOT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, table: %d, key: %d, val: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3 + stackbase);
    case _OP_DELETE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, table: %d, key: %d, valOutput: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->output + stackbase);
    case _OP_SET:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, storageObject: %d, key: %d, val: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3 + stackbase);
    case _OP_GET:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, storageObject: %d, key: %d, valOutput: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->output + stackbase);
    case _OP_EQ:
    case _OP_NE:
    case _OP_ADD:
    case _OP_SUB:
    case _OP_MUL:
    case _OP_DIV:
    case _OP_MOD:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase);
    case _OP_BITW:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d, operation: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_RETURN:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, output: %d, arg1: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output,
            instruction->arg1);
    case _OP_LOADROOTTABLE:
    case _OP_VARGC:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase);
    case _OP_LOADBOOL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, setTo: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_DMOVE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest1: %d, src1: %d, dest2: %d, src2: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3 + stackbase);
    case _OP_JMP:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, offset: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg1);
    case _OP_JZ:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, offset: %d, check %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg1,
            instruction->output + stackbase);
    case _OP_LOADFREEVAR:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, outervalIndex: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_GETVARGV:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, vargIndex: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_NEWTABLE:
    case _OP_NEWARRAY:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, size: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_APPENDARRAY:
        if (instruction->arg3)
            return snprintf(
                outBuffer,
                outBufferLength,
                "Index %d OpCode: %s, array: %d, literal: %d",
                index,
                sq_OpToString(instruction->op),
                instruction->output + stackbase,
                instruction->arg1);
        else
            return snprintf(
                outBuffer,
                outBufferLength,
                "Index %d OpCode: %s, array: %d, stack: %d",
                index,
                sq_OpToString(instruction->op),
                instruction->output + stackbase,
                instruction->arg1 + stackbase);
    case _OP_GETPARENT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, child: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase);
    case _OP_GETSTRUCTFIELD:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, struct: %d, offset: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2);
    case _OP_EQ_LITERAL:
    case _OP_NE_LITERAL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, literal: %d, arg2: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1,
            instruction->arg2 + stackbase);
    case _OP_GETGLOBAL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, globalIndex: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_SETGLOBAL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, src: %d, globalIndex: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->arg2 + stackbase,
            instruction->arg1);
    case _OP_FASTCALL:
    case _OP_FASTCALL_NATIVE:
    case _OP_FASTCALL_NATIVE_ARGTYPECHECK:
    case _OP_FASTCALL_ENV:
    case _OP_FASTCALL_NATIVE_ENV:
    case _OP_FASTCALL_NATIVE_ENV_ARGTYPECHECK:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, fastcallClosure: %d, newStackBase: %d, arg3: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_CMP_JZ:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d, arg3: %d jumpOffset: %d",
            index,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3, instruction[1].arg1);
    default:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, output: %d, arg1: %d, arg2: %d, arg3: %d DEFAULT",
            index,
            sq_OpToString(instruction->op),
            instruction->output,
            instruction->arg1,
            instruction->arg2,
            instruction->arg3);
    }
}

int sqInstructionToString(char* outBuffer, int outBufferLength, SQInstruction* instruction, HSquirrelVM* sqvm)
{
    int stackbase = sqvm->_stackOfCurrentFunction - sqvm->_stack;
    switch (instruction->op)
    {
    case _OP_MOVE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, src: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase);
    case _OP_LOAD:
    case _OP_LOADCOPY:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, literal: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_LOADINT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, setTo: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_LOADFLOAT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, setTo: %f",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            (float)instruction->arg1);
    case _OP_DLOAD:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest1: %d, literalsIndex1: %d, dest2: %d, literalsIndex2: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_GETK:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase);
    case _OP_NEWSLOT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, table: %d, key: %d, val: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3 + stackbase);
    case _OP_DELETE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, table: %d, key: %d, valOutput: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->output + stackbase);
    case _OP_SET:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, storageObject: %d, key: %d, val: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3 + stackbase);
    case _OP_GET:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, storageObject: %d, key: %d, valOutput: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->output + stackbase);
    case _OP_EQ:
    case _OP_NE:
    case _OP_ADD:
    case _OP_SUB:
    case _OP_MUL:
    case _OP_DIV:
    case _OP_MOD:
    case _OP_EXISTS:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase);
    case _OP_BITW:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d, operation: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_RETURN:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, output: %d, arg1: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output,
            instruction->arg1);
    case _OP_LOADROOTTABLE:
    case _OP_VARGC:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase);
    case _OP_LOADBOOL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, setTo: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_DMOVE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest1: %d, src1: %d, dest2: %d, src2: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3 + stackbase);
    case _OP_JMP:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, offset: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1);
    case _OP_JZ:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, offset: %d, check %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1,
            instruction->output + stackbase);
    case _OP_LOADFREEVAR:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, outervalIndex: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_GETVARGV:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, vargIndex: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_NEWTABLE:
    case _OP_NEWARRAY:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, size: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_APPENDARRAY:
        if (instruction->arg3)
            return snprintf(
                outBuffer,
                outBufferLength,
                "Index %d OpCode: %s, array: %d, literal: %d",
                instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
                sq_OpToString(instruction->op),
                instruction->output + stackbase,
                instruction->arg1);
        else
            return snprintf(
                outBuffer,
                outBufferLength,
                "Index %d OpCode: %s, array: %d, stack: %d",
                instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
                sq_OpToString(instruction->op),
                instruction->output + stackbase,
                instruction->arg1 + stackbase);
    case _OP_GETPARENT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, child: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase);
    case _OP_GETSTRUCTFIELD:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, struct: %d, offset: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2);
    case _OP_EQ_LITERAL:
    case _OP_NE_LITERAL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, literal: %d, arg2: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1,
            instruction->arg2 + stackbase);
    case _OP_GETGLOBAL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, globalIndex: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    case _OP_SETGLOBAL:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, src: %d, globalIndex: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg2 + stackbase,
            instruction->arg1);
    case _OP_FASTCALL:
    case _OP_FASTCALL_ENV:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, fastcallClosureName: %s, newStackBase: %d, arg3: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[instruction->arg1]._VAL.asFuncProto->funcName._VAL.asString->_val,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_FASTCALL_NATIVE:
    case _OP_FASTCALL_NATIVE_ARGTYPECHECK:
    case _OP_FASTCALL_NATIVE_ENV:
    case _OP_FASTCALL_NATIVE_ENV_ARGTYPECHECK:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, fastcallClosureName: %s, newStackBase: %d, arg3: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            sqvm->ci->closure._VAL.asClosure->fastcallClosureArray[instruction->arg1]._VAL.asNativeClosure->_name->_val,
            instruction->arg2 + stackbase,
            instruction->arg3);
    case _OP_CMP_JZ:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, arg1: %d, arg2: %d, arg3: %d jumpOffset: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2 + stackbase,
            instruction->arg3,
            instruction[1].arg1);
    case _OP_SETSTRUCTFIELD:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, struct: %d, offset: %d, src: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1,
            instruction->arg2 + stackbase);
    case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_START:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, arg1: %d, structDest: %d, counter: %d, structSrc: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1 + stackbase,
            instruction->arg1 + stackbase + 1,
            instruction->arg1 + stackbase + 2,
            instruction->arg2 + stackbase);
    case _OP_FOREACH_STATICARRAY_NESTEDSTRUCT_NEXT:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, nextStructOffset: %d, structDest: %d, counter: %d, structSrc: %d, maxIterations: %d, jumpOffset: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1 >> 8,
            instruction->arg2 + stackbase + 1,
            instruction->arg2 + stackbase + 2,
            (__int8)instruction->arg1 + stackbase,
            instruction->arg3,
            instruction->output);
    case _OP_ARRAY_RESIZE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, targetArray: %d, newSizeLocation: %d, newValueIndex %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1 + stackbase,
            instruction->arg2);
    case _OP_LINE:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, line: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->arg1);
    case _OP_LOADNULLS:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, dest: %d, amount: %d",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output + stackbase,
            instruction->arg1);
    default:
        return snprintf(
            outBuffer,
            outBufferLength,
            "Index %d OpCode: %s, output: %d, arg1: %d, arg2: %d, arg3: %d DEFAULT",
            instruction - sqvm->ci->closure._VAL.asFuncProto->instruction,
            sq_OpToString(instruction->op),
            instruction->output,
            instruction->arg1,
            instruction->arg2,
            instruction->arg3);
    }
}
