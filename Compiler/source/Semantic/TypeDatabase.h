#pragma once

#include <Defines.h>
#include <Semantic/Type.h>
#include <QStringView>

class COMPILER_API TypeDatabase
{
public:
    Type getNumberTypeByName(QStringView typeName);
};
