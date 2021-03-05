#pragma once

#include "game_sa/CVehicle.h"

#include <string>

bool EndsWith(const std::string& str, const std::string& suffix);

bool StartsWith(const std::string& str, const std::string& prefix);

uint64_t timeSinceEpochMillisec();

class PluginHelper {
	public:
		static void AddChatMessage(const char* string);

		static bool GetMouseState();

		static void RegisterMultiplayerHandle();

		static RwTexture* LoadTextureFromFile(const char* filename);

		static int GetMultiplayerVehicleIdentifier(CVehicle* vehicle);

		static DWORD base;
	private:
};