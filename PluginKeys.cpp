#include "PluginKeys.h"

std::map<int, std::vector<PluginKey*>> PluginKeys::functions;

std::map<int, bool> PluginKeys::keys;

PluginKey::PluginKey(PluginKeyFunction function, bool vehicle, bool vehicleSiren) {
	Function = function;

	Vehicle = vehicle;
	VehicleSiren = vehicleSiren;
};

void PluginKeys::Register(int key, PluginKeyFunction function, bool vehicle, bool vehicleSiren) {
	functions[key].push_back(new PluginKey(function, vehicle, vehicleSiren));

	if (!keys.contains(key))
		keys[key] = false;
};

void PluginKeys::OnRender() {
	if (!PluginData::Focused)
		return;

	if (PluginMultiplayer::GetMouseState())
		return;

	for (std::map<int, std::vector<PluginKey*>>::iterator key = functions.begin(); key != functions.end(); ++key) {
		if (plugin::KeyPressed(key->first)) {
			if (keys[key->first])
				continue;

			keys[key->first] = true;

			continue;
		}
		else if (keys[key->first] == true) {
			keys[key->first] = false;

			for (std::vector<PluginKey*>::iterator function = key->second.begin(); function != key->second.end(); ++function) {
				CVehicle* vehicle = FindPlayerVehicle(-1, false);

				if ((*function)->Vehicle && !vehicle)
					continue;

				(*function)->Function(key->first, vehicle);
			}
		}
	}
};
