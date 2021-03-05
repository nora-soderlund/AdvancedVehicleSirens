#pragma once

#include "plugin.h"
#include "common.h"

#include "PluginLogs.h"
#include "PluginConfig.h"
#include "PluginHelper.h"
#include "PluginMultiplayer.h"

//#include <sstream>
//#include <iostream>
//#include <filesystem>
//#include <map>
//#include <iostream>
//#include <conio.h>
//#include <tchar.h>
//#include <stdio.h>
#include <string>
//#include <cstring>
#include <wininet.h> 

#include "nlohmann/json.hpp"

class PluginVersion {
	public:
		static std::string Current;

		static bool CheckedVersion;

		static void RegisterEvents();

	private:
		static void downloadManifest();
};
