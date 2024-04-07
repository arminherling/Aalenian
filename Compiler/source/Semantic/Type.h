#pragma once

#include <Defines.h>

class COMPILER_API Type
{
public:
    explicit Type(i32 id);

    [[nodiscard]] i32 id() const noexcept { return m_id; }

    [[nodiscard]] static Type Discard() noexcept { return Type(-2); }
    [[nodiscard]] static Type Undefined() noexcept { return Type(-1); }
    [[nodiscard]] static Type U8() noexcept { return Type(1); }
    [[nodiscard]] static Type I32() noexcept { return Type(2); }

private:
    i32 m_id;
};

COMPILER_API bool operator==(Type lhs, Type rhs) noexcept;
COMPILER_API bool operator!=(Type lhs, Type rhs) noexcept;
