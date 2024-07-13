#pragma once

#include <Compiler/API.h>
#include <Syntax/NameExpression.h>
#include <Syntax/Node.h>
#include <Syntax/TypeName.h>

class COMPILER_API ParameterNode : public Node
{
public:
    ParameterNode(
        NameExpression* name,
        const Token& colon, 
        const TypeName& type);

    [[nodiscard]] NameExpression* name() const noexcept { return m_name; }
    [[nodiscard]] const Token& colon() const noexcept { return m_colon; }
    [[nodiscard]] const TypeName& type() const noexcept { return m_type; }

private:
    NameExpression* m_name;
    Token m_colon;
    TypeName m_type;
};
