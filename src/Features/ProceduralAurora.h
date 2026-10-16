#pragma once

#include "Buffer.h"

#include <chrono>

struct ProceduralAurora : Feature
{
public:
	virtual inline std::string GetName() override { return "Procedural Aurora"; }
	virtual std::string GetDisplayName() override { return T("feature.procedural_aurora.name", "Procedural Aurora"); }
	virtual inline std::string GetShortName() override { return "ProceduralAurora"; }
	virtual inline std::string_view GetShaderDefineName() override { return "PROCEDURAL_AURORA"; }
	virtual std::string_view GetCategory() const override { return FeatureCategories::kSky; }
	virtual std::pair<std::string, std::vector<std::string>> GetFeatureSummary() override
	{
		return { T("feature.procedural_aurora.description", "Replaces the flat vanilla aurora with an animated, procedurally generated aurora painted into the sky."),
			{ T("feature.procedural_aurora.key_feature_1", "Flowing curtains of glowing gas with soft rays, haze and a glow above"),
				T("feature.procedural_aurora.key_feature_2", "A lower edge tint, a main color and a top color"),
				T("feature.procedural_aurora.key_feature_3", "A new pattern every night, shown whenever the vanilla aurora would be"),
				T("feature.procedural_aurora.key_feature_4", "Color presets plus color, brightness and motion controls") } };
	}

	/** @brief Sky draws the aurora into the sky dome; Effect skips the vanilla aurora ribbons it replaces. */
	virtual bool HasShaderDefine(RE::BSShader::Type shaderType) override
	{
		return shaderType == RE::BSShader::Type::Sky || shaderType == RE::BSShader::Type::Effect;
	}

	/** @brief True for vanilla aurora ribbons ("Aurora:N", "AuroraGB:N", ...); other models in the aurora slot (Sovngarde, Blood Moon) use other names. */
	static bool IsVanillaAuroraRibbon(const char* shapeName) { return shapeName && _strnicmp(shapeName, "Aurora", 6) == 0; }

	struct Settings
	{
		bool Enabled = true;
		float Brightness = 0.75f;
		float Speed = 0.6f;  // real auroras drift slowly; storms speed up on their own
		float RayDetail = 0.85f;
		float RayStrength = 0.85f;
		float FoldStrength = 0.9f;
		float Softness = 0.7f;
		float Haze = 0.8f;
		float Nebula = 0.8f;
		float FringeAmount = 0.75f;
		float CrownStart = 0.22f;
		bool NewPatternEachNight = true;
		float GreatStormChance = 0.2f;
		float ColorVariety = 0.5f;
		std::array<float, 3> FringeColor = { 0.70f, 1.00f, 0.50f };
		std::array<float, 3> BodyColor = { 0.15f, 1.00f, 0.45f };
		std::array<float, 3> CrownColor = { 1.00f, 0.28f, 0.42f };
	} settings;

	struct alignas(16) CommonBufferData
	{
		float4 FringeColor;
		float4 BodyColor;
		float4 CrownColor;
		float Brightness;
		float Time;  // animation clock: speed and night strength applied, reset each in-game night
		float RayDetail;
		float Softness;
		float FoldStrength;
		float RayStrength;
		float Seed;
		uint Enabled;
		float3 Atmosphere;  // x: vanilla aurora visibility, y: haze, z: nebula glow
		float pad0;
	};
	STATIC_ASSERT_ALIGNAS_16(CommonBufferData);
	static_assert(sizeof(CommonBufferData) == 96, "ProceduralAurora::CommonBufferData must match ProceduralAuroraSettings in SharedData.hlsli");

	/** @brief Packs the settings for the shared feature constant buffer (SharedData::proceduralAuroraSettings). */
	CommonBufferData GetCommonBufferData();

	/** @brief Draws the settings, with an Advanced section for fine tuning. */
	virtual void DrawSettings() override;

	virtual void LoadSettings(json& o_json) override;
	virtual void SaveSettings(json& o_json) override;
	virtual void RestoreDefaultSettings() override;

private:
	/** @brief What the current night looks like: a storm level and the colors it uses. */
	struct Night
	{
		float storm = 0.7f;
		std::array<float, 3> fringe{};
		std::array<float, 3> body{};
		std::array<float, 3> crown{};
		float fringeAmount = 0.0f;
		float crownStart = 0.0f;
		int colorPreset = -1;  // -1: the colors from the settings
	};

	/** @brief Rolls the current night's storm level and colors from the in-game day count. */
	Night GetNight() const;

	/** @brief In-game night number; it rolls over at noon so a night keeps its look past midnight. */
	static uint32_t GetNightIndex();

	/** @brief How visible the vanilla aurora is right now, 0 to 1: the game fades it through its ribbons' material alpha. */
	static float GetVanillaAuroraVisibility();

	/** @brief Index of the color preset the current colors match, or -1 for custom colors. */
	int MatchPreset() const;

	/** @brief Copies a color preset into the settings. */
	void ApplyPreset(int index);

	float auroraVisibility = 0.0f;  // last value sent to the shader, shown in the menu

	// Animation clock, advanced on the CPU so speed changes never make the pattern jump
	double animationTime = 0.0;
	std::chrono::steady_clock::time_point lastClockUpdate{};
	uint32_t clockNight = UINT32_MAX;
};
