# Running Compy Programs

This guide explains how to compile and run programs written in **Compy** (`.cmpy` files) using the Compy transpiler.

---

## 1. Prerequisites

Before running Compy programs, ensure you have:

- **GCC** installed (or any C compiler compatible with your platform)
- **Compy transpiler** (`compy.exe` on Windows, `compy` on Linux/macOS)

Optional:

- Add `compy` to your **PATH** for easy access from any folder.

---

## 2. Compile the Compy Transpiler

If you don’t already have `compy` compiled:

```bash
gcc compy.c -O3 -o compy.exe   # Windows
gcc compy.c -O3 -o compy       # Linux/macOS
```

This creates the `compy` executable that translates `.cmpy` files into C code.

---

## 3. Generate C Code from Compy Source

Run the transpiler on your Compy source file:

```bash
./compy.exe test.cmpy    # Windows
./compy test.cmpy        # Linux/macOS
```

- This generates `out.c` in the **current working directory**.
- The generated C file contains all the translated code from your Compy program.

---

## 4. Compile the Generated C Code

Compile `out.c` into an executable:

```bash
gcc out.c -O3 -o out.exe   # Windows
gcc out.c -O3 -o out       # Linux/macOS
```

- This produces the final executable (`out.exe` on Windows, `out` on Linux/macOS).

---

## 5. Run the Executable

Run the program from your terminal:

```bash
./out.exe   # Windows
./out       # Linux/macOS
```

- The output reflects the behavior of your original `.cmpy` program.

---

## 6. Optional: Using Makefile

You can use the provided **Makefile** to simplify the build process:

```bash
make         # builds the Compy transpiler
make clean   # removes generated files
```

- Customize the Makefile if you want to support multiple `.cmpy` files or different output names.

---

### Notes

- `out.c` and `out.exe` are generated in the folder where you run `compy`.
- Adding `compy` to your _PATH_ allows you to run it from any directory without specifying the full path.
- Compy is designed to mimic Python’s simplicity while generating fast C code.
