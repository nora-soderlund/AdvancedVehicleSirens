#pragma once

#include "PluginVersion.h"

#include <string>

std::string GetPath();

void OpenLog();

void AddLog(std::string line);

void CloseLog();