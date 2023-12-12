#pragma once

#include <Defines.h>

#include <QString>

struct COMPILER_API FunctionCallLocation
{
    FunctionCallLocation(const QString& name, u16 targetIndex);

    QString name;
    u16 targetIndex;
};
