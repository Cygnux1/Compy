# Compy

**Compy** is a compiled Python-like language with a simple, intuitive syntax. It transpiles Compy code (`.cmpy`) into optimized C code, producing fast and efficient executables.

---

## Key Advantages

- **Python-style simplicity:** Write readable, concise code without C boilerplate.  
- **Compiled performance:** Compy generates native C code for high execution speed.  
- **Safe and maintainable:** Minimal syntax reduces complexity and potential errors.

---

## Features

- Compy transpiler written in C.  
- Converts Compy syntax into clean C code (`out.c`).  
- Supports inline C blocks using `__inline_c__` and `__inline_c_global__`.  
- Auto-generates `int main()` for top-level code.  
- Handles:
  - Function definitions (`def`)  
  - Printing and formatted output (`print`, `fprint_str`, `fprint_int`, `fprint_flt`)  
  - Variable declarations (`int`, `flt`, `double`, `str`, `bool`, `char`)  
  - Conditional statements (`if`, `else`)  
- Cross-platform support (Windows and Linux with GCC).  
- Makefile-compatible build workflow.

---

## Documentation

Detailed documentation is available in the `docs/` directory:  

- [Run Guide](docs/run.md) – Instructions for compiling and executing Compy code.  
- [Supported Features](docs/supported.md) – Full list of supported language features.

---

## Build Instructions

Compile the transpiler:

```bash
gcc compy.c -O3 -o compy.exe

# Or use Makefile

make
```

Use Compy to generate C code:

```bash
./compy.exe test.cmpy
```

Compile the generated C code:

```bash
gcc out.c -O3 -o out.exe
```

---

## License

MIT License — see LICENSE for details.

---
