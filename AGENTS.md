# AGENTS.md
Repository guide for coding agents working in `libframe`.

## Project Overview
- Language: C (C11).
- Build system: CMake.
- Library target: `frame` (root `CMakeLists.txt`).
- Test framework: Unity (`tests/unity`).
- Test executables: `test_bit`, `test_array` (`tests/CMakeLists.txt`).

Sources of truth:
- `CMakeLists.txt`
- `tests/CMakeLists.txt`
- `.clang-format`
- `tests/unity/.editorconfig` (Unity subtree only)

## Build / Test / Lint Commands
Run commands from repo root.

### Configure
```bash
cmake -S . -B build
```

### Build
```bash
cmake --build build
```

### Clean rebuild
```bash
rm -rf build
cmake -S . -B build
cmake --build build
```

### Run all tests
```bash
ctest --test-dir build
```

Verbose + failure details:
```bash
ctest --test-dir build --output-on-failure -V
```

### Run a single test executable
By CTest name:
```bash
ctest --test-dir build -R '^test_array$' --output-on-failure
ctest --test-dir build -R '^test_bit$' --output-on-failure
```

By direct binary:
```bash
./build/tests/test_array
./build/tests/test_bit
```

### Run a single test case
Current Unity setup uses hardcoded `RUN_TEST(...)` calls in each test `main()` and
does not provide a runtime case filter.

To run one case only:
1. Temporarily leave only one `RUN_TEST(...)` call in the relevant `tests/test_*.c`.
2. Rebuild: `cmake --build build`
3. Run the executable (`./build/tests/test_array` or `./build/tests/test_bit`).
4. Restore all `RUN_TEST(...)` calls before finalizing.

### Formatting
No dedicated lint target exists. Formatting policy is `.clang-format`.

Check formatting:
```bash
clang-format --dry-run --Werror --style=file src/*.c include/lf/*.h tests/*.c
```

Apply formatting:
```bash
clang-format -i --style=file src/*.c include/lf/*.h tests/*.c
```

### Typecheck
No standalone typecheck/static-analysis command is configured in-repo. Baseline
validation is successful compile + tests.

## Code Style Guidelines

### Includes and imports
- In `.c` files, include the module header first when applicable.
- Then include standard library headers, then project headers.
- Keep ordering formatter-compatible (`SortIncludes: true`,
  `IncludeBlocks: Regroup`).

### Formatting and layout
- `.clang-format` is the canonical formatter.
- Important observed settings:
  - `IndentWidth: 2`
  - `ColumnLimit: 80`
  - `BreakBeforeBraces: Attach`
  - `PointerAlignment: Left`
- Preserve existing compact style (including early returns where used).

### Types and macros
- Prefer project typedefs from `include/lf/bit.h`:
  - `u8/u16/u32/u64`
  - `i8/i16/i32/i64`
  - `usize/isize`
  - `f32/f64`
- Use `bool` for success/failure APIs.
- Reuse established helpers: `lf_cast`, `lf_countof`, `lf_zerout`.

### Naming conventions
- Prefix public API symbols with `lf_`.
- Use snake_case for function, variable, and parameter names.
- Use uppercase `LF_*` for constants and preprocessor macros.
- Keep test functions descriptive and `test_*` prefixed.

### Error handling
- Return explicit failure (`false`) for recoverable failures.
- Check allocation and dependent call failures immediately.
- Use `lf_assert(...)` for invariants/preconditions.
- Keep panic behavior centralized through `LF_PANIC_SYM`/`lf_panic`.
- Never ignore error paths.

### Memory and invariants
- Initialize struct/object state before use (zero-init patterns are common).
- Keep init/deinit pairs balanced.
- Preserve container invariants (`len <= cap`, valid indices).
- In resize-style logic, commit state only after successful allocation/copy.

### Testing conventions (Unity)
- Test files live in `tests/` and compile to separate executables.
- Each file defines `setUp(void)` and `tearDown(void)`.
- Tests are `static void test_*` and registered via `RUN_TEST(...)` in `main()`.
- Prefer specific assertion macros (`TEST_ASSERT_EQUAL_UINT64`, etc.).

## Suggested Agent Validation Flow
For non-trivial code edits:
1. `cmake -S . -B build`
2. `cmake --build build`
3. Run impacted test executable(s)
4. `ctest --test-dir build --output-on-failure`
5. Run clang-format check on touched files

If `src/*` or `include/lf/*` changed, always run full test suite before finishing.

## Cursor / Copilot Rules
No repository rule files were found at write time:
- `.cursorrules` (not found)
- `.cursor/rules/` (not found)
- `.github/copilot-instructions.md` (not found)

If these are added later, treat them as higher-priority repository instructions and
merge their constraints into this file.
