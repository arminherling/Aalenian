#pragma once

#include <Defines.h>

enum class TypeKind
{
    Invalid,
    Builtin,
    Enum,
    Type,
    Function
};

class COMPILER_API Type
{
public:
    Type(i32 id, TypeKind kind);

    [[nodiscard]] i32 id() const noexcept { return m_id; }
    [[nodiscard]] TypeKind kind() const noexcept { return m_kind; }

    [[nodiscard]] static Type Discard() noexcept { return Type(-2, TypeKind::Builtin); }
    [[nodiscard]] static Type Undefined() noexcept { return Type(-1, TypeKind::Builtin); }
    [[nodiscard]] static Type Void() noexcept { return Type(1, TypeKind::Builtin); }
    [[nodiscard]] static Type Bool() noexcept { return Type(2, TypeKind::Builtin); }
    [[nodiscard]] static Type U8() noexcept { return Type(3, TypeKind::Builtin); }
    [[nodiscard]] static Type I32() noexcept { return Type(4, TypeKind::Builtin); }

private:
    i32 m_id;
    TypeKind m_kind;
};

COMPILER_API bool operator==(Type lhs, Type rhs) noexcept;
COMPILER_API bool operator!=(Type lhs, Type rhs) noexcept;
