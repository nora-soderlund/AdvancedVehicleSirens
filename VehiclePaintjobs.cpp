#include "VehiclePaintjobs.h"

std::map<int, std::map<int, int>> VehiclePaintjobs::modelPaintjobs;

std::map<int, bool> VehiclePaintjobs::vehiclePaintjob;

void VehiclePaintjobs::Read(int model, nlohmann::json json) {
	for (nlohmann::json::iterator paintjob = json.begin(); paintjob != json.end(); ++paintjob) {
		int _paintjob = std::stoi(paintjob.key());

		nlohmann::json identifiers = paintjob.value().find("identifiers").value();

		for (nlohmann::json::iterator variable = identifiers.begin(); variable != identifiers.end(); ++variable) {
			modelPaintjobs[model][variable.value()] = _paintjob;
		}
	}
};

void VehiclePaintjobs::OnVehicleSetModel(CVehicle* vehicle) {
	vehiclePaintjob[CPools::ms_pVehiclePool->GetIndex(vehicle)] = false;
};

void VehiclePaintjobs::OnVehicleRender(CVehicle* vehicle) {
	int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

	if (vehiclePaintjob[index] == true)
		return;

	vehiclePaintjob[index] = true;

	if (!modelPaintjobs.count(vehicle->m_nModelIndex))
		return;

	int identifier = PluginMultiplayer::GetVehicleIdentifier(PluginMultiplayer::GetVehiclePool(), vehicle);

	//PluginMultiplayer::AddChatMessage(std::string("Identifier " + std::to_string(identifier)).c_str());

	if (!modelPaintjobs[vehicle->m_nModelIndex].count(identifier))
		return;

	//PluginMultiplayer::AddChatMessage(std::string("Paintjob " + std::to_string(modelPaintjobs[vehicle->m_nModelIndex][identifier]) + " set to vehicle " + std::to_string(identifier)).c_str());

	vehicle->SetRemap(modelPaintjobs[vehicle->m_nModelIndex][identifier]);
};
