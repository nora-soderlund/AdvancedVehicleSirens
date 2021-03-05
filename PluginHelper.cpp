#include "game_sa/CVehicle.h"

#include "PluginHelper.h"
#include "PluginConfig.h"

#include <windows.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include <chrono>

DWORD PluginHelper::base;

/*void PluginHelper::RegisterMultiplayerHandle() {
    base = (DWORD)GetModuleHandle("samp.dll");

    if (base) {
        DWORD byte;

        injector::ReadMemoryRaw((void*)(base + 0xBAC9), &byte, 4, true);

        if (byte != 0x50000b96)
            PluginConfig::Helper->Multiplayer = false;
    }
    else
        PluginConfig::Helper->Multiplayer = false;
};

void PluginMultiplayer::AddChatMessage(const char* string) {
    if (!PluginConfig::Helper->Multiplayer)
        return;

    if (!PluginConfig::Helper->MultiplayerMessages)
        return;

    const char* message = std::string("{7E59CA}[AVS]{FFFFFF} " + std::string(string)).c_str();

    DWORD* chat = *(DWORD**)(base + 0x2ACA10);

    ((void(__thiscall*) (void* chatPtr, int messageType, const char* msg, char* prefix, DWORD, DWORD)) (base + 0x67650)) (chat, 4, message, "", 0xFFFFFFF, 0xFFFFFFF);
};

bool PluginMultiplayer::GetMouseState() {
    if (!PluginConfig::Helper->Multiplayer)
        return false;

    DWORD misc = *(DWORD*)(base + 0x2ACA3C);

    return *(BYTE*)(misc + 0x61);
};

int PluginMultiplayer::GetVehicleIdentifier(PluginMultiplayer::GetVehiclePool(), CVehicle* vehicle) {
    if (!PluginConfig::Helper->Multiplayer)
        return -1;

    DWORD g_SAMP = *(DWORD*)(PluginHelper::base + 0x2ACA24);
    DWORD g_VehiclePool = *(DWORD*)(g_SAMP + 0x3DE);
    g_VehiclePool = *(DWORD*)(g_VehiclePool + 0xC);

    uint(__thiscall * GetSAMPVehicleIdFromGTAHandle) (void* poolPtr, CVehicle * vehicle) = (uint(__thiscall*) (void* poolPtr, CVehicle * vehicle)) (PluginHelper::base + 0x1e650);

    return (int)GetSAMPVehicleIdFromGTAHandle((void*)g_VehiclePool, vehicle);
};*/

bool EndsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool StartsWith(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
};

RwTexture* PluginHelper::LoadTextureFromFile(const char* filename) {
    RwImage* image = RtPNGImageRead(filename);

    RwInt32 width, height, depth, flags;
    RwImageFindRasterFormat(image, 4, &width, &height, &depth, &flags);

    RwRaster* raster = RwRasterCreate(width, height, depth, flags);

    RwRasterSetFromImage(raster, image);

    RwImageDestroy(image);

    return RwTextureCreate(raster);
};
