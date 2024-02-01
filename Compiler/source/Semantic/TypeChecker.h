#pragma once

#include <Defines.h>
#include <Compiler/DiagnosticsBag.h>
#include <Semantic/TypedTree.h>
#include <Syntax/ParseTree.h>

class COMPILER_API TypeChecker
{
public:
    TypeChecker(const ParseTree& parseTree, DiagnosticsBag& diagnostics);

    TypedTree TypeCheck();

private:
    ParseTree m_parseTree;
    DiagnosticsBag& m_diagnostics;
};

COMPILER_API TypedTree TypeCheck(const ParseTree& parseTree, DiagnosticsBag& diagnostics) noexcept;
