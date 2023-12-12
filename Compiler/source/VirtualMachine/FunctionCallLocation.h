#pragma once

#include <Defines.h>
#include <VirtualMachine/JumpTarget.h>

#include <QString>

struct COMPILER_API FunctionCallLocation
{
    FunctionCallLocation(const QString& name, JumpTarget target);

    QString name;
    JumpTarget target;
};
