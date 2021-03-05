#include "PluginVersion.h"

std::string PluginVersion::Current = "BETA Build 4 Debug";

bool PluginVersion::CheckedVersion = false;

void PluginVersion::RegisterEvents() {
    if (!PluginConfig::Helper->VersionCheck)
        return;

    plugin::Events::drawingEvent += []() {
        if (CheckedVersion)
            return;

        CheckedVersion = true;

        downloadManifest();
    };
};

void PluginVersion::downloadManifest() {
    try {
        AddLog("");

        std::string content;

        HINTERNET hInternet, hFile;

        char buf[1024];

        DWORD bytes_read;

        int finished = 0;

        hInternet = InternetOpen("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

        if (hInternet == NULL) {
            AddLog("Failed to start an internet session to download the versions manifest!");

            return;
        }

        DWORD rec_timeout = 5 * 1000;					// override the 30 second timeout

        InternetSetOption(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &rec_timeout, sizeof(rec_timeout));

        uint64_t time = timeSinceEpochMillisec();

        std::string hostname = std::string("http://avs.cake-dev.tech/versions.json?v=" + std::to_string(time));

        hFile = InternetOpenUrl(hInternet, hostname.c_str(), NULL, 0L, 0, 0);

        if (hFile == NULL) {
            AddLog("Failed to estabilish a connection to the versions manifest document!");

            return;
        }

        std::string buffer;

        while (!finished) {
            if (InternetReadFile(hFile, buf, sizeof(buf), &bytes_read)) {
                if (bytes_read > 0)
                    buffer.append(buf, bytes_read);
                else
                    finished = 1;
            }
            else {
                AddLog("Failed to read the versions manifest document!");

                finished = 1;
            }
        }

        InternetCloseHandle(hInternet);
        InternetCloseHandle(hFile);

        if (!buffer.size()) {
            AddLog("The version manifest document is empty!");

            return;
        }

        nlohmann::json manifest = nlohmann::json::parse(buffer);

        if (manifest.is_discarded()) {
            AddLog("Failed to parse the versions manifest!");

            return;
        }

        if (!manifest.contains("versions")) {
            AddLog("The versions manifest are corrupted, does not contain versions!");

            return;
        }

        nlohmann::json versions = manifest["versions"];

        if (!manifest.contains("current")) {
            AddLog("The versions manifest are corrupted, does not contain current!");

            return;
        }

        std::string version = manifest["current"];

        std::string versionDate = versions[version]["date"];

        if (!versions.contains(Current)) {
            AddLog("Failed to identify " + Current + ", your build appears to be corrupted!");

            PluginMultiplayer::AddChatMessage(std::string("Plugin version " + Current + " was not found, your build appears to be corrupted!").c_str());
            PluginMultiplayer::AddChatMessage(std::string("You can download the latest build at https://avs.cake-dev.tech/").c_str());

            return;
        }

        nlohmann::json build = versions[Current];

        if (Current != version) {
            if (build.contains("type") && build["type"] == "debug")
                PluginMultiplayer::AddChatMessage(std::string("You are running " + Current + " in debug mode").c_str());
            else {
                if (build.contains("deprecated") && build["deprecated"])
                    PluginMultiplayer::AddChatMessage(std::string("Your version, " + Current + ", has been deprecated and should be replaced as soon as possible!").c_str());
                else
                    PluginMultiplayer::AddChatMessage(std::string("A newer version, " + version + ", has been released on the " + versionDate + "!").c_str());

                PluginMultiplayer::AddChatMessage(std::string("You can download the latest build at https://avs.cake-dev.tech/").c_str());

                AddLog("A newer version, " + version + " has been released on the " + versionDate + "!");
                AddLog("You can download the latest build at https://avs.cake-dev.tech/");
            }

            return;
        }

        AddLog("");
    }
    catch (...) {
        AddLog("An unknown exception occured when trying to download the versions manifest file!");
    }
};
