# Applied changes to vendored CLIPS source

This file documents every deviation of the `core-*/` trees from the upstream CLIPS source.
Keep it updated whenever a `core-*` file is edited. (See `CLAUDE.md` → "Patching vendored
CLIPS source".)

---

## `facthsh.c` — `HashFact` signed-integer-overflow fix

**Files:** `core-6.4.1/facthsh.c`, `core-6.4.2/facthsh.c`
**Applied:** 2026-07-15

**Change:**
```c
// before (upstream)
count += theFact->whichDeftemplate->header.name->bucket * 73981;
// after
count += (size_t) theFact->whichDeftemplate->header.name->bucket * 73981;
```

**Why:** `bucket * 73981` was evaluated in `int`. For large buckets it overflows `int`
(e.g. `57176 * 73981 ≈ 4.23e9 > INT_MAX`), which is **undefined behavior**. clang (macOS)
and gcc (Linux) compile that UB differently at `-O3`, so fact hashes diverged and the
`009_STRING_BDI` test (many long UUID-string facts) failed only on **gcc arm64** while
passing on x86_64 and macOS arm64. `count` is already `size_t`, so casting the operand makes
the multiply 64-bit — deterministic, no overflow, identical across compilers/arches.

**Verification:** UBSan (`-fsanitize=undefined`) on `009_STRING_BDI` reported the overflow
before the change and no longer reports it after; test still passes on macOS arm64.

**Applied to both 6.4.1 and 6.4.2** because `clipspy-1.0.6` compiles against `core-6.4.1/`,
so 6.4.1 is actively maintained (not a frozen version).
