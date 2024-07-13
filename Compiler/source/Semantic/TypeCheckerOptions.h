#pragma once

#include <Compiler/API.h>
#include <Semantic/Type.h>

struct COMPILER_API TypeCheckerOptions
{
    Type defaultIntegerType;
    Type defaultEnumBaseType;
};
