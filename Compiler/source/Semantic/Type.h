#pragma once

#include <Defines.h>

class COMPILER_API Type
{
public:
    explicit Type(i32 id);

    [[nodiscard]] i32 id() const noexcept { return m_id; }

    static Type Discard() { return Type(-2); }
    static Type Undefined() { return Type(-1); }
    static Type U8() { return Type(1); }
    static Type I32() { return Type(2); }

private:
    i32 m_id;
};

COMPILER_API bool operator==(Type lhs, Type rhs) noexcept;
COMPILER_API bool operator!=(Type lhs, Type rhs) noexcept;
