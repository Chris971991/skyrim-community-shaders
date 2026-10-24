# Building the Dovakarn fork of Community Shaders

This is Community Shaders 1.8.3 by the Community Shaders team
(https://github.com/community-shaders/skyrim-community-shaders, GPL-3.0) with main-thread performance changes
listed in `DOVAKARN_CHANGES.txt`. Only `CommunityShaders.dll` differs from the official 1.8.3 release; the shaders and
feature files are the official ones, except Screen-Space Shadows' shaders (its distance fade, 2026-10-25).

1. Visual Studio 2026 (18) with the C++ workload, CMake 4.2 or later, and vcpkg (`VCPKG_ROOT` set).
2. `git submodule update --init --recursive`
3. `cmake -S . --preset=Dovakarn` then `cmake --build --preset=Dovakarn`
   (`CMakeUserPresets.json`: the official `ALL` preset, without packaging or deployment, building the DLL only).
4. Output: `build/Dovakarn/Release/CommunityShaders.dll` (+ `.pdb`).

Switches for each change: `Data/SKSE/Plugins/CommunityShaders_Dovakarn.ini`, see `src/DovakarnPerf.h`.

## Feature files Dovakarn serves (2026-10-24)

Besides the DLL, Dovakarn's server hands its players six features from this fork's `features` folder, at the same
commit as the DLL, so the shaders always match the plugin that compiles them: Wetness Effects, Skylighting, Terrain
Blending, Terrain Variation and Screen Space GI unchanged, and Screen-Space Shadows with Dovakarn's distance fade
(2026-10-25, DOVAKARN_CHANGES.txt; its constant buffer must match this DLL's). `powershell -File tools\dovakarn-features.ps1 -Out <folder>`
copies each one's `Shaders\Features\<Name>.ini` and shader folder into `<folder>\Shaders`; Dovakarn copies them into
its server's player-settings folder. Not served: Terrain Helper (needs its own plugin, TerrainHelper.esp) and
Exponential Height Fog (unreleased in 1.8.3: off by default, with no tuned look).
