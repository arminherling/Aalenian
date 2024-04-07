#pragma once

#include <Defines.h>
#include <Syntax/Node.h>
#include <Syntax/Token.h>
#include <Syntax/ArgumentNode.h>
#include <QList>

class COMPILER_API ArgumentsNode : public Node
{
public:
    ArgumentsNode(
        const Token& openParenthesis,
        const QList<ArgumentNode*>& arguments,
        const Token& closeParenthesis);

    [[nodiscard]] const Token& openParenthesis() const noexcept { return m_openParenthesis; }
    [[nodiscard]] const QList<ArgumentNode*>& arguments() const noexcept { return m_arguments; }
    [[nodiscard]] const Token& closeParenthesis() const noexcept { return m_closeParenthesis; }

private:
    Token m_openParenthesis;
    QList<ArgumentNode*> m_arguments;
    Token m_closeParenthesis;
};
