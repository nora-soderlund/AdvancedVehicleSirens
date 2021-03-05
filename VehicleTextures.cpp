#include "VehicleTextures.h"

#include "PluginHelper.h"
#include "PluginLogs.h"

RwTexture* VehicleTextures::Spotlight;

void VehicleTextures::Read() {
	char* file = (char*)std::string(GetPath() + "\\textures\\spotlight256.png").c_str();

	VehicleTextures::Spotlight = PluginHelper::LoadTextureFromFile(file);
};
