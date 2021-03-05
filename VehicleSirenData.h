#pragma once

#include <string>
#include <vector>

#include "game_sa/CVector.h"
#include "game_sa/RenderWare.h"

#include "nlohmann/json.hpp"

#include "game_sa/CVehicle.h"

#include "VehicleDummyData.h"

using json = nlohmann::json;

class VehicleSirenData {
	public:
		std::string Key;

		RwRGBA Color;

		float Size;

		std::vector<int> Pattern;

		int PatternCount;

		int State;

		uint64_t Time;

		json JsonData;

		std::vector<VehicleDummyData> Dummies;

		VehicleSirenData(json data, CVehicle* vehicle, std::string key);

		void ResetSirenData();

		void FindNodesRecursive(RwFrame* frame, CVehicle* vehicle, bool bReSearch, bool bOnExtras);
};
