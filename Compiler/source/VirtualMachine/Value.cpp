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
    : type(Type::Int32)
    , as{ .int32{value} }
{
}
