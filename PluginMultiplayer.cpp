#include "PluginMultiplayer.h"

nlohmann::json PluginMultiplayer::addresses;

DWORD PluginMultiplayer::handle;

DWORD PluginMultiplayer::chat;
DWORD PluginMultiplayer::misc;
DWORD PluginMultiplayer::vehicles;

std::string PluginMultiplayer::version;

void PluginMultiplayer::ReadHandle() {
    handle = (DWORD)GetModuleHandleA("samp.dll");

    if (!handle) {
        AddLog("Multiplayer handle was not identified, disabling the multiplayer helper handle!");

        PluginConfig::Helper->Multiplayer = false;

        return;
    }

    DWORD byte;

    injector::ReadMemoryRaw((void*)(handle + 0xBAC9), &byte, 4, true);

    if (byte == 0x50000b96) {
        version = "0.3.DL";

        chat = 0x2ACA10;
        misc = 0x2ACA3C;
        vehicles = 0x1e650;
    }
    else if (byte == 0x10282e8) {
        version = "0.3.7 R1";

        chat = 0x21A0E4;
        misc = 0x21A10C;

        vehicles = 0x1b0a0;
    }
    else if (byte == 0x10362e8) {
        version = "0.3.7 R2";

        chat = 0x21A0EC;
        misc = 0x21A114;

        vehicles = 0x1b180;
    }
    else if (byte == 0xff575008) {
        version = "0.3.7 R3";

        chat = 0x26E8C8;
        misc = 0x26E8F4;

        vehicles = 0x1e440;
    }
    else if (byte == 0x89100e52) { // 0x8903e652
        version = "0.3.7 R4";

        chat = 0x26E9F8;
        misc = 0x26EA24;

        vehicles = 0x1eb40;
    }
    else {
        AddLog("Multiplayer version is not supported, disabling!");

        PluginConfig::Helper->Multiplayer = false;

        return;
    }

    AddLog("San Andreas Multiplayer " + version + " registered and running with helper methods!");
};

DWORD PluginMultiplayer::GetVehiclePool() {
    DWORD SAMP = *(DWORD*)(handle + 0x2ACA24);
    DWORD pool = *(DWORD*)(SAMP + 0x3DE);
    pool = *(DWORD*)(pool + 0xC);

    return pool;
};

int PluginMultiplayer::GetVehicleIdentifier(DWORD poolPtr, CVehicle* vehicle) {
    if (!PluginConfig::Helper->Multiplayer)
        return -1;

    if (version != "0.3.DL")
        return -1;

    uint(__thiscall * GetSAMPVehicleIdFromGTAHandle) (void* poolPtr, CVehicle * vehicle) = (uint(__thiscall*) (void* poolPtr, CVehicle * vehicle)) (handle + vehicles);

    return (int)GetSAMPVehicleIdFromGTAHandle((void*)poolPtr, vehicle);
};

void PluginMultiplayer::AddChatMessage(const char* string) {
    if (!PluginConfig::Helper->Multiplayer)
        return;

    if (!PluginConfig::Helper->MultiplayerMessages)
        return;

    //((void(__thiscall*) (void* chatPtr, int messageType, const char* msg, char* prefix, DWORD, DWORD)) (handle + 0x67650)) (*(DWORD**)(handle + chat), 4, std::string("{7E59CA}[AVS]{FFFFFF} " + std::string(string)).c_str(), (char*)"", 0xFFFFFFF, 0xFFFFFFF);
    ((void(__thiscall*) (void* chatPtr, int messageType, const char* msg, char* prefix, DWORD, DWORD)) (handle + 0x67650)) (*(DWORD**)(handle + chat), 4, std::string("{BC80B0}[AVS]{FFFFFF} " + std::string(string)).c_str(), (char*)"", 0xFFFFFFF, 0xFFFFFFF);
};

bool PluginMultiplayer::GetMouseState() {
    if (!PluginConfig::Helper->Multiplayer)
        return false;

    return *(BYTE*)((DWORD)(*(DWORD*)(handle + misc)) + 0x61);
};
