#pragma once

#include <map>

#include "plugin.h"

#include "PluginConfig.h"
#include "PluginHelper.h"
#include "PluginKeys.h"

#include "VehicleDummy.h"
#include "VehicleMaterials.h"


enum VehicleIndicatorState { Left = 0, Right, Both };

class VehicleIndicators {
	public:
		static void RegisterEvents();

	private:
		static std::map<int, std::map<VehicleIndicatorState, std::vector<RpMaterial*>>> materials;
		static std::map<int, std::map<VehicleIndicatorState, std::vector<VehicleDummy*>>> dummies;

		static void registerMaterial(CVehicle* vehicle, RpMaterial* &material, VehicleIndicatorState state);

		static void enableMaterial(RpMaterial* material);

		static void enableDummy(int id, VehicleDummy* dummy, CVehicle* vehicle, float vehicleAngle, float cameraAngle);

		static uint64_t delay;

		static bool delayState;

		static std::map<int, VehicleIndicatorState> states;
};
