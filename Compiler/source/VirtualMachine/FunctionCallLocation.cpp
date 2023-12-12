#include "FunctionCallLocation.h"

FunctionCallLocation::FunctionCallLocation(
    const QString& name,
    JumpIndex target)
    : name{ name }
    , target{ target }
{
}
