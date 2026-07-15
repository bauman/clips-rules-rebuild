# Applied changes to vendored CLIPS source

This file documents every deviation of the `core-*/` trees from the upstream CLIPS source.
Keep it updated whenever a `core-*` file is edited. (See `CLAUDE.md` → "Patching vendored
CLIPS source".)

---

**None.** The vendored `core-*/` CLIPS source is currently unmodified from upstream.

> Build-flag differences (e.g. `-fno-strict-aliasing`, `-std=c99`, `-D<CLIPS_OS>`) live in the
> repo's own `core-*/CMakeLists.txt`, not in the CLIPS source, so they are not tracked here —
> they just carry over what the upstream `makefile` `release` recipe already uses.
>
> History: a `facthsh.c` signed-overflow patch and a `memalloc.h` `GenCopyMemory` NULL-guard
> were briefly applied while chasing an arm64 test failure, then reverted — the actual bug was
> in the repo's own `test-core-*/bdi/009_TemplatesBDI.c` (misusing a `strncmp` result as a
> count), not in CLIPS.
