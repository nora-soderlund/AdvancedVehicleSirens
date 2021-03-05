#pragma once

#include "IniReader/IniReader.h"

class PluginLightEnhancementConfig {
    public:
        bool InertiaEnabled;
        float InertiaAngle;

        PluginLightEnhancementConfig(CIniReader ini);
};

class PluginLightsConfig {
    public:
        bool Enabled;

        bool BrakeEnabled;

        bool FogEnabled;
        bool FogEnableWithSiren;

        PluginLightEnhancementConfig* Enhancement;

        PluginLightsConfig(CIniReader ini);
};

class PluginIndicatorsConfig {
    public:
        bool Enabled;

        int Delay;

        PluginIndicatorsConfig(CIniReader ini);
};

class PluginHiiiiiConfig {
    public:
        bool Enabled;

        PluginHiiiiiConfig(CIniReader ini);
};

class PluginPaintjobsConfig {
    public:
        bool Enabled;

        PluginPaintjobsConfig(CIniReader ini);
};

class PluginSpotlightsConfig {
    public:
        bool Enabled;

        PluginSpotlightsConfig(CIniReader ini);
};

class PluginSteeringConfig {
    public:
        bool Enabled;

        float Sensitivity;

        PluginSteeringConfig(CIniReader ini);
};

class PluginHelperConfig {
public:
    bool Hiiiii;

    bool Multiplayer;
    bool MultiplayerMessages;

    bool LogMaterials;
    bool LogDummies;

    bool ImVehFt;

    bool GameFocus;

    bool VersionCheck;
    bool IgnoreExceptions;

    PluginHelperConfig(CIniReader ini);
};

class PluginKeysConfig {
    public:
        int KeyDelay;

        int SirenState;
        bool SirenStateNumbers;

        int SirenMute;

        int IndicatorClear;
        int IndicatorLeft;
        int IndicatorBoth;
        int IndicatorRight;

        int SpotlightToggle;

        int Foglights;

        PluginKeysConfig(CIniReader ini);
};

class PluginSirenFlareConfig {
    public:
        bool Enabled = false;

        float Distance = 30.0f;

        PluginSirenFlareConfig(CIniReader ini);
};

class PluginSirenMuteConfig {
    public:
        bool Enabled = true;

        PluginSirenMuteConfig(CIniReader ini);
};

class PluginSirenShadowConfig {
    public:
        bool Enabled = false;
        bool ForceEnabled = false;

        PluginSirenShadowConfig(CIniReader ini);
};

class PluginSirenConfig {
    public:
        bool Enabled = true;

        float StreamDistance = 100.0f;

        bool DisableDefault = true;

        bool InertiaEnabled = true;

        PluginSirenFlareConfig* Flare;

        PluginSirenMuteConfig* Mute;

        PluginSirenShadowConfig* Shadow;

        PluginSirenConfig(CIniReader ini);
};

class PluginConfig {
    public:
        static void Read();

        static PluginSirenConfig* Siren;

        static PluginKeysConfig* Keys;

        static PluginHelperConfig* Helper;

        static PluginSteeringConfig* Steering;

        static PluginIndicatorsConfig* Indicators;

        static PluginLightsConfig* Lights;

        static PluginSpotlightsConfig* Spotlights;

        static PluginPaintjobsConfig* Paintjobs;

        static PluginHiiiiiConfig* Hiiiii;

        static int ReadKey(CIniReader ini, std::string header, std::string key, std::string _value);
};