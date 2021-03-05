#pragma once

#include "game_sa/CVehicle.h"
#include "game_sa/CPools.h"

#include "nlohmann/json.hpp"

#include "PluginHelper.h"
#include "PluginMultiplayer.h"

#include <string>
#include <map>

class VehiclePaintjobs {
	public:
		static void Read(int model, nlohmann::json json);

		static void OnVehicleSetModel(CVehicle* vehicle);

		static void OnVehicleRender(CVehicle* vehicle);

	private:
		static std::map<int, std::map<int, int>> modelPaintjobs;

		static std::map<int, bool> vehiclePaintjob;
};
