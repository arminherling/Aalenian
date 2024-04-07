#pragma once

#include <Defines.h>
#include <QHash>
#include <QString>
#include <Semantic/Type.h>
#include <unordered_map>

class COMPILER_API Environment
{
public:
    void addBinding(QStringView identifier, Type type);
    [[nodiscard]] Type tryGetBinding(QStringView identifier) const noexcept;

private:
    std::unordered_map<QString, Type> m_bindings;
};
