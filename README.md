# clips-rules-rebuild

Local rebuilder for [CLIPS](http://www.clipsrules.net/) (the C rules engine) and
[clipspy](https://clipspy.readthedocs.io/en/latest/) (its Python/cffi bindings).

This repo vendors **several complete versions of both, side by side**, and a single CMake
build lets you pick which pair to compile — producing shared/static libraries, a `clipscli`
executable, and a Python wheel, on both Linux and Windows.

## Repository layout

| Path | Contents |
|---|---|
| `core-6.31/`, `core-6.40/`, `core-6.4.1/`, `core-6.4.2/` | Full CLIPS C source, one `CMakeLists.txt` each |
| `clipspy-0.3.3/` … `clipspy-1.0.6/` | Full clipspy Python packages (`setup.py`, `clips/`, `lib/clips.cdef`) |
| `test-core-6.40/`, `test-core-6.4.1/`, `test-core-6.4.2/` | CTest C programs linking `clips-static` |
| `CMakeLists.txt` | Top-level version selector |
| `.github/workflows/` | Linux and Windows CI |

## Version matrix

The top-level `CMakeLists.txt` builds one version pair at a time, chosen by option:

| CMake option | CLIPS core | clipspy |
|---|---|---|
| `-Dbuild-631=ON` | 6.31 | 0.3.3 |
| `-Dbuild-640=ON` | 6.40 | 1.0.0 |
| `-Dbuild-641-4=ON` | 6.4.1 | 1.0.4 |
| `-Dbuild-641-5=ON` | 6.4.1 | 1.0.5 |
| `-Dbuild-641-6=ON` **(default)** | 6.4.1 | 1.0.6 |
| `-Dbuild-642=ON` | 6.4.2 | 1.0.0 |

Additional option: `-Dstatic-cli=ON` builds a statically-linked `clipscli` (default OFF).

## How it works

**CLIPS core.** Each `core-*/CMakeLists.txt` compiles every `.c` file into its own `OBJECT`
library, then aggregates them into a shared library (`clips` → `libclips.so`), a static
archive (`clips-static`), and the `clipscli` executable. `cmake --install` lays out headers,
libraries, and the CLI under `CMAKE_INSTALL_PREFIX`.

**clipspy.** Built separately from CMake using cffi: `setup.py bdist_wheel` invokes
`clips/clips_build.py`, which compiles against the freshly-installed `libclips` plus the
local core headers and reads the API surface from `lib/clips.cdef`.

## Building

### Linux / macOS

```sh
mkdir build && cd build
cmake -Dbuild-641-6=ON -DCMAKE_INSTALL_PREFIX=/usr ..   # pick a version option
cmake --build . --config Release
ctest                                                   # run the test-core-* suite
sudo cmake --install .

# Python bindings (after the library is installed):
cd ../clipspy-1.0.6
python3 setup.py bdist_wheel
pip install dist/*.whl
python3 -c "import clips"                               # smoke test
```

For a static CLI, add `-Dstatic-cli=ON`.

### Windows

```powershell
mkdir build; cd build
cmake -Dbuild-641-6=ON -DCMAKE_INSTALL_PREFIX=c:\usr -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=True ..
cmake --build . --target ALL_BUILD --config Release
cmake --install .
```

## Continuous integration

Three GitHub-hosted builders, all following the same shape — configure with CMake per
version, build, `ctest`, install, then build/install the clipspy wheel and smoke-test
`import clips`:

| Workflow | Runner | Prefix | Notes |
|---|---|---|---|
| `linuxbuild.yml` | `ubuntu-24.04` | `/usr` | static + dynamic; `sudo apt` deps |
| `windowsbuild.yml` | `windows-2022` | `c:\usr` | MSVC via `ilammy/msvc-dev-cmd`; `dumpbin` checks |
| `macbuild.yml` | `macos-14` (arm64) | `/usr/local` | **dynamic only** — `-static` isn't supported on macOS |

**Triggers.** Each workflow runs on `push` to `main` and the dev branches, and on
`pull_request` to `main`. A `concurrency` group keyed to the branch cancels superseded runs
(so a push and its PR don't both run to completion). Windows/Linux share `windev`/`lindev`;
macOS uses `macdev`.

**Version / artifact policy.** All builders still *compile* 6.31 (+ clipspy 0.3.3) as a
build check, but **only publish 6.40 artifacts** (`clipscli`/libs zip + the clipspy-1.0.0
wheel) — we're migrating consumers to **at least 6.40**. 6.31/clipspy-0.3.3 artifacts are no
longer uploaded.

> When adding a version, update the CMake options **and** every workflow. Each CI step must
> pin exactly one version (e.g. `-Dbuild-640=ON -Dbuild-641-6=OFF`) — because
> `build-641-6` defaults ON, an unpinned step pulls in a second version and collides. See
> `CLAUDE.md` for the shared-library placement details each OS needs for `import clips`.

