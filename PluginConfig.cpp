#include "PluginConfig.h"
#include "PluginLogs.h"

#include "PluginData.h"

#include "IniReader/IniReader.h"

PluginLightEnhancementConfig::PluginLightEnhancementConfig(CIniReader ini) {
	InertiaEnabled = ini.ReadBoolean("LightEnhancement", "InertiaEnabled", true);
	InertiaAngle = ini.ReadFloat("LightEnhancement", "InertiaAngle", 5.0);
};

PluginLightsConfig* PluginConfig::Lights;

PluginLightsConfig::PluginLightsConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Lights", "Enabled", true);

	BrakeEnabled = ini.ReadBoolean("Lights", "BrakeEnabled", true);

	FogEnabled = ini.ReadBoolean("Lights", "FogEnabled", true);
	FogEnableWithSiren = ini.ReadBoolean("Lights", "FogEnableWithSiren", false);

	Enhancement = new PluginLightEnhancementConfig(ini);
};

PluginIndicatorsConfig* PluginConfig::Indicators;

PluginIndicatorsConfig::PluginIndicatorsConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Indicators", "Enabled", false);
	Delay = ini.ReadInteger("Indicators", "Delay", 500);
};

PluginHiiiiiConfig* PluginConfig::Hiiiii;

PluginHiiiiiConfig::PluginHiiiiiConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Hiiiii", "Enabled", false);
};

PluginPaintjobsConfig* PluginConfig::Paintjobs;

PluginPaintjobsConfig::PluginPaintjobsConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Paintjobs", "Enabled", true);
};

PluginSpotlightsConfig* PluginConfig::Spotlights;

PluginSpotlightsConfig::PluginSpotlightsConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Spotlights", "Enabled", true);
};

PluginKeysConfig* PluginConfig::Keys;

PluginKeysConfig::PluginKeysConfig(CIniReader ini) {
	HKL keyboard = GetKeyboardLayout(0);

	SirenState = PluginConfig::ReadKey(ini, "Keys", "SirenState", "R");

	SirenStateNumbers = ini.ReadBoolean("Keys", "SirenStateNumbers", true);

	SirenMute = PluginConfig::ReadKey(ini, "Keys", "SirenMute", "L");

	IndicatorClear = PluginConfig::ReadKey(ini, "Keys", "IndicatorClear", "SHIFT");
	IndicatorLeft = PluginConfig::ReadKey(ini, "Keys", "IndicatorLeft", "Z");
	IndicatorBoth = PluginConfig::ReadKey(ini, "Keys", "IndicatorBoth", "X");
	IndicatorRight = PluginConfig::ReadKey(ini, "Keys", "IndicatorRight", "C");

	SpotlightToggle = PluginConfig::ReadKey(ini, "Keys", "SpotlightToggle", "B");

	Foglights = PluginConfig::ReadKey(ini, "Keys", "Foglights", "J");
};

PluginSteeringConfig* PluginConfig::Steering;

PluginSteeringConfig::PluginSteeringConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Steering", "Enabled", true);

	Sensitivity = ini.ReadFloat("Steering", "Sensitivity", 1.0f);
};

PluginHelperConfig* PluginConfig::Helper;

PluginHelperConfig::PluginHelperConfig(CIniReader ini) {
	Multiplayer = ini.ReadBoolean("Helper", "Multiplayer", true);

	MultiplayerMessages = ini.ReadBoolean("Helper", "MultiplayerMessages", true);

	LogMaterials = ini.ReadBoolean("Helper", "Materials", NULL);

	if (LogMaterials == NULL)
		LogMaterials = ini.ReadBoolean("Helper", "LogMaterials", false);

	LogDummies = ini.ReadBoolean("Helper", "Dummies", NULL);

	if (LogDummies == NULL)
		LogDummies = ini.ReadBoolean("Helper", "LogDummies", false);

	ImVehFt = ini.ReadBoolean("Helper", "ImVehFt", true);

	GameFocus = ini.ReadBoolean("Helper", "GameFocus", true);

	VersionCheck = ini.ReadBoolean("Helper", "VersionCheck", true);

	IgnoreExceptions = ini.ReadBoolean("Helper", "IgnoreExceptions", false);
};

