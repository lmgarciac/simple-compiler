# Albert Language Specification (`language.md`)

## 1. Overview

**Albert** is a minimal, educational programming language designed to learn how a compiler works end to end.

Goals:

- Simple, C-like syntax
- Easy to parse
- No complex types
- Enough features to demonstrate real compilation: variables, functions, control flow, expressions

Albert is intentionally small; it is **not** designed for performance or production use.

---

## 2. Source File Structure

An Albert program consists of:

- Function declarations
- Variable declarations
- Statements

The entry point is a function called **`main`**, which must return an integer.

Example:

```albert
fn main() {
    let x = 5;
    return x * 2;
}
```

---

## 3. Lexical Structure

### 3.1 Keywords

```
fn
let
return
if
else
while
```

### 3.2 Operators

```
+  -  *  /
=
== != < > <= >=
```

### 3.3 Punctuation

```
( ) { } , ;
```

### 3.4 Identifiers

Identifiers start with a letter or `_`, followed by letters, digits, or `_`.

### 3.5 Literals

Albert supports only **integer literals**.

Examples: `0`, `1`, `42`, `9999`

---

## 4. Types

Albert has exactly **one** built‑in type:

- `int`

All variables and function return values are integers.

Boolean logic uses integers (`0` = false, non-zero = true).

---

## 5. Variable Declarations

Variables must be declared with `let`.

Syntax:

```albert
let name = expression;
```

Examples:

```albert
let a = 10;
let b = a + 5;
```

Reassignment:

```albert
a = a + 1;
```

Scope is block-based.

---

## 6. Expressions

Albert supports:

### 6.1 Arithmetic

```
+  -  *  /
```

Precedence:

1. `*`, `/`
2. `+`, `-`

### 6.2 Comparison

```
== != < > <= >=
```

Results are integers (`0` or `1`).

### 6.3 Grouping

```
(expr)
```

### 6.4 Function Calls

```albert
foo(1, 2, x + 3)
```

Arguments evaluate left-to-right.

---

## 7. Statements

Statements end with semicolons, except for blocks.

### 7.1 Expression Statement

```albert
x = x + 1;
```

### 7.2 Variable Declaration

```albert
let x = 5;
```

### 7.3 Return

```albert
return expression;
```

### 7.4 Block Statement

```albert
{
    let x = 1;
    x = x + 1;
}
```

Blocks define new scopes.

---

## 8. Control Flow

### 8.1 If / Else

```albert
if (condition) {
    ...
} else {
    ...
}
```

### 8.2 While Loop

```albert
while (condition) {
    ...
}
```

---

## 9. Functions

Function declaration:

```albert
fn name(parameters) {
    body
}
```

Example:

```albert
fn sum(a, b) {
    return a + b;
}
```

Functions must return an integer.

Recursion is allowed.

---

## 10. Built-ins (Optional)

Albert defines no built-ins, but implementations may provide:

```
print(x)
```

---

## 11. Examples

### Basic Math

```albert
fn main() {
    let x = 10;
    let y = 20;
    return x + y * 3;
}
```

### Loop

```albert
fn main() {
    let x = 0;

    while (x < 5) {
        x = x + 1;
    }

    return x;
}
```

### Functions

```albert
fn mul(a, b) {
    return a * b;
}

fn main() {
    return mul(3, 4);
}
```

### Conditionals

```albert
fn main() {
    let x = 3;

    if (x == 3) {
        return 42;
    } else {
        return 0;
    }
}
```

---

## 12. Future Extensions (Not Part of v1)

Possible future additions:

- Boolean type
- Strings
- Arrays
- For-loop
- Structs / objects
- Modules / imports
- Heap allocation

---

## 13. Philosophy

Albert is designed to be:

- Small
- Clear
- Easy to compile
- Fully understandable end-to-end
