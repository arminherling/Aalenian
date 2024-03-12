#include "TypeDatabase.h"

Type TypeDatabase::getNumberTypeByName(QStringView typeName)
{
    if (typeName == QStringView(u"i32"))
    {
        return Type::I32();
    }

    return Type::Invalid();
}
