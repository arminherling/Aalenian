# Aalenian

> [!NOTE]
> Everything from syntax to semantics is currently work-in-progress and might change at any point.

## Description
Aalenian is an imperative, compiled programming language designed with a focus on simple and enjoyable syntax with sensible defaults.
The goal is a statically typed language that feels like a dynamically typed language thanks to type inference.

## Features
- Static typing
- Type inference
- Modules
- No semicolons

## Roadmap
The current focus is on getting a minimal version up and running. For that, I'm targeting a bytecode VM, that is later going to be reused for compile time execution.

- Lexer: mostly done
- Parser: basic syntax can be parsed but is missing advanced features
- Typechecker: current focus of development
- Optimizer: none yet
- Codegen: none yet
- Bytecode VM: very early version
- Compile time execution: none yet

## Examples

### Constants

The global scope can't contain variables, any identifier defined here is a constant and can't be changed at runtime.

```rb
year = 2024
currentOS = OS::Windows
```

### Functions

The global scope can also contain functions, they can be used to initialize constants.

```rb
define square(x: i32) 
{ 
    return x * x 
}

y = square(10)
```

### Types

Types are the data objects of the language, they are similar to structs in other languages and can contain fields and methods. Members are accessed with a ``.`` , similar to ``this.`` in other languages.

```rb
type Two
{
    one = 1
    
    define one()
    {
        return .one
    }

    define value()
    {
        return .one() + .one()
    }
}
```

### Enums

Enums are a way to define constant values, they work similar to C/C++.
The first member has a value of 0, and each successive member has a value one greater than the previous one, unless the value is manually assigned.

```rb
enum Values
{
    First
    Second = 5
    Third
}

s = Values::Second
```

### Variants

Variants, also known as sum types or tagged unions, are Aalenian's way to do polymorphism, they allow you to put different types behind a unified interface. They can be extended from multiple files.

```rb
variant V : Vector1D | Vector2D | Vector3D
{
    define distance()
    {
        case Vector1D d
        {
            return 1
        }
        case Vector2D d
        {
            return 2
        }
        case Vector3D d
        {
            return 3
        }
    }
}

extend variant V : Vector4D
{
    define distance()
    {
        case Vector4d d
        {
            return 4
        }
    }
}
```
