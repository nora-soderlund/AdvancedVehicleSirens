#pragma once

#include "plugin.h"

#include "game_sa/RenderWare.h"

#include "PluginLogs.h"

#include <string>
#include <map>

class PluginTextures {
	public:
		static std::map<std::string, RwTexture*> Textures;

		static RwTexture* GetTexture(std::string texture);

		static void RegisterEvents();

	private:
		static RwTexture* loadTextureFromFile(const char* filename);
};
