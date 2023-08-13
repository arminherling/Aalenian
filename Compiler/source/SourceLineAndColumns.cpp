#include "SourceLineAndColumns.h"

SourceLineAndColumns StartAndEndPositions(
    const QStringView& sourceText,
    int firstIndex,
    int lastIndex)
{
    SourceLineAndColumns positions{};

    int currentLine = 1;
    int currentColumn = 0;
    auto size = sourceText.size();

    for (auto i = 0; i <= size; i++)
    {
        QChar currentChar = ' ';
        if (i < size)
        {
            currentChar = sourceText.at(i);
        }

        if (currentChar == '\r')
        {
            currentLine++;
            currentColumn = 0;
            if (auto nextIndex = i + 1; nextIndex < size && sourceText.at(nextIndex) == '\n')
            {
                i++;
            }
        }
        else if (currentChar == '\n')
        {
            currentLine++;
            currentColumn = 0;
        }
        else
        {
            currentColumn++;
        }

        if (i == firstIndex)
        {
            positions.startLine = currentLine;
            positions.startColumn = currentColumn;
        }
        if (i == lastIndex)
        {
            positions.endLine = currentLine;
            positions.endColumn = currentColumn;
            break;
        }
    }
    return positions;
}
