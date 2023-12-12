#pragma once

#include <Defines.h>
#include <VirtualMachine/JumpIndex.h>

#include <QString>

struct COMPILER_API FunctionCallLocation
{
    FunctionCallLocation(const QString& name, JumpIndex target);

    QString name;
    JumpIndex target;
};
