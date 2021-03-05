#pragma once

#include "plugin.h"

#include "PluginData.h"

#include <string>
#include <map>
#include <functional>
#include "world.h"

typedef void (*PluginKeyFunction)(int key, CVehicle* vehicle);

class PluginKey {
	public:
		PluginKeyFunction Function;

		bool Vehicle;

		bool VehicleSiren;

		PluginKey(PluginKeyFunction function, bool vehicle = false, bool vehicleSiren = false);
};

class PluginKeys {
	public:
		static void Register(int key, PluginKeyFunction function, bool vehicle = false, bool vehicleSiren = false);

		static void OnRender();

	private:
		static std::map<int, std::vector<PluginKey*>> functions;

		static std::map<int, bool> keys;
};
