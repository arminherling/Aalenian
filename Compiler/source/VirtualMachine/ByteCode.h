#pragma once

#include <Defines.h>

#include <QString>

#include <vector>
#include <unordered_map>

enum Op : u8
{
    LoadBool,
    NotBool,
    EqualBool,
    NotEqualBool,
    LoadInt32,
    AddInt32,
    SubtractInt32,
    MultiplyInt32,
    DivideInt32,
    NegateInt32,
    EqualInt32,
    NotEqualInt32,
    GreaterInt32,
    GreaterOrEqualInt32,
    LessInt32,
    LessOrEqualInt32,
    FunctionCall,
    Jump,
    JumpIfFalse,
    Move,
    PrintBool,
    PrintInt32,
    PrintNewLine,
    Halt
};

COMPILER_API QString StringifyOp(Op op);

#include <VirtualMachine/Label.h>
struct COMPILER_API FunctionDeclaration
{
    QString name;
    Label entryPoint;
    u8 returnValues;
    u8 parameterValues;
};

struct COMPILER_API FunctionCallLocation
{
    FunctionCallLocation(const QString& name, u16 targetIndex)
        : name{ name }
        , targetIndex{ targetIndex }
    {
    }

    QString name;
    u16 targetIndex;
};

#include <QHash>

struct COMPILER_API ByteCode
{
    std::vector<u8> data;
    std::unordered_map<QString, FunctionDeclaration> functions;

    inline u8 readUInt8(u16& ip) const;
    inline u16 readUInt16(u16& ip) const;
    inline i32 readInt32(u16& ip) const;

    inline void writeUInt8(u8 value);
    inline void writeUInt16(u16 value);
    inline void writeUInt16(u16 value, u16 address);
    inline void writeInt32(i32 value);

    void setFunctionDeclaration(const FunctionDeclaration& declaration);
    std::optional<FunctionDeclaration> getFunctionDeclaration(const QString& name);
};
