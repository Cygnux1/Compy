
# Supported Features in Compy

This document lists all the features currently supported by Compy.

---

## 1. Data Types

| Type      | Description                    | Notes                    |
|-----------|--------------------------------|--------------------------|
| `int`     | Integer numbers                | 32-bit signed           |
| `flt`     | Floating-point numbers         | Maps to `float` in C    |
| `double`  | Double precision float         | 64-bit                   |
| `char`    | Single character               |                          |
| `str`     | String                         | Maps to `char*`         |
| `bool`    | Boolean                        | Stored as `int` in C    |
| `long`    | Long integer                   | Maps to `long long`     |

---

## 2. Variable Declaration & Assignment

- Variables can be declared with type:

```c
int x = 5
flt pi = 3.14
str name = "Anish"
bool is_ready = 1
```

* Assignment supports expressions:

```c
int total = x + 10
```

---

## 3. Functions

* Defined using `def`:

```py
def add(a, b):
    int c = a + b
    return c
```

* Functions return integers by default (maps to `int` in C).

---

## 4. Conditional Statements

* Supports `if` and `else`:

```py
if x > 10:
    print("x is large")
else:
    print("x is small")
```

---

## 5. Printing / Formatted Output

* Standard print:

```py
print(x)
```

* Formatted output:

```c
fprint_str("Name is ${name}")
fprint_int("Total is ${total}")
fprint_flt("Pi = ${pi}")
```

* Supports `${}` interpolation.

---

## 6. Inline C

* Use for performance-critical code or C libraries:

```c
__inline_c__{
    printf("Inline C code works!\n");
}
```

* Global inline C:

```c
__inline_c_global__{
    int global_var = 42;
}
```

---

## 7. Miscellaneous

* Auto-generates `int main()` for top-level code.
* Supports basic arithmetic, comparisons, logical operations.
* Compatible with Makefile builds and GCC compilation.

---