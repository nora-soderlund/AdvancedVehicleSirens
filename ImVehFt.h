#pragma once

#include "PluginLogs.h"

#include <string>
#include <sstream>

class ImVehFt {
	public:
		void Read(std::string file);

		static int ReadColor(std::string input);
};
