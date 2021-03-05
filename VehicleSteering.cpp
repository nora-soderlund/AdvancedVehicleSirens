#include "VehicleSteering.h"

bool VehicleSteering::enabled = false;

float VehicleSteering::mouseAccelerationHorizontal = 1.0f;
float VehicleSteering::mouseAccelerationVertical = 1.0f;

void VehicleSteering::RegisterEvents() {
	if (PluginConfig::Steering->Enabled == false)
		return;

    plugin::Events::drawHudEvent += []() {
        if (PluginMultiplayer::GetMouseState())
            return;

        CPed* ped = FindPlayerPed(-1);

        if (!ped->m_pVehicle || ped->m_pVehicle->m_pDriver != ped)
            return;

        CVehicleModelInfo* modelInfo = reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[ped->m_pVehicle->m_nModelIndex]);

        if (modelInfo->m_nVehicleType == VEHICLE_HELI)
            return;

        if (enabled && !plugin::KeyPressed(0x01)) {
            ped->m_pVehicle->m_bEnableMouseSteering = enabled = false;

            TheCamera.m_fMouseAccelHorzntl = mouseAccelerationHorizontal;
            TheCamera.m_fMouseAccelVertical = mouseAccelerationVertical;
        }
        else if (!enabled && plugin::KeyPressed(0x01)) {
            ped->m_pVehicle->m_bEnableMouseSteering = enabled = true;

            mouseAccelerationHorizontal = TheCamera.m_fMouseAccelHorzntl;
            mouseAccelerationVertical = TheCamera.m_fMouseAccelVertical;

            TheCamera.m_fMouseAccelHorzntl *= PluginConfig::Steering->Sensitivity;
            TheCamera.m_fMouseAccelVertical *= PluginConfig::Steering->Sensitivity;
        }
    };
};
