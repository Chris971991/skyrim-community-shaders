# Building the Dovakarn fork of Community Shaders

This is Community Shaders 1.8.3 by the Community Shaders team
(https://github.com/community-shaders/skyrim-community-shaders, GPL-3.0) with main-thread performance changes
listed in `DOVAKARN_CHANGES.txt`. Only `CommunityShaders.dll` differs from the official 1.8.3 release; the shaders and
feature files are the official ones.

1. Visual Studio 2026 (18) with the C++ workload, CMake 4.2 or later, and vcpkg (`VCPKG_ROOT` set).
2. `git submodule update --init --recursive`
3. `cmake -S . --preset=Dovakarn` then `cmake --build --preset=Dovakarn`
   (`CMakeUserPresets.json`: the official `ALL` preset, without packaging or deployment, building the DLL only).
4. Output: `build/Dovakarn/Release/CommunityShaders.dll` (+ `.pdb`).

Switches for each change: `Data/SKSE/Plugins/CommunityShaders_Dovakarn.ini`, see `src/DovakarnPerf.h`.
