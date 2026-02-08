# Compy Syntax Reference

This document describes the syntax rules and structure for writing Compy programs.

---

## 1. Comments

- Hash-style comments:

```py
# This is a comment
````

* C++-style comments:

```c
// This is also a comment
```

---

## 2. Variable Declaration

```c
int x = 10
flt pi = 3.14
str name = "Boogeyman"
bool ready = 1
```

---

## 3. Functions

```py
def function_name(arg1, arg2):
    # Function body
    return value
```

* Indentation **matters** (4 spaces).
* Functions map to C functions automatically.

---

## 4. Conditionals

```py
if condition:
    # code
else:
    # code
```

* No parentheses needed in `if` statements (Python-style).

---

## 5. Printing

* Basic:

```py
print("Hello World")
```

* Formatted strings:

```c
fprint_str("Name is ${name}")
fprint_int("Score = ${score}")
fprint_flt("Pi = ${pi}")
```

---

## 6. Inline C

```c
__inline_c__{
    // C code here
}
```

* Global scope:

```c
__inline_c_global__{
    int global_var = 10;
}
```

---

## 7. Include Headers

```c
include "myheader.h"
include <stdio.h>
```

---

## 8. Indentation & Structure

* 4 spaces per indentation level
* Blocks are determined by **indentation**
* Top-level code automatically wrapped in `int main()`

---

