#include "VehicleIndicators.h"

std::map<int, std::map<VehicleIndicatorState, std::vector<RpMaterial*>>> VehicleIndicators::materials;
std::map<int, std::map<VehicleIndicatorState, std::vector<VehicleDummy*>>> VehicleIndicators::dummies;

std::map<int, VehicleIndicatorState> VehicleIndicators::states;

void VehicleIndicators::RegisterEvents() {
	VehicleMaterials::Register((VehicleMaterialFunction)[](CVehicle* vehicle, RpMaterial* material) {
		if (material->color.blue == 0) {
			if (material->color.red == 255) {
				if (material->color.green > 55 && material->color.green < 59) {
					registerMaterial(vehicle, material, Right);
				
					return material;
				}
				else return material;
			}
			else if (material->color.green == 255) {
				if (material->color.red > 180 && material->color.red < 184) {
					registerMaterial(vehicle, material, Left);

					return material;
				}
				else return material;
			}
			else return material;
		}

		if (material->color.red != 255 || ((material->color.green < 4) || (material->color.green > 5)) || material->color.blue != 128 || std::string(material->texture->name).rfind("light", 0) != 0)
			return material;

		// indicator
		if (material->color.green == 4)
			registerMaterial(vehicle, material, Left);
		else
			registerMaterial(vehicle, material, Right);
	
		return material;
	});

	if (!PluginConfig::Indicators->Enabled)
		return;

	VehicleMaterials::RegisterDummy((VehicleDummyFunction)[](CVehicle* vehicle, RwFrame* frame, std::string name, bool parent) {
		int start = -1;

		if (name.rfind("turnl_", 0) == 0)
			start = 6;
		else if (name.rfind("indicator_", 0) == 0)
			start = 10;

		if (start == -1)
			return;

		int model = vehicle->m_nModelIndex;

		VehicleIndicatorState state = (toupper(name[start]) == 'L') ? (Left) : (Right);

		char position = tolower(name[start + 1]);

		int type = (position == 'f') ? (0) : ((position == 'r') ? (0) : (2));

		dummies[model][state].push_back(new VehicleDummy(frame, name, start + 3, parent, type, { 255, 98, 0, 128 }));
	});

	PluginKeys::Register(PluginConfig::Keys->IndicatorClear, (PluginKeyFunction)[](int key, CVehicle* vehicle) {
		int model = vehicle->m_nModelIndex;

		if (materials[model].size() == 0)
			return;

		int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

		if (!states.contains(index))
			return;

		states.erase(index);

		if (states.size() == 0) {
			delay = 0;

			delayState = false;
		}
	}, true, false);

	PluginKeys::Register(PluginConfig::Keys->IndicatorLeft, (PluginKeyFunction)[](int key, CVehicle* vehicle) {
		int model = vehicle->m_nModelIndex;

		if (materials[model].size() == 0)
			return;

		int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

		states[index] = Left;
	}, true, false);

	PluginKeys::Register(PluginConfig::Keys->IndicatorRight, (PluginKeyFunction)[](int key, CVehicle* vehicle) {
		int model = vehicle->m_nModelIndex;

		if (materials[model].size() == 0)
			return;

		int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

		states[index] = Right;
	}, true, false);

	PluginKeys::Register(PluginConfig::Keys->IndicatorBoth, (PluginKeyFunction)[](int key, CVehicle* vehicle) {
		int model = vehicle->m_nModelIndex;

		if (materials[model].size() == 0)
			return;

		int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

		states[index] = Both;
	}, true, false);

	VehicleMaterials::RegisterRender((VehicleMaterialRender)[](CVehicle* vehicle, int index) {
		if (!delayState)
			return;

		int model = vehicle->m_nModelIndex;

		if (materials[model].size() == 0)
			return;

		if (!states.contains(index))
			return;

		VehicleIndicatorState state = states[index];

		int id = 0;

		if (state != VehicleIndicatorState::Both) {
			if (materials[model][state].size() == 0)
				return;

			for (std::vector<RpMaterial*>::iterator material = materials[model][state].begin(); material != materials[model][state].end(); ++material)
				enableMaterial((*material));

			float vehicleAngle = (vehicle->GetHeading() * 180.0f) / 3.14f;

			float cameraAngle = (((CCamera*)0xB6F028)->GetHeading() * 180.0f) / 3.14f;

			for (std::vector<VehicleDummy*>::iterator dummy = dummies[model][state].begin(); dummy != dummies[model][state].end(); ++dummy) {
				id++;

				enableDummy(id, (*dummy), vehicle, vehicleAngle, cameraAngle);
			}
		}
		else {
			float vehicleAngle = (vehicle->GetHeading() * 180.0f) / 3.14f;

			float cameraAngle = (((CCamera*)0xB6F028)->GetHeading() * 180.0f) / 3.14f;

			for (std::vector<RpMaterial*>::iterator material = materials[model][VehicleIndicatorState::Left].begin(); material != materials[model][VehicleIndicatorState::Left].end(); ++material)
				enableMaterial((*material));

			for (std::vector<VehicleDummy*>::iterator dummy = dummies[model][VehicleIndicatorState::Left].begin(); dummy != dummies[model][VehicleIndicatorState::Left].end(); ++dummy) {
				id++;

				enableDummy(id, (*dummy), vehicle, vehicleAngle, cameraAngle);
			}

			for (std::vector<RpMaterial*>::iterator material = materials[model][VehicleIndicatorState::Right].begin(); material != materials[model][VehicleIndicatorState::Right].end(); ++material)
				enableMaterial((*material));

			for (std::vector<VehicleDummy*>::iterator dummy = dummies[model][VehicleIndicatorState::Right].begin(); dummy != dummies[model][VehicleIndicatorState::Right].end(); ++dummy) {
				id++;

				enableDummy(id, (*dummy), vehicle, vehicleAngle, cameraAngle);
			}
		}
	});

	plugin::Events::drawingEvent += []() {
		if (states.size() == 0)
			return;

		uint64_t timestamp = timeSinceEpochMillisec();

		if ((timestamp - delay) < PluginConfig::Indicators->Delay)
			return;

		delay = timestamp;
		delayState = !delayState;
	};
};

