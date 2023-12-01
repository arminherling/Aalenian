#pragma once

#include <QtCore/qglobal.h>
#include <cstdint>

#ifndef BUILD_STATIC
# if defined(COMPILER_LIB)
#  define COMPILER_API Q_DECL_EXPORT
# else
#  define COMPILER_API Q_DECL_IMPORT
# endif
#else
# define COMPILER_API
#endif

#define TODO(X) __debugbreak();

using i8 = int8_t;
using i32 = int32_t;

using u8 = uint8_t;
using u16 = uint16_t;
