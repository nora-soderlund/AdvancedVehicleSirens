#pragma once

#include "plugin.h"

#include "PluginConfig.h"
#include "PluginMultiplayer.h"

#include "game_sa/CCamera.h"
#include "game_sa/CVehicle.h"
#include "game_sa/CModelInfo.h"
#include "game_sa/CVehicleModelInfo.h"

class VehicleSteering {
	public:
		static void RegisterEvents();

	private:
		static bool enabled;

		static float mouseAccelerationHorizontal;
		static float mouseAccelerationVertical;
};
