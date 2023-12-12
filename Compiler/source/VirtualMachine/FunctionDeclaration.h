#pragma once

#include <VirtualMachine/Label.h>

#include <QString>

struct COMPILER_API FunctionDeclaration
{
    QString name;
    Label entryPoint;
    u8 returnValues;
    u8 parameterValues;
};
