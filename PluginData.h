#pragma once

#include <map>

#include "game_sa/RenderWare.h"

#include "VehicleSpotlightData.h"

#include "nlohmann/json.hpp"

class PluginData {
	public:
		static int DigitKey;

		static bool Credited;

		static bool Focused;

		static int Corona;

		static int CurrentVehicle;

		static uint64_t KeyTimestamp;

		static RpMaterial* Material;

		static RpClump* Clump;
		static RpClump* ClumpCustom;

		static std::map<int, nlohmann::json> VehicleModelSirens;
		
		static std::map<int, VehicleSpotlightData*> VehicleSpotlights;

		static std::list<std::pair<unsigned int*, unsigned int>> VehicleEntries;

		static void ResetCorona();
};
