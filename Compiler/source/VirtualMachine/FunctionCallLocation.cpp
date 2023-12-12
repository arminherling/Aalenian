#include "FunctionCallLocation.h"

FunctionCallLocation::FunctionCallLocation(
    const QString& name,
    JumpTarget target)
    : name{ name }
    , target{ target }
{
}
