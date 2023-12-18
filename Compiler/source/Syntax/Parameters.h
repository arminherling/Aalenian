#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Syntax/Parameter.h>
#include <Syntax/Token.h>
#include <QList>

class COMPILER_API Parameters : public Node
{
public:
    Parameters(
        const Token& openParenthesis,
        const QList<Parameter*>& parameters,
        const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const QList<Parameter*>& parameters() noexcept { return m_parameters; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    const QList<Parameter*> m_parameters;
    Token m_closeParenthesis;
};
