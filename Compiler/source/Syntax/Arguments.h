#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Syntax/Token.h>
#include <Syntax/Argument.h>
#include <QList>

class COMPILER_API Arguments : public Node
{
public:
    Arguments(
        const Token& openParenthesis,
        const QList<Argument*>& arguments,
        const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() noexcept { return m_openParenthesis; }
    [[nodiscard]] const QList<Argument*>& arguments() noexcept { return m_arguments; }
    [[nodiscard]] const Token& closeParenthesis() noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    QList<Argument*> m_arguments;
    Token m_closeParenthesis;
};
