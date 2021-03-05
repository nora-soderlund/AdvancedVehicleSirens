#pragma once

#include <map>

#include "plugin.h"

#include "game_sa/CAutomobile.h"
#include "game_sa/CClock.h"

#include "PluginConfig.h"
#include "PluginHelper.h"
#include "PluginKeys.h"

#include "VehicleDummy.h"
#include "VehicleMaterials.h"

enum class VehicleLightState { Something = 0, LightLeft, LightRight, TailLight, Reverselight, Brakelight, Light, Daylight, Nightlight };

class VehicleLights {
	public:
		static void RegisterEvents();

	private:
		static std::map<int, std::map<VehicleLightState, std::vector<VehicleMaterial*>>> materials;
		static std::map<int, std::map<VehicleLightState, std::vector<VehicleDummy*>>> dummies;

		static std::map<int, bool> states;

		static void registerMaterial(CVehicle* vehicle, RpMaterial* material, VehicleLightState state);

		static void renderLights(CVehicle* vehicle, VehicleLightState state, float vehicleAngle, float cameraAngle);

		static void enableDummy(int id, VehicleDummy* dummy, CVehicle* vehicle, float vehicleAngle, float cameraAngle);

		static void enableMaterial(VehicleMaterial* material);
};
