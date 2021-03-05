#include "plugin.h"
#include "common.h"

#include "world.h"

#include "PluginLogs.h"
#include "PluginConfig.h"
#include "PluginHelper.h"
#include "PluginData.h"
#include "PluginMultiplayer.h"
#include "PluginKeys.h"
#include "PluginVersion.h"
#include "PluginCoronas.h"

#include "VehicleLights.h"
#include "VehiclePaintjobs.h"
#include "VehicleMaterials.h"

#include "VehicleSpotlightData.h"
#include "VehicleIndicators.h"
#include "VehicleFoglights.h"
#include "VehicleSirens.h"
#include "VehicleSteering.h"

#include "ImVehFt.h"

#include "game_sa/CSprite2d.h"

#include "game_sa/CHud.h"
#include "game_sa/CPed.h"
#include "game_sa/CVehicleModelInfo.h"
#include "game_sa/CModelInfo.h"
#include "game_sa/CPools.h"
#include "game_sa/CControllerConfigManager.h"

#include "game_sa/C2dEffect.h"
#include "game_sa/CCoronas.h"

#include "game_sa/CControllerConfigManager.h"

#include <sstream>
#include <iostream>
#include <filesystem>
#include <map>

#include <string>

bool steeringEnabled = false;

bool versionChecked = false;

class world {

private:

public:
    world() {
        OpenLog();

        AddLog("Plugin path is: " + GetPath() + "\n");

        PluginConfig::Read();

        if (PluginData::Credited == false) {
            AddLog(" \nYour configuration file is missing the two lines you are told to NOT remove, put the credits back to remove the game text!");
            AddLog("Proper credits goes to Cake.\n ");
        }

        if (PluginConfig::Helper->Multiplayer)
            PluginMultiplayer::ReadHandle();

        plugin::Events::drawingEvent += PluginKeys::OnRender;

        plugin::Events::vehicleRenderEvent.before += [](CVehicle* vehicle) {
            VehicleMaterials::RestoreMaterials();

            VehicleMaterials::OnRender(vehicle);
        };
        
        /*plugin::Events::vehicleRenderEvent.after += [](CVehicle* vehicle) {
            VehicleMaterials::RestoreMaterials();

            VehicleMaterials::OnRender(vehicle);
        };*/

        //plugin::Events::vehicleRenderEvent.after += VehicleMaterials::OnRender;

        plugin::Events::vehicleSetModelEvent += VehicleMaterials::OnModelSet;

        PluginVersion::RegisterEvents();

        PluginCoronas::RegisterEvents();

        VehicleIndicators::RegisterEvents();

        VehicleFoglights::RegisterEvents();

        VehicleLights::RegisterEvents();

        VehicleSirens::RegisterEvents();

        plugin::Events::initGameEvent += []() {
            PluginData::Focused = true;
        };

        if (PluginConfig::Helper->GameFocus) {
            plugin::Events::d3dLostEvent += []() {
                PluginData::Focused = false;
            };

            plugin::Events::d3dResetEvent += []() {
                PluginData::Focused = true;
            };
        }

        if (PluginConfig::Paintjobs->Enabled) {
            std::string path = std::string(GetPath() + "\\paintjobs\\");

            for (int model = 400; model < 612; model++) {
                if (!std::filesystem::exists(path + std::to_string(model) + ".json"))
                    continue;

                AddLog("Reading paintjob configuration from paintjobs\\" + std::to_string(model) + ".json");

                std::ifstream stream(path + std::to_string(model) + ".json");

                nlohmann::json json;

                stream >> json;

                VehiclePaintjobs::Read(model, json);

                stream.close();
            }

            plugin::Events::vehicleCtorEvent += VehiclePaintjobs::OnVehicleSetModel;

            plugin::Events::vehicleRenderEvent += VehiclePaintjobs::OnVehicleRender;
        }

        if (PluginConfig::Spotlights->Enabled) {
            plugin::Events::vehicleSetModelEvent.after += [](CVehicle* vehicle, int model) {
                int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

                VehicleSpotlightData* data = new VehicleSpotlightData(vehicle);

                if (data->Frame != NULL)
                    PluginData::VehicleSpotlights[index] = data;
            };

            plugin::Events::drawingEvent += []() {
                if (!PluginData::Focused)
                    return;

                CPed* ped = FindPlayerPed(-1);

                if (!ped->m_pVehicle)
                    return;

                int index = CPools::ms_pVehiclePool->GetIndex(ped->m_pVehicle);

                if (PluginData::VehicleSpotlights.count(index) == 0)
                    return;

                if (!PluginData::VehicleSpotlights[index]->Frame)
                    return;

                PluginData::VehicleSpotlights[index]->OnHudRender();
            };

            plugin::Events::vehicleRenderEvent += [](CVehicle* vehicle) {
                int index = CPools::ms_pVehiclePool->GetIndex(vehicle);

                if (PluginData::VehicleSpotlights.count(index) == 0)
                    return;

                PluginData::VehicleSpotlights[index]->OnVehicleRender();
            };
        }

        VehicleSteering::RegisterEvents();

        if (PluginData::Credited == false) {
            plugin::Events::drawingEvent += [] {
                CHud::SetMessage((char*)std::string("Cake's Plugin").c_str());
            };
        }
        else if (PluginConfig::Hiiiii->Enabled) {
            plugin::Events::drawingEvent += [] {
                CHud::SetMessage((char*)std::string("Hiiiii").c_str());
            };
        }
    }

    ~world() {
        CloseLog();
    };
} _world;
