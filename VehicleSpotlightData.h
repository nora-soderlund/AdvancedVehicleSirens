#pragma once

#include "plugin.h"

#include "PluginHelper.h"
#include "PluginConfig.h"
#include "PluginMultiplayer.h"

#include "VehicleTextures.h"

#include "game_sa/CVehicle.h"
#include "game_sa/CCamera.h"
#include "game_sa/RenderWare.h"
#include "game_sa/NodeName.h"
#include "game_sa/CMatrix.h"
#include "game_sa/CCoronas.h"
#include "game_sa/CModelInfo.h"
#include "game_sa/CQuaternion.h"
#include "game_sa/CShadows.h"

#include <string>

class VehicleSpotlightData {
	public:
		CVehicle* Vehicle;

		RwFrame* Frame;

		bool Enabled;

		VehicleSpotlightData(CVehicle* vehicle);

		void FindNodesRecursive(RwFrame* frame, CVehicle* vehicle);
	
		void OnHudRender();
		void OnVehicleRender();
};
