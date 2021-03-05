#include "world.h"

#include "PluginLogs.h"

#include <string>
#include <fstream>
#include <filesystem>

std::ofstream LogStream;

std::string PluginPath = std::string(std::filesystem::current_path().string() + "\\AdvancedVehicleSirens");

std::string GetPath() {
	return PluginPath;
};

void OpenLog() {
	LogStream.open(std::string(GetPath() + "\\AdvancedVehicleSirens.log").c_str(), std::fstream::out | std::fstream::trunc);

	LogStream.close();

	AddLog("Advanced Vehicle Sirens " + PluginVersion::Current + " by Cake!\n");
}

void AddLog(std::string line) {
	LogStream.open(std::string(GetPath() + "\\AdvancedVehicleSirens.log").c_str(), std::fstream::app);

	LogStream << line << "\n";

	LogStream.close();
};

void CloseLog() {
};
