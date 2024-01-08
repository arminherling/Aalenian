#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(AALTEST_LIB)
#  define AALTEST_API Q_DECL_EXPORT
# else
#  define AALTEST_API Q_DECL_IMPORT
# endif
#else
# define AALTEST_API
#endif
