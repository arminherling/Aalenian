#include "SourceLocation.h"

SourceLocation::SourceLocation(
    const QStringView& sourcetext,
    int firstIndex,
    int lastIndex)
    : sourceText(sourcetext)
    , firstIndex(firstIndex)
    , lastIndex(lastIndex)
{
}
