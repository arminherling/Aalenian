#include "FunctionCallLocation.h"

FunctionCallLocation::FunctionCallLocation(
    const QString& name,
    u16 targetIndex)
    : name{ name }
    , targetIndex{ targetIndex }
{
}
