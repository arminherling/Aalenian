#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COMPILER_LIB)
#  define COMPILER_EXPORT Q_DECL_EXPORT
# else
#  define COMPILER_EXPORT Q_DECL_IMPORT
# endif
#else
# define COMPILER_EXPORT
#endif
