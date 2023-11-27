#include "Value.h"

Value::Value()
    : type(Type::Invalid)
    , as{}
{
}

Value::Value(bool value)
    : type(Type::Bool)
    , as{ .boolean{value} }
{
}

Value::Value(i32 value)
    : type(Type::I32)
    , as{ .numI32{value} }
{
}
