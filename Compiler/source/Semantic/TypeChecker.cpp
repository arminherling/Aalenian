#include "TypeChecker.h"

TypeChecker::TypeChecker(const ParseTree& parseTree, DiagnosticsBag& diagnostics)
    : m_parseTree{ parseTree }
    , m_diagnostics{ diagnostics }
{
}

TypedTree TypeChecker::TypeCheck()
{
    return TypedTree();
}

TypedTree TypeCheck(const ParseTree& parseTree, DiagnosticsBag& diagnostics) noexcept
{
    TypeChecker typeChecker{ parseTree, diagnostics };
    return typeChecker.TypeCheck();
}
