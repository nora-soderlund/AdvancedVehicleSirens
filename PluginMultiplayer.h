#pragma once

#include "plugin.h"

#include <string>
#include <fstream>

#include <windows.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include <chrono>

#include "nlohmann/json.hpp"

#include "PluginLogs.h"
#include "PluginConfig.h"

class PluginMultiplayer {
	public:
		static void ReadHandle();

		static int GetVehicleIdentifier(DWORD poolPtr, CVehicle* vehicle);

		static DWORD GetVehiclePool();

		static void AddChatMessage(const char* string);

		static bool GetMouseState();

	private:
		static nlohmann::json addresses;

		static DWORD chat;
		static DWORD misc;
		static DWORD vehicles;

		static DWORD handle;

		static std::string version;
};
