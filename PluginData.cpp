#include "PluginData.h"

#include "PluginHelper.h"

#include <map>

int PluginData::DigitKey = LOBYTE(VkKeyScanEx('1', GetKeyboardLayout(0)));

bool PluginData::Credited = true;

bool PluginData::Focused = false;

int PluginData::CurrentVehicle = -1;

int PluginData::Corona = 0;

uint64_t PluginData::KeyTimestamp = timeSinceEpochMillisec();

RpMaterial* PluginData::Material;
RpClump* PluginData::Clump;
RpClump* PluginData::ClumpCustom;

std::map<int, nlohmann::json> PluginData::VehicleModelSirens;

std::map<int, VehicleSpotlightData*> PluginData::VehicleSpotlights;

std::list<std::pair<unsigned int*, unsigned int>> PluginData::VehicleEntries;

void PluginData::ResetCorona() {
	Corona = 0;
};
