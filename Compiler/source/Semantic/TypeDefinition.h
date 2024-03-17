#pragma once

#include <Defines.h>
#include <QString>

class TypeDefinition
{
public:
    TypeDefinition(i32 id, const QString& name);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] const QString& name() const noexcept { return m_name; }

private:
    i32 m_id;
    QString m_name;
};

