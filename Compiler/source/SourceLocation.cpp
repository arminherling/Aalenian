#include "SourceLocation.h"
#include "SourceLineAndColumns.h"

SourceLocation::SourceLocation(
    const QStringView& sourcetext,
    int firstIndex,
    int lastIndex)
    : sourceText(sourcetext)
    , firstIndex(firstIndex)
    , lastIndex(lastIndex)
{
}

QString SourceLocation::Stringify() const
{
    auto positions = StartAndEndPositions(sourceText, firstIndex, lastIndex);

    return QString("Line %1, Column %2 - Line %3, Column %4 (Index %5 - %6)")
        .arg(
            QString::number(positions.startLine),
            QString::number(positions.startColumn),
            QString::number(positions.endLine),
            QString::number(positions.endColumn),
            QString::number(firstIndex),
            QString::number(lastIndex));
}