PluginSirenConfig* PluginConfig::Siren;

PluginSirenConfig::PluginSirenConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("Sirens", "Enabled", true);
	StreamDistance = ini.ReadFloat("Sirens", "StreamDistance", 100.0f);
	DisableDefault = ini.ReadBoolean("Sirens", "DisableDefault", true);
	InertiaEnabled = ini.ReadBoolean("Sirens", "InertiaEnabled", true);

	Flare = new PluginSirenFlareConfig(ini);

	Mute = new PluginSirenMuteConfig(ini);

	Shadow = new PluginSirenShadowConfig(ini);
};

PluginSirenFlareConfig::PluginSirenFlareConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("SirenFlares", "Enabled", true);
	Distance = ini.ReadFloat("SirenFlares", "Distance", 30.0f);
};

PluginSirenMuteConfig::PluginSirenMuteConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("SirenMute", "Enabled", true);
};

PluginSirenShadowConfig::PluginSirenShadowConfig(CIniReader ini) {
	Enabled = ini.ReadBoolean("SirenShadows", "Enabled", false);
	ForceEnabled = ini.ReadBoolean("SirenShadows", "ForceEnabled", false);
};

void PluginConfig::Read() {
	AddLog("Reading initialization configuration from AdvancedVehicleSirens.ini");

	int lineNumber = 0;
	
	std::string line;
	std::ifstream myfile;

	myfile.open(GetPath() + "/AdvancedVehicleSirens.ini");

	while (getline(myfile, line)) {
		if (lineNumber == 0) {
			std::size_t found = line.find("Advanced Vehicle Sirens by Cake");

			if (found == std::string::npos) {
				PluginData::Credited = false;
			}
		}
		else if (lineNumber == 1) {
			std::size_t found = line.find("336216");

			if (found == std::string::npos) {
				PluginData::Credited = false;
			}
		}

		lineNumber++;
	}

	myfile.close();

	CIniReader ini(GetPath() + "/AdvancedVehicleSirens.ini");

	if (ini.data.size() != 0) {
		PluginConfig::Siren = new PluginSirenConfig(ini);

		PluginConfig::Keys = new PluginKeysConfig(ini);

		PluginConfig::Helper = new PluginHelperConfig(ini);

		PluginConfig::Steering = new PluginSteeringConfig(ini);

		PluginConfig::Spotlights = new PluginSpotlightsConfig(ini);

		PluginConfig::Paintjobs = new PluginPaintjobsConfig(ini);

		PluginConfig::Hiiiii = new PluginHiiiiiConfig(ini);

		PluginConfig::Indicators = new PluginIndicatorsConfig(ini);

		PluginConfig::Lights = new PluginLightsConfig(ini);

		AddLog("Finished reading the configuration!");
	}
	else
		AddLog("Failed to read data from configuration file!");
};

int PluginConfig::ReadKey(CIniReader ini, std::string header, std::string key, std::string _value) {
	std::string value = ini.ReadString(header, key, _value);

	if (value == "LMB")
		return 0x01;

	if (value == "RMB")
		return 0x02;

	if (value == "MB1")
		return 0x05;

	if (value == "MB2")
		return 0x06;

	if (value == "BACKSPACE")
		return 0x08;

	if (value == "TAB")
		return 0x09;

	if (value == "SHIFT")
		return 0x10;

	if (value == "CTRL")
		return 0x12;

	if (value == "END")
		return 0x23;

	if (value == "HOME")
		return 0x24;

	if (value.length() > 2) {
		if (value[0] == '0' && value[1] == 'x') {
			int keyCode = ini.ReadInteger(header, key, NULL);

			if (keyCode != NULL)
				return keyCode;
		}
	}

	HKL keyboard = GetKeyboardLayout(0);

	return LOBYTE(VkKeyScanEx(value[0], keyboard));
};