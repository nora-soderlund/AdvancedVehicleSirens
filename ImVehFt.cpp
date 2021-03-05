#include "ImVehFt.h"

int ImVehFt::ReadColor(std::string input) {
    if (input.length() == 3)
        return std::stoi(input);

    std::istringstream stream(input);

    int color;

    stream >> std::hex >> color;

    return color;
};
