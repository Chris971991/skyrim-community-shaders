#pragma once

// Dovakarn fork of Community Shaders 1.8.3 (GPL-3.0): main-thread performance switches.
// Modified by the Dovakarn team, 2026-10-18. Every change in this fork is listed in DOVAKARN_CHANGES.txt.
//
// Each change can be turned off without a rebuild, for A/B measuring or if a problem shows up:
//   Data\SKSE\Plugins\CommunityShaders_Dovakarn.ini
//   [Perf]
//   ParticleLightShaderGate=1   ; skip the particle-light test for passes not drawn by the effect shader
//   PrefetchNextPass=1          ; prefetch the next render pass's property and geometry while this one draws
//   ProfilerOnlyWhenVisible=1   ; run the GPU/CPU pass profiler only while CS's menu or overlay is open
//   PrefetchPassObjects=1       ; prefetch this pass's mesh renderer data, material, alpha property and skin
//   LogParticleLights=0         ; debug: log particle lights queued per frame every 600 frames
// A missing file or key means the default shown.

#include <Windows.h>

namespace DovakarnPerf
{
	struct Settings
	{
		bool particleLightShaderGate = true;
		bool prefetchNextPass = true;
		bool profilerOnlyWhenVisible = true;
		bool prefetchPassObjects = true;
		bool logParticleLights = false;
	};

	inline Settings settings{};

	inline void Load()
	{
		constexpr auto path = ".\\Data\\SKSE\\Plugins\\CommunityShaders_Dovakarn.ini";
		settings.particleLightShaderGate = GetPrivateProfileIntA("Perf", "ParticleLightShaderGate", 1, path) != 0;
		settings.prefetchNextPass = GetPrivateProfileIntA("Perf", "PrefetchNextPass", 1, path) != 0;
		settings.profilerOnlyWhenVisible = GetPrivateProfileIntA("Perf", "ProfilerOnlyWhenVisible", 1, path) != 0;
		settings.prefetchPassObjects = GetPrivateProfileIntA("Perf", "PrefetchPassObjects", 1, path) != 0;
		settings.logParticleLights = GetPrivateProfileIntA("Perf", "LogParticleLights", 0, path) != 0;
	}
}
