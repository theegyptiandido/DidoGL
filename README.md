# DidoGL

**DidYouCallForAMinimalEngine?** — a minimal, OpenGL-style graphics API and tiny game engine written from hand in C++.

DidoGL is a small graphics layer: you call `dg::` functions (matrices, immediate-mode vertices, textures, and raw VBOs) and it issues the underlying OpenGL calls for you. It also ships a C-facing shim (`dgc_`) used by the ClassiCube backend.

## What's inside

| File | Role |
|------|------|
| `src/didogl.h` / `src/didogl.cpp` | The graphics API (namespace `dg`) |
| `src/didogl_c.h` / `src/didogl_c.cpp` | C API (prefix `dgc_`) with real VBO support |
| `src/platform.h` / `src/platform.cpp` | Win32 window + WGL OpenGL context + input |
| `src/engine.h` / `src/engine.cpp` | `diyqme` loop: `Init` / `Run(update, render)` / `Shutdown` |
| `src/game.cpp` | Spinning textured checker cube demo |
| `build.bat` | Builds `build\DidYouCallForAMinimalEngine.exe` |

## Build

```bat
build.bat
build\DidYouCallForAMinimalEngine.exe
```

Requires MSVC (Visual Studio Build Tools) and the Windows SDK.

## ClassiCube backend

`Graphics_DidoGL.c` is a graphics backend that lets [ClassiCube](https://github.com/UnknownShadow200/ClassiCube) render entirely through DidoGL (surfaced as the `CC_GFX_BACKEND_DidoGL` backend).

## Note

DidoGL wraps **OpenGL** (`opengl32`). It is a hand-written API layer, not a from-scratch GPU driver.
