#pragma once

#include <Defines.h>
#include <QHash>
#include <QString>
#include <Semantic/Type.h>
#include <unordered_map>

class COMPILER_API Scope
{
public:
    Scope(Scope* parent);
    //~Scope() = default;
    //Scope(Scope&&) = default;

    void addTypeBinding(QStringView identifier, Type node);
    void addVariableBinding(QStringView identifier, Type node);
    void addFunctionBinding(QStringView identifier, Type node);
    [[nodiscard]] Type tryGetTypeBinding(QStringView identifier) const noexcept;
    [[nodiscard]] Type tryGetVariableBinding(QStringView identifier) const noexcept;
    [[nodiscard]] Type tryGetFunctionBinding(QStringView identifier) const noexcept;

private:
    Scope* m_parent;
    std::unordered_map<QString, Type> m_typeBindings;
    std::unordered_map<QString, Type> m_variableBindings;
    std::unordered_map<QString, Type> m_functionBindings;
};