void VehicleIndicators::registerMaterial(CVehicle* vehicle, RpMaterial* &material, VehicleIndicatorState state) {
	material->color.red = material->color.green = material->color.blue = 255;

	if (PluginConfig::Indicators->Enabled)
		materials[vehicle->m_nModelIndex][state].push_back(material);
};

uint64_t VehicleIndicators::delay = 0;

bool VehicleIndicators::delayState = true;

std::map<int, VehicleIndicatorState> VehicleIndicatorStates;

void VehicleIndicators::enableMaterial(RpMaterial* material) {
	VehicleMaterials::StoreMaterial(std::make_pair(reinterpret_cast<unsigned int*>(&material->surfaceProps.ambient), *reinterpret_cast<unsigned int*>(&material->surfaceProps.ambient)));

	material->surfaceProps.ambient = 4.0;
};

void VehicleIndicators::enableDummy(int id, VehicleDummy* dummy, CVehicle* vehicle, float vehicleAngle, float cameraAngle) {
	if (dummy->Type < 2) {
		float dummyAngle = vehicleAngle + dummy->Angle;

		float differenceAngle = ((cameraAngle > dummyAngle) ? (cameraAngle - dummyAngle) : (dummyAngle - cameraAngle));

		if (differenceAngle < 90.0f || differenceAngle > 270.0f)
			return;
	}

	CCoronas::RegisterCorona(reinterpret_cast<unsigned int>(vehicle) + 30 + id, vehicle, dummy->Color.red, dummy->Color.green, dummy->Color.blue, dummy->Color.alpha, dummy->Position,
		dummy->Size, PluginConfig::Siren->StreamDistance, eCoronaType::CORONATYPE_HEADLIGHT, eCoronaFlareType::FLARETYPE_NONE, false, false, 0, 0.0f, false, 0.5f, 0, 50.0f, false, true);
};
