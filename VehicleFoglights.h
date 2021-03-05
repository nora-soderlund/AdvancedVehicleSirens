#pragma once

#include <map>

#include "plugin.h"

#include "game_sa/CAutomobile.h"

#include "PluginConfig.h"
#include "PluginHelper.h"
#include "PluginKeys.h"

#include "VehicleDummy.h"
#include "VehicleMaterials.h"

enum class VehicleFoglightState { FoglightLeft = 0, FoglightRight };

class VehicleFoglights {
	public:
		static void RegisterEvents();

	private:
		static std::map<int, std::map<VehicleFoglightState, std::vector<VehicleMaterial*>>> materials;
		static std::map<int, std::map<VehicleFoglightState, std::vector<VehicleDummy*>>> dummies;

		static std::map<int, bool> states;

		static void registerMaterial(CVehicle* vehicle, RpMaterial* material, VehicleFoglightState state);

		static void enableDummy(VehicleDummy* dummy, CVehicle* vehicle, float vehicleAngle, float cameraAngle);

		static void enableMaterial(VehicleMaterial* material);
};
