#pragma once

#include "CompilerApi.h"

#include "DiagnosticsBag.h"
#include "TokenBuffer.h"
#include "SourceText.h"

COMPILER_API TokenBuffer Lex(const SourceTextSharedPtr& source, DiagnosticsBag& diagnostics) noexcept;
